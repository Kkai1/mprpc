#include "rpcprovider.h"
#include "mprpcapplication.h"
#include "rpcheader.pb.h"
#include "logger.h"
#include "zookeeperutil.h"

/* 
service => service描述
                => service* 记录服务对象
                method_name => method方法对象
*/
// 框架提供的专门服务发布rpc服务的网络对象类
// 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
void RpcProvider::NotifyService(google::protobuf::Service* service){
    ServiceInfo service_info;

    // 获取服务对象的描述信息 
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();
    // 获取服务的名称
    std::string service_name = pserviceDesc->name();
    // 获取服务对象service的方法的数量
    int methodCnt = pserviceDesc->method_count();

    LOG_INFO("service_name:%s", service_name.c_str());

    for(int i = 0;i < methodCnt;++i){
        // 获取了服务对象指定下标的服务方法的描述（抽象描述）
        const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.m_methodMap.insert({method_name,pmethodDesc});

        LOG_INFO("method_name:%s", method_name.c_str());
    }
    service_info.m_service = service;
    m_ServiceMap.insert({service_name,service_info});
}

//启动rpc服务节点，开始提供rpc远程调用服务 
void RpcProvider::Run(){
    // 组合了TcpServer
    std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;

    // 读取配置文件rpcserver的信息
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserver_ip");
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserver_port").c_str());
    muduo::net::InetAddress address(ip, port);
    
    // 创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop,address, "RpcProvider");

    // 绑定连接回调，和消息读写回调方法  用muduo库很好地分离了网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库的线程数量
    server.setThreadNum(4);

    // 把当前rpc节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    ZkClient zkCli;
    zkCli.Start();
    // service_name设为永久性节点   method_name设为临时性节点
    for(auto &sp : m_ServiceMap){
        // /service_name
        std::string service_path = "/" + sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0, 0);
        for(auto &mp : sp.second.m_methodMap){
            // /service_name/method_name  存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL); // ZOO_EPHEMERAL 表示临时性节点，默认为永久性节点
        }
    }

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip: " << ip << " port: " << port << std::endl;

    // 启动网络服务
    server.start();
    m_eventLoop.loop();

}

// 新的socket连接回调
void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr &conn){
    if(!conn->connected()){
        // 和rpc client的连接断开了
        conn->shutdown();
    }

}

/*
在框架内部，RpcProvider和RpcConsumer协商好之间通信的protobuf数据格式
service_name method_name args  定义proto的message类型，进行数据头的序列化和反序列化
                                service_name method_name args_size
16UserServiceLoginzhang san123456

header_size(4个子节) + header_str + args_str

利用 std::string 的 inset、copy方法
*/
// 已建立连接用户的读写事件回调  如果远程有一个rpc服务的调用请求，那么OnMessage方法就会响应
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr& conn,
                            muduo::net::Buffer *buffer,
                            muduo::Timestamp)
{
    // 将接收到的字节流全部转码为字符串    网络上接收的远程rpc调用请求的字符流  包含了Login方法名、args参数
    std::string recv_buf = buffer->retrieveAllAsString();\

    // 从字符流中读取前4字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size, 4, 0);
    
    // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4, header_size);
    mprpc::RpcHeader rpcHeader;
    std::string service_name;
    std::string method_name;
    uint32_t args_size;
    if(rpcHeader.ParseFromString(rpc_header_str)){
        // 数据反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    }else{
        // 数据反序列化失败
        std::cout << "rpc_header_str" << rpc_header_str << " parse error" << std::endl;
        return;
    }

    // 获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4 + header_size,args_size);

    // 打印调试信息
    std::cout << "===========================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str:  " << rpc_header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_str: " << args_str << std::endl;
    std::cout << "===========================================" << std::endl;

    // 获取service对象和method对象
    if(!m_ServiceMap.count(service_name)){
        std::cout << service_name << "is not exist" << std::endl;
        return;
    }

    if(!m_ServiceMap[service_name].m_methodMap.count(method_name)){
        std::cout << service_name << ":" << method_name << "is not exist" << std::endl;
        return;
    }

    google::protobuf::Service *service = m_ServiceMap[service_name].m_service; // 获取service对象 new UserService
    const google::protobuf::MethodDescriptor *method = m_ServiceMap[service_name].m_methodMap[method_name]; // 获取method对象

    // 生成rpc方法调用的请求request和响应response参数
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str)){
        std::cout << "request parse error, content" << args_str << std::endl;
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 给下面的method方法的调用，绑定一个Closure的回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider, const muduo::net::TcpConnectionPtr&, google::protobuf::Message*>(this, &RpcProvider::SendRpcResonse, conn, response);
 
    // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    // 这里相当于 new UserService().Login(controller,request,response,done) 这里是框架中通用化，以抽象的方式进行方法的调用，因为调用的服务以及方法并不固定。
    service->CallMethod(method,nullptr,request,response,done); 

}

// Closure的回调操作，用于序列化rpc的响应和网络发送
void RpcProvider::SendRpcResonse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message* response){
    std::string response_str;
    if(response->SerializeToString(&response_str)){ // response进行序列化
        // 序列化成功后，通过网络把rpc响应发送给rpc调用方
        conn->send(response_str);
    }else{
        std::cout << "serialize response_str error!" << std::endl;
    }
    conn->shutdown(); // 模拟http的短链接服务，由rpcprovider主动断开连接
}
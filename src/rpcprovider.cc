#include "rpcprovider.h"
#include <string>
#include "mprpcapplication.h"
#include <functional>


void RpcProvider::NotifyService(google::protobuf::Service* service){
    
}

void RpcProvider::Run(){
    // 组合了TcpServer
    std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;

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

    std::cout << "RpcProvider start service at ip: " << ip << " port: " << port << std::endl;

    // 启动网络服务
    server.start();
    m_eventLoop.loop();

}

void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr& conn){

}

void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr&,muduo::net::Buffer*,muduo::Timestamp){

}
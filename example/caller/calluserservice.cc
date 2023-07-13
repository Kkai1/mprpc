#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc, char **argv){
    // 整个程序启动以后，想使用mprpc来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc,argv);

    // 演示调用远程发布的rpc方法Login 定义一个代理对象
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc 方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;  
    // 发起rpc方法的调用 同步的rpc调用过程 MprpcChannel::callmethod方法的调用  同步阻塞的方式
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送
    // 一次rpc调用完成，读调用结果
    if(0 == response.result().errcode()){
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }else{
        std::cout << "rpc login response error:" << response.result().errmsg() << std::endl;
    }

    return 0;
} 
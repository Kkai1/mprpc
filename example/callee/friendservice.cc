#include <iostream>
#include <string>
#include "friend.pb.h" 
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>

class FriendService:public fixbug::FriendServiceRpc{
public:
    std::vector<std::string> GetFriendsList(uint32_t id){
        std::cout << "do GetFriendsList service! userid:" << id << std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("mao kai");
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done){
        uint32_t id = request->userid();
        std::vector<std::string> friendslist = GetFriendsList(id);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(std::string name : friendslist){
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }

};

int main(int argc,char** argv){
    // 调用框架的初始化操作 provider -i config.conf
    MprpcApplication::Init(argc,argv);

    // provider是一个rpc网络服务对象。把FriendService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    // 启动一个rpc服务器发布节点。Run以后，进程进入阻塞状态，等待远程rpc调用请求
    provider.Run();

    return 0;
}




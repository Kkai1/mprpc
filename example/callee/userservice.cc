#include <iostream>
#include <string>
#include "user.pb.h" 


/*
    UserService原来是一个本地服务，提供两个进程内的本地方法，Login和GetFriendLists
    需求：
        将UserService类的Login方法变成一个rpc远程方法，不仅在进程内部调用，还可以在不同进程或者不同机器上进行调用

*/
class UserService : public fixbug::UserServiceRpc{ // 使用在rpc服务发布端（rpc服务提供者）
public:
    //这是本地的方法
    bool Login(std::string name,std::string pwd){
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << "pwd:" << pwd << std::endl;
        return true;
    }
    /*
        如果远端想要调用的方法，通过request匹配到相应的方法，我们在该方法下，填写相应的响应，然后做出回调发回响应。
        1. caller   ===>    Login(LoginRequest) => muduo => callee
        2. callee   ===>    Login(LoginRequest) => 交到重写的Login方法上了
    */
    // 重写基类UserServiceRpc的虚函数，下面这些方法都是框架直接调用的
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done){
        // 框架给业务上报了请求参数LoginRequest，应用获取响应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务
        bool login_result = Login(name,pwd);

        // 把响应写入 包括错误码 错误消息 返回值
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作  执行响应对象的序列化和网络发送（都是由框架来完成的）
        done->Run();
    }

    



};

int main(){
    UserService us;
    us.Login("xxx","xxx");

    return 0;
}

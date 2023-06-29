#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;


int main(){
    /*
    LoginResponse rsp;
    ResultCode* rc = rsp.mutable_result();
    rc->set_errcode(0);
    rc->set_errmsg("登录处理失败了");
    */
    GetFriendListsResponse gflr;
    ResultCode* rc = gflr.mutable_result();
    rc->set_errcode(0);
    rc->set_errmsg("登录处理失败了");
    User* user1 = gflr.add_friend_list();
    user1->set_age(25);
    user1->set_name("xiao ming");
    user1->set_sex(User::MAN);

    User* user2 = gflr.add_friend_list();
    user2->set_age(25);
    user2->set_name("xiao li");
    user2->set_sex(User::MAN);

    std::cout << gflr.friend_list_size() << std::endl;

    

    return 0;
}



/*
int main1(){

    //封装了login请求对象的数据
    LoginRequest req;
    req.set_name("ZhangSan");
    req.set_pwd("123");
    
    //对象数据序列化
    std::string send_str;
    if(req.SerializeToString(&send_str)){
        std::cout << send_str.c_str() << std::endl;
    }

    //从send_str反序列化一个login请求对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str)){
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }


    return 0;
}
*/



    


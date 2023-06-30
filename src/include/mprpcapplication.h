#pragma once

//mprpc框架的基础类,负责框架的的初始化
class MprpcApplication{
public:
    static void Init(int argc,char** argv);
    static MprpcApplication& GetInstance();
   
private:
    MprpcApplication();
    // 删除拷贝构造函数
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};




#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp(){
    std::cout << "format: command -i <configfile>" << std::endl; 
}

void MprpcApplication::Init(int argc,char** argv){
    //如果没有传入参数
    if(argc < 2){
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    //也就是读取配置文件，以i:
    while((c = getopt(argc,argv,"i:")) != -1){
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            //出现不希望的参数
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            //出现-i但是没有参数
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default: 
            break;
        }
    }

    //开始加载配置文件 rpcserver_ip= rpcserver_port= zookeeper_ip= zookeeper_port=
    m_config.LoadConfigFile(config_file.c_str());
 
    std::cout << "rpcserver_ip:"   << m_config.Load("rpcserver_ip")    << std::endl;
    std::cout << "rpcserver_port:" << m_config.Load("rpcserver_port")  << std::endl;
    std::cout << "zookeeper_ip:"   << m_config.Load("zookeeper_ip")    << std::endl;
    std::cout << "zookeeper_port:" << m_config.Load("zookeeper_port")  << std::endl;


}

MprpcApplication& MprpcApplication::GetInstance(){
    static MprpcApplication app;
    return app;
}

MprpcConfig& MprpcApplication::GetConfig(){
    return m_config; 
}
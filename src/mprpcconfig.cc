#include "mprpcconfig.h"

#include <iostream>
#include <string>

void MprpcConfig::LoadConfigFile(const char* config_file){
    FILE *pf = fopen(config_file,"r");
    if(pf == nullptr){
        std::cout << config_file <<" is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 需要考虑的 1.注释 2.正确的配置项 = 3.去掉开头的多余空格 
    while(!feof(pf)){
        char buf[512] = {0};
        fgets(buf,512,pf);
        
        // 去掉字符串前面多余的空格
        std::string src_buf(buf);
        int idx = src_buf.find_first_not_of(' ');
        if(idx != -1){
            // 说明字符串前面存在空格
            src_buf = src_buf.substr(idx,src_buf.size()-idx);
        }
        // 去掉字符串后面多余的空格
        idx = src_buf.find_last_not_of(' ');
        if(idx != -1){
            // 说明字符串后面存在空格
            src_buf = src_buf.substr(0,idx);
        }

        // 判断#的注释
        if(src_buf[0] == '#' || src_buf.empty()){
            //读取下一行
            continue;
        }

        //判断解析配置项 =
        idx = src_buf.find('=');
        if(idx == -1){
            //解析配置项不合法
            continue;
        }

        //解析配置项存在
        int begin = src_buf.find_first_not_of(' ',idx+1);
        int end = src_buf.find_last_not_of(' ');

        std::string key = "";
        std::string value = "";

        if(begin != -1 && end != -1){
            key = src_buf.substr(0,idx);
            value = src_buf.substr(begin,end);
        }else{
            continue;
        }
        
        m_configMap.insert({key,value});
    }
}

std::string MprpcConfig::Load(std::string key){
    auto it = m_configMap.find(key);
    if(it == m_configMap.end()){
        return "";
    }
    return it->second;
}
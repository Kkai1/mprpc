#include "zookeeperutil.h"
#include "mprpcapplication.h"
#include <iostream>
#include <semaphore.h>

void globle_watcher(zhandle_t *zh, int type, 
        int state, const char *path,void *watcherCtx){
    // 判断zk服务端的连接状态
    if(type = ZOO_CONNECTED_STATE){
        if(state == ZOO_CONNECTED_STATE){
            sem_t *sem = (sem_t*)zoo_get_context(zh);
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient() : m_zhandle(nullptr){
}

ZkClient::~ZkClient(){
    if(m_zhandle != nullptr){
        zookeeper_close(m_zhandle); // 关闭句柄，释放资源
    }
}
    
// zkclient启动连接zkserver
void ZkClient::Start(){
    std::string host = MprpcApplication::GetInstance().GetConfig().Load("zookeeper_ip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("zookeeper_port");
    std::string connstr = host + ":" + port;

    /*
    zookeeper_mt:多线程版本
    zookeeper的API客户端程序提供了三个线程：
    1.API调用线程
    2.网络I/O线程 pthread_create  采用poll方案
    3.watcher回调机制线程
    */
    //该函数执行后，globle_watcher回调机制线程就启动了  30s
    m_zhandle = zookeeper_init(connstr.c_str(), globle_watcher, 30000, nullptr, nullptr, 0);
    if(nullptr == m_zhandle){
        std::cout << "zookeeper_init error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem);

    sem_wait(&sem);  // 阻塞，等待信号量被posted
    std::cout << "zookeeper_init success!" << std::endl; 
}

// 在zkserver上根据指定的path创建znode节点
void ZkClient::Create(const char *path, const char *data, int datalen, int state){
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);
    int flag;
    // 先判断path表示的znode节点是否存在，如果存在，就不再重复创建了
    flag = zoo_exists(m_zhandle, path, 0, nullptr);
    if(ZNONODE == flag){ // 表示path的znode节点不存在
        // 创建指定path的znode节点
        flag = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
        if(ZOK == flag){
            std::cout << "znode create success... path:" << path << std::endl;
        }else{
            std::cout << "flag:" << flag << std::endl;
            std::cout << "znode create error... path:" << path << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

// 根据参数指定的znode节点路径，或者znode节点的值
std::string ZkClient::GetData(const char *path){
    char buffer[64];
    int bufferlen = sizeof(buffer);
    int flag = zoo_get(m_zhandle, path, 0, buffer, &bufferlen, nullptr);
    if(flag != ZOK){
        std::cout << "get znode error... path:" << path << std::endl;
        return "";
    }else{
        return buffer;
    }
}



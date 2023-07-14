#include "logger.h"
#include <iostream>

// 获取日志的单例
Logger& Logger::GetInstance(){
    static Logger logger;
    return logger;
}

Logger::Logger(){
    // 启动专门的写日志线程
    std::thread writeLogTask([&](){
        for(;;){
            // 获取当前的日期，然后取日志信息，写入响应的日志文件当中 a+
            time_t now = time(nullptr); // 获取1970年到现在的秒数
            tm *nowtm = localtime(&now); // 换算成当前时间
            
            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt",nowtm->tm_year+1900,nowtm->tm_mon+1,nowtm->tm_mday);

            // "a+" : Open  for  reading and appending (writing at end of file).
            FILE *pf = fopen(file_name, "a+");
            if(pf == nullptr){
                std::cout << "logger file : " << file_name << "open error!" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string msg = m_lckQue.Pop();
            
            char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d =>[%s]",nowtm->tm_hour, nowtm->tm_min, nowtm->tm_sec, (m_loglevel == INFO ? "info" : "error"));
            msg.insert(0, time_buf);
            msg.append("\n");

            fputs(msg.c_str(),pf);
            fclose(pf);

        }

    });
    // 设置分离线程，守护线程
    writeLogTask.detach();

}

// 设置日志级别
void Logger::SetLogLevel(LogLevel level){
    m_loglevel = level;
}

// 写日志  把日志信息写入lockqueue缓冲区当中
void Logger::Log(std::string msg){
    m_lckQue.push(msg);
}
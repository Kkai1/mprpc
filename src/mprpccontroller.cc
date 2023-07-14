#include "mprpccontroller.h"

MprocController::MprocController(){
    m_failed = false;
    m_errText = "";
}  

void MprocController::Reset(){
    m_failed = false;
    m_errText = "";
}

bool MprocController::Failed() const{
    return m_failed;
}

std::string MprocController::ErrorText() const{
    return m_errText;
}

void MprocController::SetFailed(const std::string& reason){
    m_failed = true;
    m_errText = reason;
}

// 目前未实现具体的功能
void MprocController::StartCancel(){

}

bool MprocController::IsCanceled() const{
    return false;
}

void MprocController::NotifyOnCancel(google::protobuf::Closure* callback){
    
}
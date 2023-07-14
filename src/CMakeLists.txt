# 将当前目录下所有源文件放入 SRC_LIST
# aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcprovider.cc 
    rpcheader.pb.cc 
    mprpcchannel.cc 
    mprpccontroller.cc
    logger.cc)

# 将SRC_LIST中的源文件生成一个动态库
# add_library(mrpc SHARED ${SRC_LIST})
add_library(mrpc ${SRC_LIST})
# 顺序不能改变
target_link_libraries(mrpc muduo_net muduo_base pthread)

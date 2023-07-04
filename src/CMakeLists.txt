# 将当前目录下所有源文件放入 SRC_LIST
# aux_source_directory(. SRC_LIST)
set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcprovider.cc)

# 将SRC_LIST中的源文件生成一个动态库
add_library(mrpc SHARED ${SRC_LIST})

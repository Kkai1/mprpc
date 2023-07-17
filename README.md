这是一个基于protobuf实现数据的序列化与反序列化，由zookeeper作为rpc服务注册中心，具备日志系统功能的远程服务调用框架。
提供可调用的静态库，文件存放lib目录下。

提供测试的可执行文件存储在/bin目录下，test.conf为配置文件，测试方式如下。
./provider -i test.conf
./consumer -i test.conf

# VMarchTools部署工具
> VMarchTools可以很方便的帮助开发部署、测试、监控、排查BUG等开发功能。VMarchTools使用C++开发。只有开发了Linux版本；

## 简单演示

**运行服务**
```shell
$ vmarch start -xtl -cp dev -vdb 8080
```
 - 打印日志`（-xtl）`
 - 设置远程调试端口`（-vdb）`
 - 使用application-dev配置文件`（-cp）`

**使用Status命令**
```shell
$ vmarch status pid
```
```shell
• springboot-demo.jar from VMarchTools <status> command.
    Start/Run Status (java -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=8999 -jar foxlibc-1.0.0.jar --spring.config.location=application-dev.yml)
      └─CPU: 2.70%
      └─Memory: 2.76%
      └─VSZ: 2.76%
      └─RSS: 2.76%
    Main PID: 2382465
  process status: Sl
  terminal status: pts/0
start & run time:  10:31/0:16
```
## 安装/构建

### 编译环境

- `cmake3.22.1及以上`
- `gcc/g++8.3.0 (Uos 8.3.0.3-3+rebuild)`

### 安装
将源码下载到一个目录中，比如`home`目录下。然后进入VMarchTools目录使用如下命令：

```shell
$ sh make
```

当前编译成功后输入`vmarch -h`验证是否可以使用。
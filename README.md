# VMarchTools部署工具
> VMarchTools可以很方便的帮助开发部署、测试、监控、排查BUG等开发功能。VMarchTools使用C++开发。只有开发了Linux版本；

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
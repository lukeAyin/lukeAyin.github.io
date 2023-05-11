### 三个配置文件

#### 系统配置：存放在%Git%/etc/gitconfig 

git config --system core.autocrlf

#### 用户配置：linux存放在~/.gitconfig

git config --global user.name

#### 仓库配置：存放在仓库的.git/config

git config --local remote.origin.url

优先级由小变大

### Git基础配置

git  config --global user.name "lukeayin"

git config --global user.email "lukeayin@gmail.com"

这个配置信息会在Git仓库提交的修改信息中体现，但和git服务器认证使用的密码或者公钥密码无关

责任追踪/应用之间的用户关联/贡献度统计

#### 文本换行符配置

> windows使用CRLF结束一行，linux和mac使用LF结束一行

git 可以在提交时自动把行结束符CRLF转换成LF，签出代码时把LF转换成CRLF，使用core.autocrlf来打开此项功能。在windows系统上把它设置成true，签出代码时，LF会转换成CRLF。

git config --global core.autocrlf true

linux或mac系统使用LF作为行结束符，使用core.autocrlf设置成input来告诉git在提交时把CRLF转换成LF，签出时不转换。

git config --global core.autocrlf input

这样在windows系统上的签出文件中保留CRLF，在mac和linux系统上，包括仓库中保留LF。

#### 与服务器的认证配置

1. http/https协议认证

设置口令缓存：

git config --global credential.helper store

添加HTTPS证书信任：

git config http.sslverify false

ssh 协议认证

2. ssh协议认证

ssh协议时一种非常常用的git仓库访问协议，使用公钥认证、无需输入密码，加密传输，操作便利又保证安全性。




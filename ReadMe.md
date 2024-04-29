## 实现思路
针对每个功能各自写一个xx.c文件，编译产生可执行文件。
shell.c作为主程序不断接收用户输入命令，根据命令调用各自功能的可执行文件。
## 构建运行
```
git clone xx
cd xx
make build
```
## 注意
我的代码中有大量注释，特别是ls.c，时间不是很充裕没有完全测试所以功能，但是可以保证基本正确，如果遇到有错误请指正并自行更改。
## 命令实现
| 命令| 解释|
|----|----|
|whoami|我是谁？？|
|clear|清屏|
|pwd|打印工作路径|
|cd dir|跳转工作目录到指定目录（相对路径觉得轮都行）| 
|cp [src] [dest]|复制文件|
|head \<-n x> filename|打印文件前x行,默认5行|
|echo str1 str2 … strn|n=1，可以去除单双引号；n>1，各str中间的多个空格只打印一个|
|cat [file]|打印文件|
|cat [src] [> \| >>] [dest]|重定向打印：>覆盖式，>>追加式|
|mv [file1] [file2]|移动文件|
|rmdir dir|创建目录|
|rm [file/dir]|移除文件或者目录|
|ls -[a/l/al/R] \<dir>|列出指定目录下的文件，-a表示所有（包括"."开头的文件）；-l表示列表形式展示；-R表示递归打印子目录的文件|


此代码参考 [MyShell/myshell at main · DreamboatW/MyShell (github.com)](https://github.com/DreamboatW/MyShell/tree/main/myshell)

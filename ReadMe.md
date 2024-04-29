## 实现思路
针对每个命令功能写一个xx.c文件，然后编译产生可执行文件到/bin目录。<br>
shell.c作为主程序循环接收用户输入命令，根据命令调用对应可执行文件。
## 构建运行
```
git clone https://github.com/mendge/shell-demo.git
cd shell-demo
make
```
点击运行bin目录下的shell即可
## 注意
- 代码中有大量中文注释，特别是ls.c。
- 没有完全测试所功能，但是可以保证基本正确。
- 只能运行在 Linux 系统（不支持 Macos 和 Windows ）
## 命令实现
| 命令| 解释|
|----|----|
|whoami|我是谁？？|
|clear|清屏|
|pwd|打印工作路径|
|cd [dir]|跳转工作目录到指定目录| 
|cp [src] [dest]|复制文件|
|head \<-n x> filename|打印文件前 x 行，默认 5 行|
|echo [str]|在命令行中打印 str ，会去掉首尾的单双引号|
|cat [file]|打印文件内容|
|cat [src] [> \| >>] [dest]|重定向打印：`>`覆盖式，`>>`追加式|
|mv [file1] [file2]|移动文件|
|rmdir dir|创建目录|
|rm [file/dir]|移除文件或者目录|
|ls -[a/l/al/R] \<dir>|列出指定目录下的文件<br>`-a`打印所有（包括"."开头的文件）<br>`-l`以列表形式打印<br>`-R`表示递归打印子目录的文件|

注：[xx]中的是命令参数，\<xx>中的是可选参数


此代码参考 [MyShell/myshell at main · DreamboatW/MyShell (github.com)](https://github.com/DreamboatW/MyShell/tree/main/myshell)

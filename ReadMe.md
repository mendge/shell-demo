此代码参考 [MyShell/myshell at main · DreamboatW/MyShell (github.com)](https://github.com/DreamboatW/MyShell/tree/main/myshell)

我的代码中有大量注释，特别是ls.c，时间不是很充裕没有完全测试所以功能，但是可以保证基本正确，如果遇到有错误请指正并自行更改。

思路：

针对每个功能各自写一个.c文件实现，最后实现shell.c作为主程序创建子进程调用各个功能.c文件编译出的.out文件。实现功能如下：

###### (1)	head [-n line] filename

打印文件前line行
line默认为5； 

###### (2)	cd destdir

destdir可是绝对或者相对路径

###### (3)	clear

###### (4)	cp srcfile destfile

###### (5)	echo str1 str2 … strn

n=1，可以去除单双引号
n>1，各str中间的多个空格只打印一个

###### (6)	cat filename

打印文件名

###### cat file1 >/>> file2

File1打印到file2          >：覆盖上打印  >>：追加式打印

###### (7)	mv file1 file2

file2可带相对路径和绝对路径

###### (8)	pwd

###### (9)	rmdir dir

###### (10)	rm file/dir

###### (11)	whoami

获取用户名

###### (12)	ls [-a/-l/-al/-R] dir

-a/-al  输出文件名，帶. 和..
-l/-al  输出文件基本信息，不帶. 和..
-R 遇到目录则要输出其子目录的文件名
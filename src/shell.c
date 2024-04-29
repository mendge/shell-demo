#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<sys/wait.h>
#include<unistd.h>

void printLoginName();

void printHostName();

void printDir();

int main()
{
    while(1){
        printLoginName();
        printHostName();
        printDir();
        // fflush()用于清空文件缓冲区，如果文件是以写的方式打开 的，则把缓冲区内容写入文件
        // 成功返回0，失败返回EOF，错误代码存于errno 中。指定的流没有缓冲区或者只读打开时也返回0值
        fflush(stdout);

        char buf[1024];
        // read是unistd.h中的函数，会把参数fd=0所指的文件传送count 个字节到buf 指针所指的内存中
        // 返回实际读到的字节数
        // fd: 是文件描述符, 从command line获取数据时，为0
        // 如果是wirte函数写到命令行则fd参数置1
        int s = read(0,buf,1024);
		// 键入的回车键会写进来，去掉
		buf[s-1] = '\0';

        // 用来处理命令行中的\b，基本不会用
        if(s > 0){
            int i = 0;
            for(i=0; i<s; ++i){
                // \b的含义是，将光标从当前位置向前（左）移动一个字符（遇到\n或\r则停止移动）
                // 并从此位置开始覆盖式输出\b后面的字符（空字符\0和换行符\n除外)
                // 下面是对'\b'是否在字符串首的两种情况的处理，自己构造一个实例情况就能理解
                if(buf[i]=='\b' && i>=1){
                    int j = 0;
                    for(j=i+1;j<s;++j)
                        buf[j-2] = buf[j];
                    buf[j] = '\0';
                    i--;
                }
                else if(buf[i]=='\b' && i==0){
                    int j = 0;
                    for(j=1; j<s; ++j)
                        buf[j-1] = buf[j];
                    buf[j] = '\0';
                }
                else if(buf[i]=='\0')
					break;
				else	
                    continue;
            }
        }
        else
            continue;

        // 把start指针指向的命令字符串按空格分割成多个参数给myargv
        char *start = buf;
        int i = 1;
        char *myargv[10] = {0};
        myargv[0] = start;
        while(*start){
            if(isspace(*start)){
				*start = '\0';
				// 有时候参数间有多个空格，必须保证参数指针指向位置为非空格
                if(isspace(*(++start))==0)
                	myargv[i++] = start;
            }
            else
                ++start;
        }
        myargv[i] = NULL;
		
		/*
		printf("test the params:\n");
		for(i=i-1;i>=0;i--){
			printf("%s\n",myargv[i]);
		}
		*/


        // 1）在父进程中，fork返回新创建子进程的进程ID；
        // 2）在子进程中，fork返回0；
        // 3）如果出现错误，fork返回一个负值；
        int id = fork();
        if(id==0){
            // execvp()会从PATH环境变量所指的目录中查找符合参数file("./head.out")的文件名, 找到后便执行该文件
            // 然后将第二个参数argv传给该欲执行的文件。
            // 如果执行成功则函数不会返回, 执行失败则直接返回-1, 失败原因存于errno 中.
            if(strcmp(myargv[0],"head")==0)
                execvp("./head.out",myargv);
			else if(strcmp(myargv[0],"cd")==0)
                execvp("./cd.out",myargv);
            else if(strcmp(myargv[0],"cp")==0)
                execvp("./cp.out",myargv);
            else if(strcmp(myargv[0],"ls")==0)
                execvp("./ls.out",myargv);
            else if(strcmp(myargv[0],"pwd")==0)
                execvp("./pwd.out",myargv);
            else if(strcmp(myargv[0],"mv")==0)
                execvp("./mv.out",myargv);
            else if(strcmp(myargv[0],"rm")==0)
                execvp("./rm.out",myargv);
            else if(strcmp(myargv[0],"rmdir")==0)
                execvp("./rmdir.out",myargv);
            else if(strcmp(myargv[0],"cat")==0)
                execvp("./cat.out",myargv);
            else if(strcmp(myargv[0],"clear")==0)
                execvp("./clear.out",myargv);
            else if(strcmp(myargv[0],"whoami")==0)
                execvp("./whoami.out",myargv);
            else if(strcmp(myargv[0],"echo")==0)
                execvp("./echo.out",myargv);
            else
                printf("Sorry, i haven't implement this commad you enter yet.\n");

            // 子进程执行玩成后结束进程，只保留一个父进程循环执行命令
            exit(1);
        }
        else{
            // shell命令是逐条执行到
            // fork()创立不了子进程可能是因为内存不够，则继续执行下一个命令时也无法创建子进程
            // 为确保资源，要阻塞等待当前所有子进程完成
            // wait()会暂时停止目前进程的执行, 直到有信号来到或子进程结束.
            // 如果不在意结束状态值, 则参数 int *status 可以设成NULL
            wait(NULL);
        }
    }
    return 0;
}

void printLoginName(){
    struct passwd *pw;
    // struct passwd * getpwuid(uid_t uid);
    // 知道用户uid(user id)，用getpwuid获取用户相关信息。
    pw = getpwuid(getuid());
    printf("[%s@", pw->pw_name);
}

void printHostName(){
    char name[128];
    // 获取主机名到name中，第二个参数为缓冲区最大长度
    gethostname(name,sizeof(name)-1);
    printf("%s ",name);
}

void printDir(){
    char pwd[128];
    getcwd(pwd,sizeof(pwd));//返回的dir默认最后不带"/"

    int len = strlen(pwd);
    char *p = pwd + len -1;
    // 例如将C:\user\desktop最末尾的desktop提取为当前工作路径的根目录
    while(*p != '/' && len--)
        p--;
    p++;
    printf("%s]@",p);
}


/*
补充：
struct passwd {
   char *pw_name;                // 用户登录名 
   char *pw_passwd;              // 密码(加密后) 
   __uid_t pw_uid;               // 用户ID 
   __gid_t pw_gid;               // 组ID 
   char *pw_gecos;               // 详细用户名 
   char *pw_dir;                 // 用户目录 
   char *pw_shell;               // Shell程序名  
};
*/

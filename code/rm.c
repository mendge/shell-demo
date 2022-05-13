#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

// S_ISDIR 不仅能判断字符串是否是目录格式，还能判断该目录是否存在

void rm_dir(const char *dir);

// rm 能移除文件和目录
int main(int argc,char **argv)
{
    if(argc != 2){
        printf("params error.\n");
        exit(-1);
    }
    // stat赋值成功返回0，失败返回-1
    struct stat statbuf;
    if(stat(argv[1],&statbuf) < 0){
        //  void perror(const char *str) 把一个描述性错误消息输出到标准错误 stderr
        perror("open");
        exit(-1);
    }
	// 当参数为普通文件时
    if(!S_ISDIR(statbuf.st_mode)){
		if(access(argv[1],0) < 0){
			printf("there is no such file.\n");
			exit(-1);
		}
        char temp;
        printf("Do you really want to remove this file?(y/n)\n");
        scanf("%c",&temp);
        if(temp=='y')
            remove(argv[1]);
    }
    else
        rm_dir(argv[1]);
    return 0;
}

// 其实不递归也可以？
void rm_dir(const char *dir){
    
	char cmd;
	printf("Do you really want to remove this directory?(y/n).\n");
	scanf("%c",&cmd);
	if(cmd!='y')
		exit(-1);

	// 打开指定目录，返回目录流（DIR*）
    DIR *fdir = opendir(dir);
    // 进入当前目录中
    chdir(dir);

    struct dirent *dirbuf;
    // readdir返回值为目录流fdir的下个目录进入点的dirent
    dirbuf = readdir(fdir);
    while(dirbuf!=NULL){
        // 如果当前类型是一个目录  才  递归调用rm_dir删除其  子  目录
        if(dirbuf->d_type == DT_DIR){
            if(strcmp(dirbuf->d_name,"..")&&strcmp(dirbuf->d_name,"."))
                rm_dir(dirbuf->d_name);
        }
        remove(dirbuf->d_name);
        dirbuf = readdir(fdir);
    }
    // 回到父目录在删除其子目录
    // 在当前目录删除当前目录还处于当前目录，但是该目录已不存在
    chdir("..");
    remove(dir);
}

/*
补充：为了获取某文件夹目录内容所使用的结构体
dirent{
    long d_ino; // 索引节点号 
    off_t d_off; // 在目录文件中的偏移 
    unsigned short d_reclen; // 文件名长 
    unsigned char d_type; // 文件类型 
    char d_name [NAME_MAX+1]; //  文件名，最长256字符 
}
*/

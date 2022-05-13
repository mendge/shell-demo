#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

void cd(char *path){
    struct stat* statbuf = (struct stat*)malloc(sizeof(statbuf));
    stat(path,statbuf);
    if(0==S_ISDIR(statbuf->st_mode)){
        printf("can not open dir: %s.\n",path);
        exit(-1);
    }
    //切换目录，可以是绝对路径或者相对路径
    chdir(path);
}

int main(int argc, char *argv[])
{
    if(argc!=2){
        printf("params error.\n");
        return -1;
    }
	else
    	cd(argv[1]);
    return 0;
}

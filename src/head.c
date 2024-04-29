#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define BUFFSIZE 512

// 部分函数使用参考：https://www.delftstack.com/zh/howto/c/optind-in-c/

int main(int argc, char **argv)
{
    char c;
    // 默认读取行数为5行
    int line = 5;
    char buffer[BUFFSIZE][BUFFSIZE];
    int count=0;
    // getopt是unistd.h中的函数，执行时会依次扫描每一个命令行参数，如果扫描完成就会返回-1
    // getopt函数用来解析命令行选项参数 前两个参数是从main直接传进来的，
    // 最后一个包含正确选项字符字符串，如果一个字符后面有冒号，那么在传递参数时就需要跟着一个参数
    while((c=getopt(argc,argv,"n:"))!=-1){
        // atoi是stdlib.h的函数，将保存的选项参数字符串转换成一个整数并返回结果
        // optarg保存的是选项参数，字符串形式
        int x = atoi(optarg);
        line = x;//获取命令行需要读取的行数
    }
    // optind是-n后第二给参数在argv的下标，因为optind从1开始
    char *path = argv[optind];
    FILE *fp;
    int index = 0;
    if(!(fp=fopen(path,"r"))){
        printf("can not open file: %s.\n",path);
        exit(-1);
    }
    // 
    while(!feof(fp)){
        count++;
        // 从指定的流fp读取一行，并把它存储在buffer[index]所指向的字符串内。
        // 当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
        fgets(buffer[index],BUFFSIZE,fp);
        index++;
    }
    fclose(fp);
    
    // 文件行数小于需要显示的行数时报错,count为已读出打最大行数。
    if(count<line)
        printf("the file doesn't have enough lines\n.");
    else{
        index = 0;
        int i =0;
        for(i=0;i<line;i++)
            printf("%s",buffer[index++]);
    }

    return 0;
}

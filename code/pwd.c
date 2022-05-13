#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define LENTH 255

int main()
{
    char path[LENTH];
    // getcwd()获取当前工作目录的绝对路径
    // 会将当前工作目录的绝对路径复制到参数path所指的内存空间中
    // 参数LENTH是path的空间大小
    puts(getcwd(path,LENTH));
    return 0;
}
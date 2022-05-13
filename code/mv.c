#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    FILE *fsrc = fopen(argv[1],"r");
    if(fsrc==NULL){
        perror("file no exist!\n");
        exit(-1);
    }
    else{
        // int stat(const char *file_name, struct stat *buf)
        // 通过文件名获取文件信息，并保存在buf所指的结构体statbuf中
        // 执行成功返回0，失败返回-1，作物代码存于errno
        struct stat *statbuf=(struct stat*)malloc(sizeof(statbuf));
        stat(argv[2],statbuf);
        // S_ISDIR判断目标路径是一个普通文件还是一个目录文件
        if(S_ISDIR(statbuf->st_mode)){
            int i,j,k=0;
            // 目标路径是一个目录，默认拷贝到一个名字和源文件相同的文件
            // 源路径最后一个"/"后的字符串就是源文件名
            // 找到就退出，保留其下标为i,找不到就代表源文件到标识符不带路径，i最后置0
            for(i=strlen(argv[1])-1;i>=0;i--)
                if(argv[1][i]=='/')
                    break;
            // 存储源文件名
            char source_file_name[128] = {};
            for(j=i+1;j<strlen(argv[1]);j++)
                source_file_name[k++] = argv[1][j];
            // 如果目标路径最后没有"/"就为其添上一个
            if(argv[2][strlen(argv[2])-1]!='/')
                strcat(argv[2],"/");
            FILE *fdest = fopen(strcat(argv[2],source_file_name),"w");
            // feof判断流是否到达文件末尾，返回0、1
            while(!feof(fsrc)){
                char buf[10] = {};
                fread(buf,1,10,fsrc);
                fwrite(buf,1,10,fdest);
            }
            fclose(fdest);
        }
        // 目标路径是文件，直接拷贝
        else{
            FILE *fdest = fopen(argv[2],"w+");
            while(!feof(fsrc)){
                char buf[10] ={};
                fread(buf,1,10,fsrc);
                fwrite(buf,1,10,fdest);
            }
            fclose(fdest);
        }
    }
    remove(argv[1]);
    fclose(fsrc);

    return 0;
}

/*
知识补充
struct stat{
mode_t st_mode; //文件对应的模式，文件，目录等
ino_t st_ino; //i-node节点号
dev_t st_dev; //文件所在设备的ID
dev_t st_rdev; //特殊设备号码
nlink_t st_nlink; //文件的连接数
uid_t st_uid; //文件所有者
gid_t st_gid; //文件所有者对应的组
off_t st_size; //普通文件，对应的文件字节数
time_t st_atime; //文件最后被访问的时间
time_t st_mtime; //文件内容最后被修改的时间
time_t st_ctime; //文件状态（属性）改变时间
blksize_t st_blksize; //文件内容对应的块大小
blkcnt_t st_blocks; //文件内容对应的块数量
};
*/

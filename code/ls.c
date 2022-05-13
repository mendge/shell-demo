#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<pwd.h>
#include<grp.h>
#include<sys/stat.h>
#include<string.h>

#define LS_NONE 0
#define LS_L 101
#define LS_R 102
#define LS_D 103
#define LS_A 200
#define LS_AL (LS_A + LS_L)

void mode_to_letters(int mode, char str[]);

char* uid_to_name(uid_t uid);

char* gid_to_name(gid_t gid);

void show_file_info(char* filename, struct stat* info_p);

void do_ls(char dirname[],int mode);

int analyzeParam(char *input);

int main(int argc,char **argv) {
    if (argc == 1) {
        // 只有一个参数ls，直接输出当前文件目名
        char filename[2] = {'.', '\0'};
        do_ls(filename, LS_NONE);
    }
    else{
        int mode = LS_NONE;
        int have_file_param = 0;

        while(argc > 1){
            argc--;
            argv++;
            // 如果能解析到模式参数模式合并（例：-l + -a = -al）
            int calMode = analyzeParam(*argv);
            if(calMode!=-1)
                mode += calMode;
            // 否则代表遇到路径名参数，每遇到一个则按照对应模式输出文件列表
            else{
                have_file_param = 1;
                do{
                    printf("%s:\n",*argv);
                    do_ls(*argv,mode);
                    printf("\n");

                    argc--;
                    argv++;
                }while(argc>=1);
            }
        }
        // 只有ls 和 -a等参数但是没有路径名，则按默认模式默认打印当前目录的文件
        if(!have_file_param)
            do_ls(".",mode);
    }
    return 0;
}

// 利用文件mode获取到文件的权限，将权限字串赋予传入的的str
void mode_to_letters(int mode, char str[]){
    strcpy(str,"----------");
    // 第1个字母，文件的类型
    if(S_ISDIR(mode))
        str[0] = 'd';
    else if(S_ISCHR(mode))
        str[0] = 'c';
    else if(S_ISBLK(mode))
        str[0] = 'b';
    // 第2~4位，表文件所属用户权限
    if((mode & S_IRUSR))
        str[1] = 'r';
    if((mode & S_IWUSR))
        str[2] = 'w';
    if((mode & S_IXUSR))
        str[3] = 'x';
    // 第5~7位，表文件所属组权限
    if((mode & S_IRGRP))
        str[4] = 'r';
    if((mode & S_IWGRP))
        str[5] = 'w';
    if((mode & S_IXGRP))
        str[6] = 'x';
    // 第8~10位，表其他用户对文件权限
    if((mode & S_IROTH))
        str[7] = 'r';
    if((mode & S_IWOTH))
        str[8] = 'w';
    if((mode & S_IXOTH))
        str[9] = 'x';
}

// uid_t 和 usigned int 相同
char* uid_to_name(uid_t uid){
    struct passwd *pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid))==NULL){
        // 格式化输出到number指向的字符串
        sprintf(numstr,"%d",uid);
        return numstr;
    }
    else   
        return pw_ptr->pw_name;
}
char* gid_to_name(gid_t gid){
    struct group *getgrgid(),*grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid))==NULL){
        sprintf(numstr,"%d",gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}

void show_file_info(char* filename, struct stat* info_p){
    char * uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p->st_mode, modestr);
    // 打印文件的用户权限信息
    printf("%s",modestr);
    // 打印文件硬链接数量
    printf("%4d",(int)info_p->st_nlink);
    // 打印文件用户名
    printf("%-8s",uid_to_name(info_p->st_uid));
    // 打印文件所属组名
    printf("%-8s",gid_to_name(info_p->st_gid));
    // 打印文件大小，字节为单位
    printf("%8ld",(long) info_p->st_size);
    // 打印文件最近修改时间
    printf("%.12s", 4 + ctime(&info_p->st_mtime));
    printf("%s\n",filename);
}

// 解析-l -a -al类的参数，返回对应模式，如果不对应模式则返回-1
int analyzeParam(char *input){
    if(strlen(input)==2 && input[0]=='-'){
        if(input[1]=='l')   return LS_L;
        if(input[1]=='a')   return LS_A;
        if(input[1]=='d')   return LS_D;
        if(input[1]=='R')   return LS_R;
    }
    else if(strlen(input)==3 && input[0]=='-')
        if(input[1]=='a' && input[2]=='l')  return LS_AL;
    return -1;
}


void do_ls(char dirname[],int mode){
    DIR *dir_ptr;
    struct dirent *direntbuf;
    if((dir_ptr = opendir(dirname))==NULL){
        fprintf(stderr,"ls2: cannot open %s.\n",dirname);
        exit(-1);
    }
    else{
        // LS_D对应的模式是直接打印当前目录名？？？
        if(mode==LS_D)
            printf("%s\n",dirname);
        else{
            // 不断从目录流中读入目录
            // readdir成功则返回指向要读目录的dirent结构体指针，否则返回NULL
            while((direntbuf = readdir(dir_ptr))!=NULL){

                // 拼接当前目录文件的父目录名和自己的目录名，形成相对完整的目录名
                char complete_dir_name[200];
                strcpy(complete_dir_name, dirname);
                strcat(complete_dir_name, "/");
                strcat(complete_dir_name, direntbuf->d_name);


                // 读入文件（普通文件和目录文件都有可能）的信息到info（stat结构体）中
                struct stat info;
                if(stat(complete_dir_name,&info)==-1){
                    perror(complete_dir_name);
                    printf("error.\n");
                    exit(-1);
                }
                // 读入成功则对应模式输出文件列表信息
                else{
                    // 特别注意比较不能直接比较dirent->dt_name和"."，这是指向两个完全不同地址的指针不可能相等，要用strcmp()
                    // debug了一下午，泪

                    // 这两种模式，打印的需要有文件的相关信息
                    if(mode==LS_L && strcmp(direntbuf->d_name,".")!=0 && strcmp(direntbuf->d_name,"..")!=0)
                        show_file_info(direntbuf->d_name,&info);
                    else if(mode==LS_AL)
                        show_file_info(direntbuf->d_name,&info);
                    // 这两种模式，只需要打印文件名
                    else if(mode==LS_A)
                        printf("%s\n",direntbuf->d_name);
                    else if(mode==LS_NONE && strcmp(direntbuf->d_name,".")!=0 && strcmp(direntbuf->d_name,"..")!=0)
                        printf("%s\n",direntbuf->d_name);
                    // 该模式，打印文件名，当是目录文件时还要打印其目录里的文件名
                    else if(mode==LS_R && strcmp(direntbuf->d_name,".") && strcmp(direntbuf->d_name,"..")){
                        // 是文件目录时,递归打印
                        if(S_ISDIR(info.st_mode))
                            do_ls(complete_dir_name,LS_R);
						else
                        	printf("%s%s\n",complete_dir_name,direntbuf->d_name);
                    }
                }
            }
        }
    }
    closedir(dir_ptr);
}

#include<stdio.h>
#include<stdlib.h>
#include<pwd.h>
#include<unistd.h>
#include<sys/types.h>

int main(int ac,char **av)
{
    struct passwd *pw;
    pw = getpwuid(getuid());
    if(pw==NULL){
        perror(*av);
        exit(-1);
    }
    printf("%s\n",pw->pw_name);
    return 0;
}

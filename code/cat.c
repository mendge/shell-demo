#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	// 两个参数时打印文件内容
    if(argc == 2){
        FILE *fp;
        if(!(fp = fopen(argv[1], "r"))){
            fprintf(stderr,"cannot open file :%s.\n",argv[1]);
            exit(-1);
        }
        int c;
        while((c=fgetc(fp)) != EOF){
            fputc(c,stdout);
        }
        fclose(fp);
    }

   // 四个参数时，将源文件打印到目的文件中
   // > 覆盖式打印      >> 追加式打印 
    else if(argc == 4){
        FILE *src;
        FILE *dest;
        if( !(src = fopen(argv[1], "r"))){
            fprintf(stderr,"%s: cannot open file %s\n", argv[0], argv[1]);
            exit(-1);
        }
        if(argv[2] == ">"){
            if(!(dest = fopen(argv[3],"w+"))){
                fprintf(stderr,"%s: cannot open file %s\n",argv[0],argv[3]);
                exit(-1);
            }
            int c;
            while((c = fgetc(src)!=EOF)){
                fputc(c,dest);
            }
        }
        else if(argv[2]==">>"){
            if(!(dest = fopen(argv[3],"a"))){
               fprintf(stderr,"%s: cannot open file %s\n",argv[0],argv[3]);
               exit(-1);
            }
            int c;
            while((c=fgetc(src))!=EOF){
                fputc(c,dest);
            }
        }
        fclose(src);
        fclose(dest);
    }
    return 0;

}

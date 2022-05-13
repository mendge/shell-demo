#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=3){
        printf("params error.\n");
        exit(-1);
    }
    FILE *rfp = fopen(argv[1], "r");
    FILE *wfp = fopen(argv[2], "w");

    int ret;
    char a[1024*4];
    while(1){
        //fread从给定流rfp读入sizeof(a)字节到a指向的数组中，读入最小单位为1
        ret = fread(a,1,sizeof(a),rfp);
        if(ret==0)
            break;
        // 同理fwrite将数组a写到文件中去
        fwrite(a,1,ret,wfp);
    }

    fclose(rfp);
    fclose(wfp);
    return 0;
}

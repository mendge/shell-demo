#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void delquomark(char *s);

int main(int argc, char *argv[])
{
	if(1==argc)
		printf("\n");
	else if(2==argc){
		delquomark(argv[1]);
		printf("%s\n",argv[1]);
	}
	else{
		int i;
		for(i=1;i<argc;){
			printf("%s",argv[i++]);
			if(i!=argc)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}

// 删除字符数组首尾的单/双引号
void delquomark(char *s){
	int len = strlen(s);
	int tail = len - 1;
	if(len==0 || len==1)
		return;
	if((s[0]=='\'' && s[tail]=='\'') || (s[0]=='\"' && s[tail]=='\"')){
		s++;
		s[tail] = '\0';
	}

}

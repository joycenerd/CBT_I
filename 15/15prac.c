#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;


FILE *fout;

void recur(char *str){
	ui len=strlen(str);
	int i;
	int num=0;
	for(i=0;i<len;i++) num+=str[i]-'0';
	if(num<10) fprintf(fout,"%d\n",num);
	else{
		char str[N];
		sprintf(str,"%d",num);
		recur(str);
	}  
}

int main()
{
	FILE *fin=fopen("15input-3.txt","r");
	fout=fopen("15result.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	fclose(fin);
	recur(l);
	fclose(fout);
	return 0;
}
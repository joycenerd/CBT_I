#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;

typedef struct{
	char data;
}Stack;

int main()
{
	FILE *fin=fopen("19input-2.txt","r");
	FILE *fout=fopen("19result.txt","w");
	assert(fin!=NULL);
	int spl;
	char l[N];
	fscanf(fin,"%d %s",&spl,l);
	ui len=strlen(l);
	spl%=len;
	int i=0;
	Stack stack[N];
	while(i<len){
		int count=spl;
		int top=-1;
		while(count--) stack[++top].data=l[i++];
		while(top!=-1) fprintf(fout,"%c",stack[top--].data);
	}
	fprintf(fout,"\n");
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;


typedef struct stacknode *stackptr;
typedef struct stacknode{
	char data[N];
	stackptr link;
}Node;


int main()
{
	FILE *fin=fopen("7input.txt","r");
	FILE *fout=fopen("7result.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	ui len=strlen(l);
	int i;
	char rev[N];
	for(i=0;i<len;i++) rev[i]=l[len-i-1];
	stackptr top=NULL;
	for(i=0;i<len;i++){
		if(isalpha(rev[i])){
			stackptr node=malloc(sizeof(Node));
			strncpy(node->data,rev+i,1);
			node->link=top;
			top=node;
		}
		else if(rev[i]=='+' || rev[i]=='-' || rev[i]=='*' || rev[i]=='/'){
			char *token=rev+i;
			char op1[N]="\0", op2[N]="\0",str[N]="\0";
			strcpy(op1,top->data);
			top=top->link;
			strcpy(op2,top->data);
			top=top->link;
			strcpy(str,op1);
			strcat(str,op2);
			strncat(str,token,1);
			stackptr node=malloc(sizeof(Node));
			strcpy(node->data,str);
			node->link=top;
			top=node;
		}
	}
	char ins[N];
	strcpy(ins,top->data);
	len=strlen(ins);
	for(i=0;i<len;i++) fprintf(fout,"%c ",ins[i]);
	fprintf(fout,"\n");
	int count=0;
	for(i=0;i<len;i++){
		if(isalpha(ins[i])) count++;
		else count--;
		fprintf(fout,"%d ",count);
	}
	fprintf(fout,"\n");
	return 0;
}
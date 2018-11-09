#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define N 200
typedef unsigned long int ui;


typedef struct stacknode *stackptr;
typedef struct stacknode{
	char data[N];
	stackptr link;
}Stack;

int main()
{
	FILE *fin=fopen("7input.txt","r");
	assert(fin!=NULL);
	Stack stack[N];
	char l[N],rev[N];
	fgets(l,N,fin);
	fclose(fin);
	FILE *fout=fopen("7result.txt","w");
	ui len=strlen(l);
	int i;
	for(i=0;i<len;i++) rev[i]=l[len-i-1];
	stackptr top=NULL;
	for(i=0;i<len;i++){
		char op1[N]="\0", op2[N]="\0";
		if(isalpha(rev[i])){
			stackptr node=malloc(sizeof(Stack));
			strncpy(node->data,rev+i,1);
			node->link=top;
			top=node;
		}
		else if(rev[i]=='+' || rev[i]=='-' || rev[i]=='*' || rev[i]=='/'){
			char *token=rev+i;
			strcpy(op1,top->data);
			top=top->link;
			strcpy(op2,top->data);
			top=top->link;
			char str[N]="\0";
			strcpy(str,op1);
			strcat(str,op2);
			strncat(str,token,1);
			stackptr node=malloc(sizeof(Stack));
			strcpy(node->data,str);
			node->link=top;
			top=node;
		}
	}
	fprintf(fout,"%s\n",top->data);
	char ins[N];
	strcpy(ins,top->data);
	int count=0;
	len=strlen(ins);
	for(i=0;i<len;i++){
		if(isalpha(ins[i])) count++;
		else count--;
		fprintf(fout,"%d ",count);
	}
	fprintf(fout,"\n");
	return 0;
}
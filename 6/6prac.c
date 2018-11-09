#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define N 1010
typedef unsigned long int ui;


typedef struct{
	char oper;
}Stack;

int Dist(char c){
	if(c=='+' || c=='-') return 1;
	else if(c=='*' || c=='/') return 2;
}

int main()
{
	FILE *fin=fopen("6input-2.txt","r");
	FILE *fout=fopen("6result.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	ui len=strlen(l);
	int i;
	Stack stack[N];
	int top=-1;
	int maxi=0;
	for(i=0;i<len;i++){
		if(isalpha(l[i])) fprintf(fout,"%c ",l[i]);
		else if(l[i]=='+' || l[i]=='-'  || l[i]=='*' || l[i]=='/'){
			if(top==-1) stack[++top].oper=l[i];
			else{
				while(Dist(l[i])<=Dist(stack[top].oper) && top!=-1) fprintf(fout,"%c ",stack[top--].oper);
				stack[++top].oper=l[i];
			}
			if(top+1>maxi) maxi=top+1;
		}
	}
	while(top!=-1) fprintf(fout,"%c ",stack[top--].oper);
	fprintf(fout,"\n");
	fprintf(fout,"%d\n",maxi);
	fclose(fin);
	fclose(fout);
	return 0;
}
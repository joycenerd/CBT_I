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

int dist(char c){
	if(c=='+') return 1;
	else if(c=='-') return 1;
	else if(c=='*') return 2;
	else if(c=='/') return 2;
}

int main()
{
	FILE *fin=fopen("6input-2.txt","r");
	assert(fin!=NULL);
	char l[N];
	Stack stack[N];
	int top=-1;
	int maxi=0;
	FILE *fout=fopen("6result.txt","w");
	while(!feof(fin)){
		fgets(l,N,fin);
		ui len=strlen(l);
		int i;
		for(i=0;i<len;i++){
			if(isalpha(l[i])) fprintf(fout,"%c ",l[i]);
			else if(l[i]=='+' || l[i]=='-' || l[i]=='*' || l[i]=='/'){
				if(top==-1) stack[++top].oper=l[i];
				else{
					while(dist(stack[top].oper)>=dist(l[i]) && top!=-1) fprintf(fout,"%c ",stack[top--].oper);
					stack[++top].oper=l[i];
				}
				if(top+1>maxi) maxi=top+1; 
			}
		}
	}
	fclose(fin);
	while(top!=-1) fprintf(fout,"%c ",stack[top--].oper);
	fprintf(fout,"\n");
	fprintf(fout,"%d\n",maxi);
	fclose(fout);
	return 0;
}
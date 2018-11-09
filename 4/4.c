#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define N 1010


typedef struct stacknode *stackptr;
typedef struct stacknode{
	int data;
	stackptr link;
}Stack;

int main()
{
	FILE *fin=fopen("4input.txt","r");
	assert(fin!=NULL);
	char ins[N];
	int num;
	stackptr top=NULL;
	while(!feof(fin)){
		fscanf(fin,"%s",ins);
		if(strncmp(ins,"Push",4)==0){
			fscanf(fin,"%d",&num);
			stackptr node=malloc(sizeof(Stack));
			node->data=num;
			node->link=top;
			top=node;
		}
		else if(strncmp(ins,"Pop",3)==0){
			stackptr tmp=top;
			top=top->link;
			free(tmp);
		}
	}
	fclose(fin);
	FILE *fout=fopen("4result.txt","w");
	stackptr cur=NULL,trail;
	int count=0;
	while(top){
		count++;
		trail=cur;
		cur=top;
		top=top->link;
		cur->link=trail;
	}
	fprintf(fout,"%d\n",count);
	while(cur){
		fprintf(fout,"%d ",cur->data);
		cur=cur->link;
	}
	fprintf(fout,"\n");
	fclose(fout);
	return 0;
}
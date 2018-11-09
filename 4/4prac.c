#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 1010


typedef struct stacknode *stackptr;
typedef struct stacknode{
	int data;
	stackptr link;
}Node;

int main()
{
	FILE *fin=fopen("4input.txt","r");
	FILE *fout=fopen("4result.txt","w");
	assert(fin!=NULL);
	char ins[N];
	stackptr top=NULL;
	while(!feof(fin)){
		fscanf(fin,"%s",ins);
		if(strncmp(ins,"Push",4)==0){
			int num;
			fscanf(fin,"%d",&num);
			stackptr node=malloc(sizeof(Node));
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
	fclose(fin);
	fclose(fout);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define N 500
typedef unsigned long int ui;


typedef struct listnode *listptr;
typedef struct listnode{
	char name[N];
	int mark;
	listptr link;
}List;

int main()
{
	FILE *fin=fopen("16input.txt","r");
	FILE *fout=fopen("16result.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	ui len=strlen(l);
	strncpy(l+len-2,"\0",1);
	char *token;
	listptr head=NULL,ptr;
	int num=0;
	token=strtok(l,",\0");
	while(token!=NULL){
		num++;
		listptr node=malloc(sizeof(List));
		strcpy(node->name,token);
		node->mark=0;
		if(!head){
			head=node;
			ptr=node;
			ptr->link=head;
		}
		else{
			node->link=head;
			ptr->link=node;
			ptr=node;
		}
		token=strtok(NULL,",\0");
	}
	int skip;
	fscanf(fin,"%d",&skip);
	fclose(fin);
	int k=1,count=0;
	while(count<num-1){
		while(k<skip){
			head=head->link;
			if(!head->mark) k++;
		}
		fprintf(fout,"%s is killed\n",head->name);
		head->mark=1;
		k=0;
		count++;
	}
	while(head){
		if(!head->mark){
			fprintf(fout,"%s is survived\n",head->name);
			break;
		}
		head=head->link;
	}
	fclose(fout);
	return 0;
}
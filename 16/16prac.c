#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 200
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
	FILE *fout=fopen("16output.txt","w");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	//printf("%s",l);
	ui len=strlen(l);
	strncpy(l+len-2,"\0",1);
	char *token=strtok(l,",\0");
	int num=0;
	listptr head=NULL,ptr;
	while(token!=NULL){
		num++;
		listptr node=malloc(sizeof(List));
		strcpy(node->name,token);
		node->mark=0;
		if(!head){
			head=node;
			ptr=node;
			node->link=head;
		}
		else{
			ptr->link=node;
			ptr=node;
			ptr->link=head;
		}
		token=strtok(NULL,",\0");
	}
	int skip;
	fscanf(fin,"%d",&skip);
	fclose(fin);
	int count=0;
	int k=1;
	while(count<num-1){
		while(k<skip){
			head=head->link;
			if(!head->mark) k++;
		}
		fprintf(fout,"%s is killed\n",head->name);
		head->mark=1;
		count++; k=0;
	}
	while(head){
		if(!head->mark){
			fprintf(fout,"%s is survived\n",head->name);
			break;
		}
		head=head->link;
	}
	return 0;
}
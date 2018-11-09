#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 1010
typedef unsigned long int ui;

typedef struct listnode *listptr;
typedef struct listnode {
	int num;
	listptr link;
} List;

int main()
{
	listptr ptr,head=NULL;
	FILE *fin=fopen("3input.txt","r");
	assert(fin!=NULL);
	char l[N];
	fgets(l,N,fin);
	char *token;
	token=strtok(l," \0");
	int count=0;
	while(token!=NULL){
		count++;
		listptr node=malloc(sizeof(List));
		node->num=atoi(token);
		node->link=NULL;
		if(head==NULL) head=node;
		else ptr->link=node;
		ptr=node;
		token=strtok(NULL," \0");
	}
	int bl=count/3;
	int sec;
	int i;
	while(!feof(fin)){
		fscanf(fin,"%d",&sec);
		int find=(sec-1)*bl;
		listptr tmp=head;
		while(find && --find) tmp=tmp->link;
		
}

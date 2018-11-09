#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;

typedef struct treenode *treeptr;
typedef struct treenode {
	int data;
	treeptr lchild;
	treeptr rchild;
} Tree;

treeptr ptr, head = NULL;

void delete(int num){
	treeptr find=NULL,parent=NULL;
	ptr=head;
	while(ptr){
		if(num<ptr->data){
			parent=ptr;
			ptr=ptr->lchild;
		}
		else if(num>ptr->data){
			parent=ptr;
			ptr=ptr->rchild;
		}
		else{
			find=ptr;
			break;
		}
	}
	if(find){
		treeptr tmp=find;
		if(tmp->lchild==NULL){
			if(parent==NULL) head=head->rchild;
			else if(parent->lchild==tmp) parent->lchild=tmp->rchild;
			else if(parent->rchild==tmp) parent->rchild=tmp->rchild;
		}
		else{
			tmp=tmp->lchild;
			while(tmp->rchild) tmp=tmp->rchild;
			find->data=tmp->data;
			tmp=NULL;
		}
	}
}

void insert(int num) {
	treeptr node = malloc(sizeof(Tree));
	node->data = num;
	node->lchild = node->rchild = NULL;
	if (!head) head = node;
	else {
		ptr = head;
		while (ptr) {
			if (node->data < ptr->data) {
				if (ptr->lchild == NULL) {
					ptr->lchild = node;
					break;
				}
				else ptr=ptr->lchild;
			}
			else if(node->data>ptr->data){
				if(ptr->rchild==NULL){
					ptr->rchild=node;
					break;
				}
				else ptr=ptr->rchild;
			}
		}
	}
}

int main()
{
	FILE *fin = fopen("10input.txt", "r");
	FILE *fout=fopen("10result.txt","w");
	assert(fin != NULL);
	char l[N];
	fgets(l, N, fin);
	char *token = strtok(l, " \0");
	while (token != NULL) {
		int num = atoi(token);
		insert(num);
		token = strtok(NULL, " \0");
	}
	while(!feof(fin)){
		fgets(l,N,fin);
		if(strncmp(l,"insert",6)==0) insert(atoi(l+7));
		else if(strncmp(l,"delete",6)==0) delete(atoi(l+7));
	}
	fclose(fin);
	treeptr que[N];
	int front=-1,rear=-1;
	que[++rear]=head;
	while(front!=rear){
		treeptr pop=que[++front];
		fprintf(fout,"%d ",pop->data);
		if(pop->lchild) que[++rear]=pop->lchild;
		if(pop->rchild) que[++rear]=pop->rchild;
	}
	fprintf(fout,"\n");
	return 0;
}
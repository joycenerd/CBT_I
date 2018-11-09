#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 1010


typedef struct treenode *treeptr;
typedef struct treenode {
	int data;
	treeptr lchild;
	treeptr rchild;
} Tree;
treeptr ptr, head = NULL;

void delete(int num){
	ptr=head;
	treeptr find=NULL;
	treeptr parent=NULL;
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
			if(parent->rchild==tmp) parent->rchild=tmp->rchild;
			else if(parent->lchild==tmp) parent->lchild=tmp->rchild;
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
	node->rchild = node->lchild = NULL;
	if (!head) head = node;
	else {
		ptr = head;
		while (ptr) {
			if (node->data < ptr->data) {
				if (ptr->lchild == NULL) {
					ptr->lchild = node;
					break;
				}
				else ptr = ptr->lchild;
			}
			else if (node->data > ptr->data) {
				if (ptr->rchild == NULL) {
					ptr->rchild = node;
					break;
				}
				else ptr = ptr->rchild;
			}
		}
	}
}


int main() {
	FILE *fin = fopen("10input.txt", "r");
	FILE *fout=fopen("10result.txt","w");
	assert(fin != NULL);
	char l[N];
	fgets(l, N, fin);
	char *token;
	token = strtok(l, " \0");
	int num;
	while (token != NULL) {
		num = atoi(token);
		insert(num);
		token = strtok(NULL, " \0");
	}
	while(!feof(fin)){
		fgets(l,N,fin);
		if(strncmp(l,"insert",6)==0){
			num=atoi(l+7);
			insert(num);
		}
		else if(strncmp(l,"delete",6)==0){
			num=atoi(l+7);
			delete(num);
		}
	}
	treeptr que[200];
	int front=-1, rear=-1;
	que[++rear]=head;
	while(front!=rear){
		treeptr pop=que[++front];
		fprintf(fout,"%d ",pop->data);
		if(pop->lchild) que[++rear]=pop->lchild;
		if(pop->rchild) que[++rear]=pop->rchild;
	}
	fprintf(fout,"\n");
}
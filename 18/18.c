#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define N 100010
typedef unsigned long int ui;


typedef struct listnode *listptr;
typedef struct listnode{
	char c;
	listptr rlink;
	listptr llink;
}Node;

int main()
{
	FILE *fin=fopen("18input.txt","r");
	FILE *fout=fopen("18result.txt","w");
	assert(fin!=NULL);
	char l[N];
	while(!feof(fin)){
		listptr head=NULL,ptr=NULL;
		fgets(l,N,fin);
		ui len=strlen(l);
		int i;
		for(i=0;i<len;i++){
			if(isalpha(l[i])){
				listptr node=malloc(sizeof(Node));
				node->c=l[i];
				node->rlink=NULL;
				node->llink=NULL;
				if(!head) head=node;
				else{
					ptr->rlink=node;
					node->llink=ptr;
				}
				ptr=node;
			}
		}
		ptr=head;
		while(1){
			fprintf(fout,"%c",ptr->c);
			if(ptr->rlink==NULL) break;
			else ptr=ptr->rlink;
		}
		char rep=ptr->c;
		while(ptr->c==rep && ptr) ptr=ptr->llink;
		while(ptr){
			fprintf(fout,"%c",ptr->c);
			ptr=ptr->llink;
		}
		fprintf(fout,"\n");
	}
	fclose(fin);
	fclose(fout);
	return 0;
}

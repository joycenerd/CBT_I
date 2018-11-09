#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


FILE *fout;

typedef struct treenode *treeptr;
typedef struct treenode {
	int data;
	treeptr lchild;
	treeptr rchild;
} Node;

void inorder(treeptr ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		fprintf(fout,"%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void postorder(treeptr ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		fprintf(fout,"%d ", ptr->data);
	}
}

void preorder(treeptr ptr) {
	if (ptr) {
		fprintf(fout,"%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

int main() {
	FILE *fin = fopen("9input.txt", "r");
	fout=fopen("9result.txt","w");
	assert(fin != NULL);
	treeptr head = NULL, ptr;
	while (!feof(fin)) {
		int num;
		fscanf(fin, "%d", &num);
		treeptr node = malloc(sizeof(Node));
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
	inorder(head);
	fprintf(fout,"\n");
	postorder(head);
	fprintf(fout,"\n");
	preorder(head);
	fprintf(fout,"\n");
}
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;


typedef struct {
	char data;
} Stack;

int main()
{
	FILE *fin = fopen("19input-1.txt", "r");
	FILE *fout = fopen("19result.txt", "w");
	assert(fin != NULL);
	char l[N];
	int n;
	fscanf(fin, "%d %s", &n, l);
	ui len = strlen(l);
	if (n > len) fprintf(fout,"%s\n", l);
	else {
		Stack stack[N];
		int i = 0;
		while (i < len) {
			int count = n;
			int top = -1;
			while (count--) {
				stack[++top].data = l[i];
				i++;
			}
			while (top != -1) fprintf(fout, "%c", stack[top--].data);
		}
	}
	fprintf(fout, "\n");
}
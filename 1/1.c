#include <stdio.h>
#include <assert.h>
#define N 1010


typedef struct {
	int row;
	int col;
	int data;
} Matrix;

int main()
{
	FILE *fin = fopen("1input.txt", "r");
	Matrix a[N], b[N];
	int n, m;
	int i, j;
	int data;
	while (!feof(fin)) {
		fscanf(fin, "%d %d", &n, &m);
		int i, j;
		int data;
		int count = 0;
		a[count].row = n; a[count].col = m;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				fscanf(fin, "%d", &data);
				if (data != 0) {
					count++;
					a[count].row = i;
					a[count].col = j;
					a[count].data = data;
				}
			}
		}
		a[0].data = count;
		count = 0;
		fscanf(fin, "%d %d", &n, &m);
		b[0].row = n; b[0].col = m;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				fscanf(fin, "%d", &data);
				if (data != 0) {
					count++;
					b[count].row = i;
					b[count].col = j;
					b[count].data = data;
				}
			}
		}
		b[0].data = count;
	}
	fclose(fin);
	FILE *fout=fopen("1result.txt","w");
	int rec[N] = {0}, start[N] = {0};
	for (i = 1; i <= b[0].data; i++) rec[b[i].col]++;
	start[0] = 1;
	for (i = 1; i <b[0].col; i++) start[i] = start[i - 1] + rec[i - 1];
	fprintf(fout,"Starting position for each column of b:\n");
	for(i=0;i<b[0].col;i++) fprintf(fout,"%d ",start[i]-1);
	fprintf(fout,"\n");
	Matrix tran[N];
	tran[0].row = b[0].col; tran[0].col = b[0].row; tran[0].data = b[0].data;
	for (i = 1; i <= tran[0].data; i++) {
		int cur = start[b[i].col]++;
		tran[cur].row = b[i].col;
		tran[cur].col = b[i].row;
		tran[cur].data = b[i].data;
	}
	Matrix c[N];
	int count = 0;
	for (i = 0; i < N; i++) c[i].data = 0;
	for (i = 1; i <= a[0].data; i++) {
		for (j = 1; j <= tran[0].data; j++) {
			if (a[i].col == tran[j].col) {
				int k = 1;
				while (k <= count) {
					if (c[k].row == a[i].row && c[k].col == tran[j].row) {
						c[k].data += a[i].data * tran[j].data;
						break;
					}
					k++;
				}
				if (k==count+1) {
					count++;
					c[count].row = a[i].row;
					c[count].col = tran[j].row;
					c[count].data = a[i].data * tran[j].data;
				}
			}
		}
	}
	c[0].row = a[0].row; c[0].col = tran[0].row; c[0].data = count;
	fprintf(fout,"A * B:\n");
	for (i = 0; i <= count; i++) fprintf(fout,"%d %d %d\n", c[i].row, c[i].col, c[i].data);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;


typedef struct{
	int row;
	int col;
	int data;
}Matrix;

int main()
{
	FILE *fin=fopen("1input.txt","r");
	FILE *fout=fopen("1result.txt","w");
	assert(fin!=NULL);
	int n,m;
	Matrix a[N],b[N],tran[N],c[N];
	fscanf(fin,"%d %d",&n,&m);
	int i,j;
	int num;
	int count=0;
	a[count].row=n;a[count].col=m;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fscanf(fin,"%d",&num);
			if(num!=0){
				a[++count].row=i;
				a[count].col=j;
				a[count].data=num;
			}
		}
	}
	a[0].data=count;
	fscanf(fin,"%d %d",&n,&m);
	count=0;
	b[count].row=n;b[count].col=m;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			fscanf(fin,"%d",&num);
			if(num!=0){
				b[++count].row=i;
				b[count].col=j;
				b[count].data=num;
			}
		}
	}
	b[0].data=count;
	int rec[N]={0},start[N];
	for(i=1;i<=b[0].data;i++) rec[b[i].col]++;
	start[0]=1;
	for(i=1;i<b[0].col;i++) start[i]=start[i-1]+rec[i-1];
	fprintf(fout,"Starting position for each column of B:\n");
	for(i=0;i<b[0].col;i++) fprintf(fout,"%d ",start[i]-1);
	fprintf(fout,"\n");
	tran[0].row=b[0].col;tran[0].col=b[0].row;tran[0].data=b[0].data;
	for(i=1;i<=b[0].data;i++){
		int cur=start[b[i].col]++;
		tran[cur].row=b[i].col;
		tran[cur].col=b[i].row;
		tran[cur].data=b[i].data;
	}
	count=0;
	c[count].row=a[0].row;c[count].col=tran[0].row;
	for(i=1;i<=a[0].data;i++){
		for(j=1;j<=tran[0].data;j++){
			if(a[i].col==tran[j].col){
				int k=1;
				while(k<=count){
					if(c[k].row==a[i].row && c[k].col==tran[j].row){
						c[k].data+=a[i].data*tran[j].data;
						break;
					}
					k++;
				}
				if(k==count+1){
					c[++count].row=a[i].row;
					c[count].col=tran[j].row;
					c[count].data=a[i].data*tran[j].data;
				}
			}
		}
	}
	c[0].data=count;
	fprintf(fout,"A * B:\n");
	for(i=0;i<=c[0].data;i++) fprintf(fout,"%d %d %d\n",c[i].row,c[i].col,c[i].data);
	return 0;
}
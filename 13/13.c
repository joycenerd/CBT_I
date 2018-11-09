#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 200


int maze[10][10];

typedef struct{
	int row;
	int col;
	int prevdir;
}Stack;
Stack stack[N];

typedef struct{
	int vert;
	int horiz;
}Dir;

int nextrow,nextcol;

int find(int top){
	Dir dir[5];
	dir[1].vert=0; dir[1].horiz=1;
	dir[2].vert=1; dir[2].horiz=0;
	dir[3].vert=0; dir[3].horiz=-1;
	dir[4].vert=-1; dir[4].horiz=0;
	int cur=stack[top].prevdir;
	if(cur+1==5) return cur+1;
	do{
		cur++;
		if(cur==5) break;
		nextrow=stack[top].row+dir[cur].vert;
		nextcol=stack[top].col+dir[cur].horiz;
	}while(maze[nextrow][nextcol]==1);
	return cur;
}

int main(){
	FILE *fin=fopen("13input.txt","r");
	FILE *fout=fopen("13result.txt","w");
	assert(fin!=NULL);
	int i,j;
	char l[N];
	for(i=0;i<10;i++){
		fgets(l,N,fin);
		for(j=0;j<10;j++) maze[i][j]=l[j]-'0';
	}
	fclose(fin);
	int top=-1;
	stack[++top].row=1;
	stack[top].col=1;
	stack[top].prevdir=0;
	while(top!=-1){
		if(stack[top].row==8 && stack[top].col==8) break;
		fprintf(fout,"(%d,%d),",stack[top].col,stack[top].row);
		int now=find(top);
		if(now==5) top--;
		else{
			stack[top].prevdir=now;
			stack[++top].row=nextrow;
			stack[top].col=nextcol;
			stack[top].prevdir=0;
			maze[nextrow][nextcol]=1;
		}
	}
	if(stack[top].row==8 && stack[top].col==8) fprintf(fout,"(%d,%d)\n",8,8);
	else fprintf(fout,"Not found\n");
	return 0;
}
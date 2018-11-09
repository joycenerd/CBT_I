#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 100
typedef unsigned long int ui;


typedef struct{
	int data;
}Stack[N];

Stack stack[N];

int main()
{
	FILE *fin=fopen("12input-2.txt","r");
	FILE *fout=fopen("12result.txt","w");
	assert(fin!=NULL);
	int a,b;
	int i;
	int len=0;
	int top[N];
	for(i=0;i<N;i++) top[i]=-1;
	while(!feof(fin)){
		fscanf(fin,"%d %d",&a,&b);
		if(a>len) len=a;
		if(b>len) len=b;
		stack[a][++top[a]].data=b;
		stack[b][++top[b]].data=a;
	}
	fclose(fin);
	Stack rec;
	int cur=-1;
	int out[N]={0};
	for(i=0;i<=len;i++){
		int arr[N]={0};
		if(out[i] || top[i]==-1) continue;
		rec[++cur].data=i;
		arr[i]=1;
		while(top[i]!=-1) rec[++cur].data=stack[i][top[i]--].data;
		out[i]=1;
		while(cur!=-1){
			int pop=rec[cur--].data;
			if(out[pop]) continue;
			arr[pop]=1;
			while(top[pop]!=-1) rec[++cur].data=stack[pop][top[pop]--].data;
			out[pop]=1;
		}
		for(int j=0;j<=len;j++){
			if(arr[j]) fprintf(fout,"%d ",j);
		}
		fprintf(fout,"\n");
	}
	return 0;
}
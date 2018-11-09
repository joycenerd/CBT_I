#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 100

typedef struct{
	int data;
}Stack[N];

Stack stack[N];

int main()
{
	FILE *fin=fopen("12input-2.txt","r");
	FILE *fout=fopen("12result.txt","w");
	assert(fin!=NULL);
	int top[N];
	int i;
	for(i=0;i<N;i++) top[i]=-1;
	int len=0;
	while(!feof(fin)){
		int a,b;
		fscanf(fin,"%d %d",&a,&b);
		if(a>len) len=a;
		if(b>len) len=b;
		stack[a][++top[a]].data=b;
		stack[b][++top[b]].data=a;
	}
	Stack rec;
	int cur=-1;
	int out[N]={0};
	for(i=0;i<=len;i++){
		if(out[i] || top[i]==-1) continue;
		int arr[N]={0};
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
		int j;
		for(j=0;j<=len;j++){
			if(arr[j]) fprintf(fout,"%d ",j);
		}
		fprintf(fout,"\n");
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define N 1010
typedef unsigned long int ui;


int main()
{
	FILE *fin=fopen("2input.txt","r");
	FILE *fout=fopen("2result.txt","w");
	assert(fin!=NULL);
	char l[N],str[N],pat[N];
	fgets(l,N,fin);
	char *token=strtok(l+4," \0");
	int count=0;
	while(token!=NULL){
		if(isalpha(*token)){
			strncpy(str+count,token,1);
			count++;
		}
		token=strtok(NULL," \0");
		//printf("yes\n");
	}
	fgets(l,N,fin);
	token=strtok(l+4," \0");
	count=0;
	while(token!=NULL){
		if(isalpha(*token)){
			strncpy(pat+count,token,1);
			count++;
		}
		token=strtok(NULL," \0");
	}
	ui lenp=strlen(pat);
	int fail[N];
	fail[0]=-1;
	int i,j;
	for(j=1;j<lenp;j++){
		i=fail[j-1];
		while(pat[j]!=pat[i+1] && i>=0) i=fail[i];
		if(pat[j]==pat[i+1]) fail[j]=i+1;
		else fail[j]=-1;
	}
	fprintf(fout,"F:");
	for(i=0;i<lenp;i++) fprintf(fout,"%d ",fail[i]);
	fprintf(fout,"\n");
	ui lens=strlen(str);
	i=0;j=0;
	while(i<lens && j<lenp){
		if(str[i]==pat[j]){
			i++;j++;
		}
		else if(j==0) i++;
		else j=fail[j-1]+1;
	}
	if(j==lenp) fprintf(fout,"Yes,%lu,%d\n",i-lenp,i-1);
	else fprintf(fout,"Not found\n");
	fclose(fin);
	fclose(fout);
	return 0;
}
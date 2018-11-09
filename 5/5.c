#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define N 1010
typedef unsigned long int ui;


typedef struct{
	char name[N];
	int day[8];
	int eval;
	char area[N];
}Table;

int main()
{
	FILE *fin=fopen("5input.txt","r");
	assert(fin!=NULL);
	char l[N];
	char *token[4];
	FILE *fout=fopen("5result.txt","w");
	int count=0;
	Table tab[20];
	int i;
	while(!feof(fin)){
		fgets(l,N,fin);
		int col=0;
		token[col]=strtok(l,",\r\n\0");
		strcpy(tab[count].name,token[0]);
		printf("%s\n",tab[count].name);
		while(token[col]!=NULL) token[++col]=strtok(NULL,",\r\n\0");
		ui len=strlen(token[1]);
		for(i=0;i<8;i++) tab[count].day[i]=0;
		for(i=0;i<len;i++){
			int open=token[1][i]-'0';
			tab[count].day[open]=1;
		}
		tab[count].eval=atoi(token[2]);
		strcpy(tab[count].area,token[3]);
		printf("%s",tab[count].area);
		count++;
	}
	fclose(fin);
	fprintf(fout,"評價最高的夜市：");
	int maxi=0;
	for(i=0;i<count;i++){
		if(tab[i].eval>tab[maxi].eval) maxi=i;
	}
	fprintf(fout,"%s\n",tab[maxi].name);
	fprintf(fout,"星期三有開的夜市：");
	for(i=0;i<count;i++){
		if(tab[i].day[3]==1) fprintf(fout,"%s,",tab[i].name);
	}
	fprintf(fout,"\n");
	fprintf(fout,"台中的夜市：");
	for(i=0;i<count;i++){
		if(strcmp(tab[i].area,"台中市")==0) fprintf(fout,"%s,",tab[i].name); 
	}
	fprintf(fout,"\n");
}
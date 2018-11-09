#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
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
	Table tab[20];
	int count=0;
	int i;
	while(!feof(fin)){
		fgets(l,N,fin);
		char *token[4];
		int col=0;
		token[col]=strtok(l,",\0");
		strcpy(tab[count].name,token[0]);
		//printf("%d ",count);
		//printf("%s\n",tab[count].name);
		while(token[col]!=NULL) token[++col]=strtok(NULL,",\0");
		ui len=strlen(token[1]);
		for(i=0;i<8;i++) tab[count].day[i]=0;
		for(i=0;i<len;i++){
			int open=token[1][i]-'0';
			tab[count].day[open]=1;
		} 
		tab[count].eval=atoi(token[2]);
		strncpy(tab[count].area,token[3],3);
		count++;
	}
	fclose(fin);
	printf("評價最高的夜市：");
	int maxi=0;
	for(i=0;i<count;i++){
		if(tab[i].eval>tab[maxi].eval) maxi=i;
	}
	//printf("%s\n",tab[0].name);
	printf("%s\n",tab[maxi].name);
	printf("星期三有開的夜市：");
	for(i=0;i<count;i++){
		if(tab[i].day[3]==1) printf("%s,",tab[i].name);
	}
	printf("\n");
	printf("台中的夜市：");
	for(i=0;i<count;i++){
		if(strcmp(tab[i].area,"台中市")==0) printf("%s,",tab[i].name);
	}
	printf("\n");
}

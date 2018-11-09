#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define N 1010
typedef unsigned long int ui;

int fail[N];

void lsp(char *pat) {
	fail[0] = 0;
	int i, j;
	ui len = strlen(pat);
	for (j = 1; j < len; j++) {
		i = fail[j - 1];
		while (pat[j] != pat[i + 1] && i > 0) i = fail[i];
		if (pat[j] == pat[i + 1]) fail[j] = i + 1;
		else fail[j] = 0;
	}
}

int main()
{
	FILE *fin = fopen("20input.txt", "r");
	FILE *fout=fopen("20result.txt","w");
	assert(fin != NULL);
	char pat[N], mainstr[N];
	int index = 0;
	while (!feof(fin)) {
		char l[N];
		fgets(l, N, fin);
		if (strncmp(l, "P:", 2) == 0) {
			strcpy(pat, l + 2);
			lsp(pat);
			break;
		}
		char *token = strtok(l, ",\0");
		char str[N] = "\0";
		if (token != NULL) {
			strncpy(str, mainstr, index);
			strcat(str, token);
			strcat(str, mainstr + index);
			strcpy(mainstr,str);
			token=strtok(NULL,",\0");
			index+=atoi(token);
		}
	}
	fprintf(fout,"Final string:%s\n",mainstr);
	int i=0,j=0;
	ui lens=strlen(mainstr);
	ui lenp=strlen(pat);
	while(i<lens && j<lenp){
		if(mainstr[i]==pat[j]){
			i++;j++;
		}
		else if(j==0) i++;
		else j=fail[j-1];
	}
	fprintf(fout,"last string:");
	if(j!=lenp) fprintf(fout,"%s\n",mainstr);
	else{
		int k;
		for(k=0;k<i-lenp;k++) fprintf(fout,"%c",mainstr[k]);
		fprintf(fout,"%s\n",mainstr+i);
	}
	fprintf(fout,"Lps{");
	for(i=0;i<lenp;i++){
		if(i==lenp-1) fprintf(fout,"%d}\n",fail[i]);
		else fprintf(fout,"%d,",fail[i]);
	}
	return 0;
}
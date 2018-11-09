#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define N 1010
typedef unsigned long int ui;


int main()
{
	FILE *fin = fopen("2input.txt", "r");
	assert(fin != NULL);
	char l[N];
	char str[N], pat[N];
	char *token;
	int count;
	while (!feof(fin)) {
		fgets(l, N, fin);
		count = 0;
		token = strtok(l + 4, " \0");
		while (token != NULL) {
			if (isalpha(*token)) {
				strncpy(str + count, token, 1);
				count++;
			}
			token = strtok(NULL, " \0");
		}
		fgets(l, N, fin);
		count = 0;
		token = strtok(l + 4, " \0");
		while (token != NULL) {
			if (isalpha(*token)) {
				strncpy(pat + count, token, 1);
				count++;
			}
			token = strtok(NULL, " \0");
		}
	}
	fclose(fin);
	FILE *fout=fopen("2result.txt","w");
	ui lenp = strlen(pat);
	int failure[N];
	failure[0] = -1;
	int i, j;
	for(j=1;j<lenp;j++){
		i=failure[j-1];
		while(pat[j]!=pat[i+1] && i>=0) i=failure[i];
		if(pat[j]==pat[i+1]) failure[j]=i+1;
		else failure[j]=-1;
	}
	fprintf(fout,"F: ");
	for (i = 0; i < lenp; i++) fprintf(fout,"%d ", failure[i]);
	fprintf(fout,"\n");
	i=0;j=0;
	ui lens=strlen(str);
	while(i<lens && j<lenp){
		if(str[i]==pat[j]){
			i++;j++;
		}
		else if(j==0) i++;
		else j=failure[j-1]+1;
	}
	if(j==lenp) fprintf(fout,"Yes,%lu,%d\n",i-lenp,i-1);
	else fprintf(fout,"Not found\n");
	fclose(fout);
	return 0;
}
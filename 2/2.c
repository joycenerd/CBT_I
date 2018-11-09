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
	//printf("%s\n",str);
	//printf("%s\n",pat);
	FILE *fout=fopen("2result.txt","w");
	char head = pat[0];
	ui lenp = strlen(pat);
	int failure[N];
	failure[0] = -1;
	int i, j;
	for (i = 1; i < lenp; i++) {
		if (failure[i - 1] == -1) {
			if (pat[i] == head) failure[i] = failure[i - 1] + 1;
			else failure[i] = -1;
			continue;
		}
		int j = i - 1;
		int index;
		while (j > 0) {
			if (failure[j] == 0) {
				index = j;
				break;
			}
			j--;
		}
		//printf("%d ",index);
		//printf("\n");
		if (failure[i - 1] == i - index - 1) {
			if (strncmp(pat, pat + index, i - index + 1) == 0) {
				failure[i] = failure[i - 1] + 1;
				continue;
			}
		}
		for (j = index + 1; j < i; j++) {
			if (pat[j] == head) {
				if (strncmp(pat, pat + j, i - j + 1)==0) {
					failure[i] = i - j;
					break;
				}
			}
		}
		if (j == i) {
			if (pat[i] == head) failure[i] = 0;
			else failure[i] = -1;
		}
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
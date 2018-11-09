#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int step=0;
FILE *fout;

void hanoi(int n, char A,char B,char C){
	if(n==1){
		step++;
		fprintf(fout,"Move sheet from %c to %c\n",A,C);
	}
	else{
		hanoi(n-1,A,C,B);
		hanoi(1,A,B,C);
		hanoi(n-1,B,A,C);
	}
}

int main()
{
	FILE *fin=fopen("17input.txt","r");
	fout=fopen("17result.txt","w");
	assert(fin!=NULL);
	int n;
	fscanf(fin,"%d",&n);
	fclose(fin);
	hanoi(n,'A','B','C');
	fprintf(fout,"%d\n",step);
	fclose(fout);
	return 0;
}
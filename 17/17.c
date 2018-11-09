#include <stdio.h>
#include <assert.h>

int step=0;
FILE *fout;

void hanoi(int n, char A, char B, char C) {
    if(n == 1) {
        step++;
        fprintf(fout,"Move sheet from %c to %c\n", A, C);
    }
    else {
        hanoi(n-1, A, C, B);    // 非最大(n-1)個A->B
        hanoi(1, A, B, C);  // 最大（1)A->C
        hanoi(n-1, B, A, C);    // 非最大(n-1)個B->C
    }
}

int main() {
    FILE *fin=fopen("17input.txt","r");
    fout=fopen("17result.txt","w");
    assert(fin!=NULL);
    int n;
    fscanf(fin,"%d", &n);
    hanoi(n, 'A', 'B', 'C');
    fprintf(fout,"%d\n",step);
    return 0;
} 
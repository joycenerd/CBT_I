#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
typedef unsigned long int ui;


int front = 0, rear = 0;
int que[6];
FILE *fout;

void enqueue(int num) {
	if (front == (rear + 1) % 6) fprintf(fout, "The queue is full, can't insert data\n");
	else {
		rear = (rear + 1) % 6;
		que[rear] = num;
	}
}

void dequeue() {
	if (front == rear) fprintf(fout, "The queue is empty, can't delete data\n");
	else front = (front + 1) % 6;
}

void display() {
	int tmp = front;
	if (front == rear) fprintf(fout, "The queue is empty\n");
	else {
		while (tmp < rear) {
			tmp = (tmp + 1) % 6;
			fprintf(fout, "%d ", que[tmp]);
		}
		fprintf(fout, "\n");
	}
}

int main()
{
	FILE *fin = fopen("8input.txt", "r");
	fout = fopen("8result.txt", "w");
	assert(fin != NULL);
	int choice, num;
	while (!feof(fin)) {
		fscanf(fin, "%d", &choice);
		if (choice == 1) {
			fscanf(fin, "%d", &num);
			enqueue(num);
		}
		else if (choice == 2) dequeue();
		else if (choice == 3) display();
	}
}
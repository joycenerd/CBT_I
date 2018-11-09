#include <stdio.h>
#include <assert.h>


FILE *fout;

int front=0,rear=0;
int que[6];

void enqueue(int num){
	if(front==(rear+1)%6) fprintf(fout,"The queue is full, you can't insert any data\n");
	else{
		rear=(rear+1)%6;
		que[rear]=num;
	}
}

void dequeue(){
	if(front==rear) fprintf(fout,"The queue is empty, you can't delete any data\n");
	else front=(front+1)%6;
}

void display(){
	int tmp=front;
	if(tmp==rear) fprintf(fout,"The queue is empty\n");
	else{
		do{
			tmp=(tmp+1)%6;
			fprintf(fout,"%d ",que[tmp]);
		}while(tmp!=rear);
		fprintf(fout,"\n");
	}
}

int main()
{
	FILE *fin=fopen("8input-2.txt","r");
	fout=fopen("8result.txt","w");
	assert(fin!=NULL);
	while(!feof(fin)){
		int choice;
		fscanf(fin,"%d",&choice);
		if(choice==1){
			int num;
			fscanf(fin,"%d",&num);
			enqueue(num);
		}
		else if(choice==2) dequeue();
		else if(choice==3) display();
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
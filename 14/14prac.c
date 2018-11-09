#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 1010


typedef struct polynode *polyptr;
typedef struct polynode{
	float coef;
	int exp;
	polyptr link;
}Node;


void print(polyptr ptr){
	ptr=ptr->link;
	printf("%.1fx^%d",ptr->coef,ptr->exp);
	ptr=ptr->link;
	while(ptr){
		if(ptr->coef<0.0) printf("%.1fx^%d",ptr->coef,ptr->exp);
		else if(ptr->coef>0.0) printf("+%.1fx^%d",ptr->coef,ptr->exp);
		ptr=ptr->link;
	}
	printf("\n");
}

polyptr attach(polyptr ptr,float coef,int exp){
	polyptr node=malloc(sizeof(Node));
	node->coef=coef;
	node->exp=exp;
	node->link=NULL;
	ptr->link=node;
	ptr=node;
	return ptr;
}

void add(polyptr a,polyptr b){
	polyptr c=malloc(sizeof(Node));
	c->link=NULL;
	polyptr head=c;
	a=a->link; b=b->link;
	while(a && b){
		if(a->exp==b->exp){
			c=attach(c,a->coef+b->coef,a->exp);
			a=a->link;b=b->link;
		}
		else if(a->exp>b->exp){
			c=attach(c,a->coef,a->exp);
			a=a->link;
		}
		else if(a->exp<b->exp){
			c=attach(c,b->coef,b->exp);
			b=b->link;
		}
	}
	while(a){
		c=attach(c,a->coef,a->exp);
		a=a->link;
	}
	while(b){
		c=attach(c,b->coef,b->exp);
		b=b->link;
	}
	printf("C(x)=");
	print(head);
}

void sub(polyptr a,polyptr b){
	polyptr d=malloc(sizeof(Node));
	d->link=NULL;
	polyptr head=d;
	a=a->link; b=b->link;
	while(a && b){
		if(a->exp==b->exp){
			d=attach(d,a->coef-b->coef,a->exp);
			a=a->link;b=b->link;
		}
		else if(a->exp>b->exp){
			d=attach(d,a->coef,a->exp);
			a=a->link;
		}
		else if(a->exp<b->exp){
			d=attach(d,-b->coef,b->exp);
			b=b->link;
		}
	}
	while(a){
		d=attach(d,a->coef,a->exp);
		a=a->link;
	}
	while(b){
		d=attach(d,-b->coef,b->exp);
		b=b->link;
	}
	printf("D(x)=");
	print(head);
}

void mult(polyptr a,polyptr b){
	polyptr e=malloc(sizeof(Node));
	e->exp=-1;
	e->link=NULL;
	polyptr heade=e;
	a=a->link;b=b->link;
	polyptr headb=b;
	while(a){
		b=headb;
		while(b){
			float coef=a->coef*b->coef;
			int exp=a->exp+b->exp;
			polyptr tmp=heade;
			while(tmp){
				if(tmp->exp==exp){
					tmp->coef+=coef;
					break;
				}
				tmp=tmp->link;
			}
			if(tmp==NULL) e=attach(e,coef,exp);
			b=b->link;
		}
		a=a->link;
	}
	printf("E(x)=");
	print(heade);
}

int main(){
	FILE *fin=fopen("14input.txt","r");
	assert(fin!=NULL);
	char l[N];
	polyptr a=malloc(sizeof(Node));
	a->link=NULL;
	polyptr heada=a;
	polyptr b=malloc(sizeof(Node));
	b->link=NULL;
	polyptr headb=b;
	float coef;
	int exp;
	while(fgets(l,N,fin) && l[0]!=':'){
		sscanf(l,"%f %d",&coef,&exp);
		a=attach(a,coef,exp);
	}
	printf("%f %d\n",a->coef,a->exp);
	printf("A(x)=");
	print(heada);
	while(fgets(l,N,fin)){
		sscanf(l,"%f %d",&coef,&exp);
		b=attach(b,coef,exp);
	}
	printf("%f %d\n",b->coef,b->exp);
	printf("B(x)=");
	print(headb);
	add(heada,headb);
	sub(heada,headb);
	mult(heada,headb);
}
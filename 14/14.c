#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 1010


typedef struct polynode *polyptr;
typedef struct polynode{
	float coef;
	int exp;
	polyptr link;
}Poly;
FILE *fout;

void printPoly(polyptr ptr){
	ptr=ptr->link;
	fprintf(fout,"%.1fx^%d",ptr->coef,ptr->exp);
	ptr=ptr->link;
	while(ptr){
		if(ptr->coef<0.000) fprintf(fout,"%.1fx^%d",ptr->coef,ptr->exp);
		else if(ptr->coef>0.000)fprintf(fout,"+%.1fx^%d",ptr->coef,ptr->exp);
		ptr=ptr->link;
	}
	fprintf(fout,"\n");
}

polyptr attach(polyptr ptr,float coef,int exp){
	polyptr node=malloc(sizeof(Poly));
	node->coef=coef;
	node->exp=exp;
	node->link=NULL;
	ptr->link=node;
	ptr=node;
	return ptr;
}

void polymul(polyptr a, polyptr b){
	polyptr headb=b->link;
	polyptr e=malloc(sizeof(Poly));
	e->coef=0;
	e->exp=-1;
	polyptr heade=e;
    a=a->link;
	while(a!=NULL){
		b=headb;
		while(b!=NULL){
			float coef=b->coef*a->coef;
			int exp=a->exp+b->exp;
			polyptr tmpe=heade;
			while(tmpe){
				if(tmpe->exp==exp){
					tmpe->coef+=coef;
					break;
				}
				tmpe=tmpe->link;
			}
			if(tmpe==NULL) e=attach(e,coef,exp);
			b=b->link;
		}
		a=a->link;
	}
	fprintf(fout,"E(x)=");
	printPoly(heade->link);
}

void polysub(polyptr a, polyptr b){
	a=a->link;
	b=b->link;
	polyptr d=malloc(sizeof(Poly));
	d->link=NULL;
	polyptr head=d;
	while(a!=NULL && b!=NULL){
		polyptr node=malloc(sizeof(Poly));
		if(a->exp==b->exp){
			float coef=a->coef-b->coef;
			d=attach(d,coef,a->exp);
			a=a->link;
			b=b->link;
		}
		else if(a->exp>b->exp){
			d=attach(d,a->coef,a->exp);
			a=a->link;
		}
		else{
			d=attach(d,-b->coef,b->exp);
			b=b->link;
		}
	}
	while(a!=NULL){
		d=attach(d,a->coef,a->exp);
		a=a->link;
	}
	while(b!=NULL){
		d=attach(d,-b->coef,b->exp);
		b=b->link;
	}
	fprintf(fout,"D(x)=");
	printPoly(head);
}

void polyadd(polyptr a, polyptr b){
	a=a->link;
	b=b->link;
	polyptr c=malloc(sizeof(Poly));
	c->link=NULL;
	polyptr head=c;
	while(a!=NULL && b!=NULL){
		polyptr node=malloc(sizeof(Poly));
		if(a->exp==b->exp){
			float coef=a->coef+b->coef;
			c=attach(c,coef,a->exp);
			a=a->link;
			b=b->link;
		}
		else if(a->exp>b->exp){
			c=attach(c,a->coef,a->exp);
			a=a->link;
		}
		else{
			c=attach(c,b->coef,b->exp);
			b=b->link;
		}
	}
	while(a!=NULL){
		c=attach(c,a->coef,a->exp);
		a=a->link;
	}
	while(b!=NULL){
		c=attach(c,b->coef,b->exp);
		b=b->link;
	}
	fprintf(fout,"C(x)=");
	printPoly(head);
}

int main()
{
	FILE *fin=fopen("14input.txt","r");
	fout=fopen("14result.txt","w");
	assert(fin!=NULL);
	polyptr polya=malloc(sizeof(Poly));
	polya->link=NULL;
	polyptr polyb=malloc(sizeof(Poly));
	polyb->link=NULL;
	polyptr heada=polya,headb=polyb;
	float coef;
	int exp;
	char l[N];
	while(fgets(l,N,fin) && l[0]!=':'){
		sscanf(l,"%f %d",&coef,&exp);
		polya=attach(polya,coef,exp);
	}
	fprintf(fout,"A(x)=");
	printPoly(heada);
	while(fgets(l,N,fin)){
		sscanf(l,"%f %d",&coef,&exp);
		polyb=attach(polyb,coef,exp);
	}
	fprintf(fout,"B(x)=");
	printPoly(headb);
	polyadd(heada,headb);
	polysub(heada,headb);
	polymul(heada,headb);
}

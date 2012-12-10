/*
 ============================================================================
 Name        : Operating.c
 Author      : Narender
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Node{   ///////////// Structure for First and Second Level Array

	struct Node_S *next;
};

struct Link{    //////////// Structure for Free Memory

int size;
int free;
struct Link *next;       //// Next Free Memory
struct Link *NextFree;
struct Link *previous;  ////  Previous Physical Block
};

struct Node_S{

	struct Link *next;
};

struct Node *A;//Level one
struct Node *B;//Level Two

void First_Level(){

A=(struct Node *) malloc(6*sizeof(struct Node));  ///Allocating array of Nodes till Index 5 i.e. till 512 KB

	int var;
		for ( var = 0; var < 6; ++var)
			A[var].next=NULL;

}

// Converting Memory Required according First Level
int Conversion_First(int k){

	int i=k;
	int j=16;
	int index=0;

	while((i-j)>=j){  //For converting given address to required Index that can match The Index of First_Level Array

		i=k;
		j=j*2;
		index+=1;
	}
	return index;
}

// Converting Memory Required according to Second Level
int Conversion_Second(int size,int k,int z){

int i=16;
int Index=k;

while(k>0){

	i=i*2;
	k--;
}

int Gap=i/4; ////////Gap after dividing the Space by 4 i.e (64-32)/4  which is Gap of 8
int Cal=size-i;  ////////////////  Calculating  i.e. 67-64
	Cal=Cal/Gap;	/// Calculating Index for Second_Table i.e. (67-64)/8 which is 0 index fr 64 Node.
	Cal=Cal+Index*4;

	struct Link *tempo;

	if(z==1)		//1 means searching for freememory
		while(Cal<24){

		tempo=B[Cal].next;
////     checking First Link of the Second Level if less than move ahead else return .
	if((B[Cal].next!=NULL)&&(tempo->size>size)){

		return Cal;//Returning The Index of Second_Level Array.

	}
	else
		Cal++;
		}
	else
		return Cal;			//0 means searching for proper index to assing
		return -1; // If Index point to NULL
}

void Second_Level(){

int var=0;
int Index=0;
B=(struct Node_S *) malloc(24*sizeof(struct Node_S));///Allocating array of 24 i.e. 4 for each Node(T.6 Nodes Til 512)

		for ( var = 0; var < 24; ++var)  //checking the NULL of Array B.
				B[var].next=NULL;

////////// Here Comes The joining Part Of First Level Array to Second Level Array  /////////////////////////
			for ( var = 0; var <6; ++var) {
										//////// Joining 0st var of A to 0 Index of B and then incre Index by 4.
			A[var].next=(B+Index);
				Index=Index+4;
			}
/////////////////////////  Joining DONE   //////////////////////////////////////////////
}

int MemInit(){

	void *a=(void *)malloc(512);	//Allocate 512 bytes
	struct Link *p=(struct Link *)a;

	First_Level();
	Second_Level();
		p->free=1;                         ///1 for allocation
		p->next=NULL;
		p->previous=NULL;
		p->NextFree=NULL;
		p->size=512-20;
		B[23].next=p;

}

void *MyMalloc(int s){

	int k=Conversion_First(s);
	int p=Conversion_Second(s,k,1);
	void *a,*v;
	if(p==-1)
		printf("Sorry ! Memory Cann't Be Allocated\n");
	else{

		struct Link *temp=B[p].next;

		if((temp->size)<(s+20))
			printf("Sorry ! Memory Cann't Be Allocated\n");
		else {
		B[p].next=NULL;
		int S=temp->size; //Actual Size
		temp->size=s;
		temp->free=1;//Get Allocated
		temp->NextFree=NULL;
		a=temp;
		v=a;
		a=a+s;
		a=a+20;
		struct Link *x=(struct Link *)a;
		x->previous=temp;
		temp->next=x;
		x->size=S-s-20;
		x->free=0;
		x->NextFree=NULL;
		if(x->size>=16){					///Disregarding the fragmentation less that size 16
		int l=Conversion_First(x->size);
		int m=Conversion_Second(x->size,l,0);
		if(B[m].next==NULL){
			B[m].next=x; ///make it x
			x->next=NULL;
			}
		else{
			struct Link *y=B[m].next;

			while(y->NextFree!=NULL){

				y=y->NextFree;

			}
			y->NextFree=x;

		}

			}
		}
	}

	return v;
}


////////////////////////////////////////////////  Here Comes MyFree  ////////////////////////////

void MyFree(void *p){


	struct Link *d=(struct Link *)p;
	struct Link *a=d;
	struct Link *e=d;


		int l,m;
		l=m=0;
		a->free=0;
		while((a->next!=NULL)&&(a->next->free==0)){
			l++;
			d->size+=a->next->size;
			a->free=0;
			int b=Conversion_First(a->next->size);
			int c=Conversion_Second(a->next->size,b,0);
			B[c].next=NULL;

			a=a->next;
		}

			d->size+=l*20;

			d->next=a->next;

		while((e->previous!=NULL)&&(e->previous->free==0)){
			m++;
			d=e;
			e->free=0;
			e->size+=e->previous->size;
			int f=Conversion_First(e->previous->size);
			int g=Conversion_Second(e->previous->size,f,0);
			B[g].next=NULL;

			e=e->previous;
		}

		d->previous=e->previous;
		d->size+=m*20;
		int h=Conversion_First(d->size);
		int i=Conversion_Second(d->size,h,0);
		if(B[i].next==NULL){
			B[i].next=d;
		}
		else{
			struct Link *j=B[i].next;

			while(j->NextFree!=NULL)
				j=j->NextFree;
			j->NextFree=d;
		}
}

/////////////////////////////////////// MyFree - THE END  /////////////////////////////////////////////////



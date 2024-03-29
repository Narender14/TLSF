/*
 ============================================================================
 Name        : TLSF.c
 Author      : Narender
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Defining structure for First-Level Hashing.
 */
struct Node{

	struct Node_S *next;
};

/*
 * Defining structure for Blocks of Free Memory to be allocated.
 */
struct Link{

int size;  				 // size of free or allocated blocks
int free;  				 // flag for block i.e. Free or Allocated
struct Link *next;       // Pointer to next block
struct Link *NextFree;   // Pointer to next free block within a corresponding Hash Index
struct Link *previous;   // Pointer to previous block
};


/*
 * Defining structure for Second-Level Hashing.
 */
struct Node_S{

	struct Link *next;
};

struct Node *A;    // First-Level
struct Node *B;    // Second-Level


/*
 *Creating the First-level Hash of size 6, where first Index corresponds to memory size of 32 units,
 *second to 64 units, third to 128 and so on.
 *
 *This Function Create the First-Level Hash and Initializes its index to NULL value
 */
void First_Level(){

	A=(struct Node *) malloc(6*sizeof(struct Node));

	int var;
	for ( var = 0; var < 6; ++var)
		A[var].next=NULL;

}

/*
 *Creating the Second-Level hash of size 24 i.e. each First-Level Index is subdivided into 4 Second-level Index.
 *Each First-level index is joined to start+4th Index of second-level where start =0.
 */
void Second_Level(){

	int var=0;
	int Index=0;
	B=(struct Node_S *) malloc(24*sizeof(struct Node_S));

		for ( var = 0; var < 24; ++var)
				B[var].next=NULL;

		for ( var = 0; var <6; ++var) {
				A[var].next=(B+Index);
				Index=Index+4;
			}
}

/*
 *This Function takes the memory size as an argument and return the corresponding First-Level Hash Index.
 */
int Conversion_First(int k){

	int i=k;
	int j=16;
	int index=0;

	while((i-j)>=j){

		i=k;
		j=j*2;
		index+=1;
	}
	return index;
}

/*
 *This Function takes the memory size, First-level index as an argument and return the corresponding
 *Second-Level Hash Index.
 */
int Conversion_Second(int size,int k,int z){

	int i=16;
	int Index=k;

		while(k>0){

			i=i*2;
			k--;
		}

	int Gap=i/4;
	int Cal=size-i;
	Cal=Cal/Gap;
	Cal=Cal+Index*4;
	struct Link *tempo;

	if(z==1)		               //1 means searching for free memory
		while(Cal<24){

			tempo=B[Cal].next;
			if((B[Cal].next!=NULL)&&(tempo->size>size)){
				return Cal;		//Returning The Index of Second_Level Array.
			}
			else
				Cal++;
		}
	else
		return Cal;			//0 means searching for proper index to assign
		return -1; 			// If Index point to NULL
}


/*
 *Allocating initial Free memory pool of size 512 unit.
 *and then joining this free memory pool to the corresponding
 *first and second level Hash Index
 */
int MemInit(){

	void *a=(void *)malloc(512);         //Allocating free pool
	struct Link *p=(struct Link *)a;        // Conversion to struct which has size 20.

	First_Level();
	Second_Level();
		p->free=1;                  // Initialising it as free
		p->next=NULL;
		p->previous=NULL;          //  With no previous
		p->NextFree=NULL;          //  With no next Free
		p->size=512-20;            // size of 512-20.
		B[23].next=p;

}

/*
 *Given the size of memory to be allocated, its first and second-level index is calculated and
 *then it was checked whether any free memory corresponding to that size exist or not.
 *Depending on condition, Memory is allocated
 *
 *If memory left corresponding to Hash level after allocation is less than 16 unit, it is allocated to the
 *requested process.
 */
void *MyMalloc(int s){

	int k=Conversion_First(s);
	int p=Conversion_Second(s,k,1);
	void *a,*v;

	if(p==-1)       // If no corresponding size exist
		printf("Sorry ! Memory Cann't Be Allocated\n");
	else{

		struct Link *temp=B[p].next;

			if((temp->size)<(s+20))
				printf("Sorry ! Memory Cann't Be Allocated\n");
			else {
					B[p].next=NULL;
					int S=temp->size;
						temp->size=s;
							temp->free=1;
								temp->NextFree=NULL;
									a=temp;
									v=a;    // be careful !!
									a=a+s;  // It is required
										a=a+20; // It is required
									struct Link *x=(struct Link *)a;
								x->previous=temp;
							temp->next=x;
						x->size=S-s-20;

											x->free=0;
											x->NextFree=NULL;

									if(x->size>=16){		///Disregarding the fragmentation less that size 16.
										int l=Conversion_First(x->size);
										int m=Conversion_Second(x->size,l,0);

											if(B[m].next==NULL){
												B[m].next=x;
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


/*
 *
 *Given the pointer to allocated memory, it deallocate the memory chunk and coalesce it with neighboring
 *free memory.
 *Then, it will calculate the corresponding hash Index and attached the Index to the size of memory freed.
 *
 *
 *For coalesce, it traverses the memory list left and right and checking for free flag equals 1 keeps updating
 *the size of free memory.
 *
 */

void MyFree(void *p){

	struct Link *d=(struct Link *)p;
	struct Link *a=d;
	struct Link *e=d;


		int l,m;
		l=m=0;
		a->free=0;

			while((a->next!=NULL)&&(a->next->free==0)){    // Forward traverse
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

		while((e->previous!=NULL)&&(e->previous->free==0)){		// Backward traverse
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
		int h=Conversion_First(d->size);           // Getting First-level Index
		int i=Conversion_Second(d->size,h,0);      // Getting Second-level index
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

/////////////////////////***************************************************////////////////////////////


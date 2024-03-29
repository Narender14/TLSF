/*
 *Test Cases where each argument represent memory size in bytes.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include"mymalloc.h"

int main() {

MemInit();   //Initializing free pool of memory

int i=0;

void *A[10];	//Array to store the pointer to allocated memory, these pointer will be used for freeing. 
struct Link *cv;
A[0]=MyMalloc(100);       // Allocating the memory
A[1]=MyMalloc(30);
A[2]=MyMalloc(40);
A[3]=MyMalloc(20);
A[4]=MyMalloc(50);
A[5]=MyMalloc(50);

MyFree(A[0]);            // Free the memory
MyFree(A[1]);
MyFree(A[2]);
MyFree(A[3]);
MyFree(A[4]);
MyFree(A[5]);

MyMalloc(200);
MyMalloc(125);

return 0;

}


#include"fib.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

// Define Fib Instance of Sequence Interface

struct _fib_seq{
  seq si;  //instance of the interface as first element.
  int next; //number to become current when gotoNext is called
  int current; //number to return for getCurrent is called
};

typedef struct _fib_seq fib;


//gotoNext function for fib instance
void fibGotoNext(seq * sthis){
  fib* this = (fib*) sthis;
  int prev = this->current;
  this->current = this->next;
  this->next = prev + this->current;
}


//getCurrent function for fib instance
token fibGetCurrent(seq * sthis){
  fib* this = (fib*) sthis;
  token t;
  //translate integer to string and package in token
  snprintf(t.text, sizeof(token)-1, "%d",this->current);   
  return t; //not a pointer, safe to return;
}

//destroy function for fib instance (destructor)
void fibDestroy(seq* sthis){
  free(sthis); //return memory occupied by instance back to system.
}

//Fib Constructor
seq * newFibSeq(int A, int B){
  //allocate space for instance
  fib * f = (fib*) malloc(sizeof(fib));
  //format  interface with instance related functions. 
  f->si.getCurrent = fibGetCurrent;
  f->si.gotoNext = fibGotoNext;
  f->si.destroy = fibDestroy;
  //format private variables of instance.
  f->next = B;
  f->current = A;
  //return instance as pointer to its interface.
  return (seq*) f;
}




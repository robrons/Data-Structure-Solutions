#include"foxsays.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

struct _foxsays_seq{
  seq si;  //instance of the interface as first element.
  token next, current, temp;
  int call_count;
};
typedef struct _foxsays_seq foxsays;

//getCurrent function for foxsays instance
token foxsaysGetCurrent(seq * sthis){
  foxsays* this = (foxsays*) sthis;
  token t;
  if(this->call_count%7 != 0){
     this->temp = this->current;
  }
  snprintf(t.text,sizeof(token), "%s", (this->temp.text));
  this->call_count++;
  return t; //not a pointer, safe to return;
}

//gotoNext function for foxsays instance
void foxsaysGotoNext(seq * sthis){
  foxsays* this = (foxsays*) sthis;
  this->temp = this->next;
}


//destroy function for fib instance (destructor)
void foxsaysDestroy(seq* sthis){
  free(sthis); //return memory occupied by instance back to system.
}


//Foxsays Constructor
seq * newFoxSaysSeq(token A, token B){
  //allocate space for instance
  foxsays * g = (foxsays*) malloc(sizeof(foxsays));
  //format  interface with instance related functions.
  g->si.getCurrent = foxsaysGetCurrent;
  g->si.gotoNext = foxsaysGotoNext;
  g->si.destroy = foxsaysDestroy;
  //format private variables of instance.

  g->current = A;
  g->next = B;
  g->call_count = 1;
  //return instance as pointer to its interface.
  return (seq*) g;
}


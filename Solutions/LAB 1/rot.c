#include"rot.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


struct _rot_seq{
  seq si;  //instance of the interface as first element.
  unsigned int next; //number to become current when gotoNext is called
  unsigned int current; //number to return for getCurrent is called
  unsigned int temp;
  unsigned int call_count;
};

typedef struct _rot_seq rot;


token rotGetCurrent(seq * sthis){
  rot* this = (rot*) sthis;
  token t;
  if(this->call_count == 8){
      this->call_count = 0;
      this->temp = this->current;
}
  //translate integer to string and package in token
  snprintf(t.text, sizeof(token)-1, "%d",this->temp);
  return t; //not a pointer, safe to return;
}

//gotoNext function for rot instance
void rotGotoNext(seq * sthis){
  rot* this = (rot*) sthis;
  this->call_count++;

  if(this->call_count  == 1){
  this->temp = (this->current + this->next);
  } else if(this->call_count  == 2){
      this->temp = this->next;
  } else if(this->call_count  == 3){
      this->temp = 0;
  } else if(this->call_count  == 4){
      this->temp = -this->current;
  } else if(this->call_count  == 5){
      this->temp = -(this->current + this->next);
  } else if(this->call_count  == 6){
      this->temp = -this->next;
  } else if(this->call_count  == 7){
      this->temp = 0;
  }

}


void rotDestroy(seq* sthis){
  free(sthis); //return memory occupied by instance back to system.
}



//Rot Constructor
seq * newRotSeq(int N, int A){
  //allocate space for instance
  rot * r = (rot*) malloc(sizeof(rot));
  //format  interface with instance related functions.
  r->si.getCurrent = rotGetCurrent;
  r->si.gotoNext = rotGotoNext;
  r->si.destroy = rotDestroy;
  //format private variables of instance.
  r->next = A;
  r->current = N;
  //return instance as pointer to its interface.

  r->call_count = 0;
  r->temp = N;
  return (seq*) r;
}

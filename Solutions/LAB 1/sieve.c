#include "sieve.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


// Define Sieve Instance of Sequence Interface
struct _sieve_seq{
  seq si;
  int * pArray; //array of "primes"
  int aSize;    //size of array
  int last;     //position of latest addition to array
};
typedef struct _sieve_seq sieve;

//declaration of functions defined after constructor

token sieveGetCurrent();
void sieveGotoNext();
void sieveDestroy();

//sieve constructor
seq * newSieveSeq(int P){
  //allocate space for instance
  sieve * s = (sieve *) malloc(sizeof(sieve));
  //format  interface with instance related functions. 
  s->si.getCurrent = sieveGetCurrent;
  s->si.gotoNext = sieveGotoNext;
  s->si.destroy = sieveDestroy;
  //format private variables of instance.
  s->aSize = 2; //initial array size
  s->pArray = (int*) malloc(sizeof(int)*s->aSize);  //get space 
  s->pArray[0] = P; //set the seed prime.
  s->last = 0;  //index of seed prime, the last prime. 
  //return pointer to instance interface. 
  return (seq*) s;
}



//gotoNext function for sieve instance
void sieveGotoNext(seq * sthis){
  sieve* this = (sieve*) sthis;
  if(this->last == this->aSize-1) { // resize array condition
    int newSize = this->aSize * 2; //double in size
    int * newArray = (int *) malloc(sizeof(int)*newSize); //space for new array
    memcpy(newArray, this->pArray, sizeof(int)*this->aSize); //copy content 
    free(this->pArray); //free old array
    this->pArray = newArray;  //set new array
    this->aSize = newSize;  //set size of new array
  }
  int candidate = this->pArray[this->last]+1; //next number after last saved "prime"
  while(1){
    int i;
    for(i = 0; i <= this->last; i++){
      if((candidate % this->pArray[i]) == 0){
        break; //candidate divisible by ith prime, break for loop.  
      }
    }
    //(if i > last) the candidate survives the for loop, it is prime. 
    if(i > this->last){
      this->last++;
      this->pArray[this->last] = candidate; //add successful candidate to array
      break;
    } else {
      //go to next candidate because for loop was broken. 
      candidate++;
    }
  } 
}
  
 
//getCurrent function for sieve instance
token sieveGetCurrent(seq * sthis){
  sieve * this = (sieve *) sthis;
  token t;
  snprintf(t.text,sizeof(token)-1, "%d", this->pArray[this->last]); //turn int into token
  return t;
}

//destroy function for sieve instance (destructor)
void sieveDestroy(seq* sthis){
  sieve * this = (sieve *) sthis;
  //constructor allocated array for primes, need to free it. 
  free(this->pArray);
  free(this); //return memory occupied by instance back to system.
}




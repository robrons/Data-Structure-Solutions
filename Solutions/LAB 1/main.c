#include "seq.h"
#include "fib.h"
#include "sieve.h"
#include "rot.h"
#include "foxsays.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void error(char * msg){printf("%s\n", msg); exit(-1);}

int main (int argc, char ** argv){
  char seqName[30];
  seq * s = NULL;
  int n;

  while(scanf("%s", seqName) > 0){
    s = NULL;
    if(strcmp(seqName, "Fib") == 0){
      int A, B;
      if(scanf("%d %d %d", &A, &B, &n) == 3)
        s = newFibSeq(A,B);
      else
        error("Could not read three integers for Fib sequence.");
    } else if(strcmp(seqName, "Sieve") == 0){
      int P;
      if(scanf("%d %d", &P, &n) == 2)
        s = newSieveSeq(P);
      else
        error("Could not read two integers for Sieve sequence.");
    } else if(strcmp(seqName, "FoxSays") == 0){
      token J, S;
      if(scanf("%s %s %d", J.text, S.text, &n) == 3)
        s = newFoxSaysSeq(J,S);
      else
        error("Could not read two characters for FoxSays sequence.");
    } else if(strcmp(seqName, "Rot") == 0){
      unsigned int T, U;
      if(scanf("%d %d %d", &T, &U, &n) == 3)
        s = newRotSeq(T,U);
      else
        error("Could not read two integers for Rot sequence.");
    } else {
      char errormsg[200];
      snprintf(errormsg, 200, "No sequence defined for %s.", seqName);
      error(errormsg);
    }

    //print first n entries in sequence.
    int i;
    for(i = 0; i < n; i++){
      token t = s->getCurrent(s);

      printf("%s", t.text);
      if(i < n-1){
        printf(", ");
        s->gotoNext(s);
      }else
        printf("\n");
    }

    s->destroy(s);
    s= NULL;
  }

  return 0;
}

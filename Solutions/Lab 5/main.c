#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#include "multiset.h"
#include <string.h>

int main() {
 char command[30];
 Set * s = NULL;
 s = AVLTree();
 while(scanf("%s", command) > 0){
 if(strcmp(command, "Add") == 0){
  box b;
  char si[22];
  unsigned long h, w, d;
  scanf("%lu",&h);
  scanf("%lu",&w);
  scanf("%lu",&d);
  scanf("%s",si);
  b.h = h;
  b.d = d;
  b.w = w;
  strcpy(b.o,si);
  s = s->add(s,b);
 } else if(strcmp(command, "Inorder") == 0){
   s->inorder(s);
 } else if(strcmp(command, "Preorder") == 0){
   s->preorder(s);
 } else if(strcmp(command, "Postorder") == 0){
   s->postorder(s);
 } else if(strcmp(command, "Count") == 0){
   unsigned long v;
   scanf("%lu",&v);
   int z = s->count(s,v);
   printf("\nThere are %d boxes with volume %lu\n",z,v);
 } else if(strcmp(command, "Remove") == 0){
   unsigned long v;
   scanf("%lu",&v);
   s->remove(s,v);
 } else if(strcmp(command, "RemoveAll") == 0){
   unsigned long v;
   scanf("%lu",&v);
   s->removeall(s,v);
 }

 }
 if(s){
 s->destroy(s);
 }
 return 0;
}

/*
 * avltree.c
 *
 *  Created on: Oct 17, 2016
 *      Author: gh0st
 */
#include "avltree.h"
#include <stdio.h>

typedef struct treenode node;
struct treenode{
        box a;
        size_t height;
        node *left;
        node *right;
};
typedef struct tree AVL;
struct tree{
    Set s;
    node * root;
};

int c = 0;

typedef int bool;
#define true 1
#define false 0

Set * AVLadd(Set*, box);
void  AVLpreorder(Set*);
void  AVLinorder(Set*);
void  AVLpostorder(Set*);
node * RecalcHeight(node*);
size_t H(node*);
bool Balanced(node*);
node * RotateRight(node*);
node * RotateLeft(node*);
node * Rebalance(node*);
node * Remove(node*, unsigned long, bool*);
node * RemoveHelp(node*, node*);
int comp(box,box);
Set * AVLremove(Set*, unsigned long);
Set * AVLremoveall(Set*, unsigned long);
int AVLcount(Set*, unsigned long);
unsigned long vol(box);
void AVLdestroy(Set*);

Set * AVLTree(){
      AVL * avl = NULL;
	  avl = (AVL*) malloc(sizeof(AVL));
	  avl->s.add = AVLadd;
	  avl->s.preorder = AVLpreorder;
	  avl->s.inorder = AVLinorder;
	  avl->s.postorder = AVLpostorder;
      avl->root = NULL;
      avl->root->height;
	  avl->s.remove = AVLremove;
	  avl->s.removeall = AVLremoveall;
	  avl->s.count = AVLcount;
	  avl->s.destroy = AVLdestroy;
      return (Set*)avl;
}

int comp(box a,box b){
 unsigned long va = vol(a);
 unsigned long vb = vol(b);
 if(va>vb) return -1;
 else if(va<vb) return 1;
 else return 0;
}

node * Insert(node *n, box a)
	{
	        if(n==NULL)
	        {
	                node *temp;
	                temp = (node*)malloc(sizeof(node));
	                temp->a = a;
	                temp->left = temp->right = NULL;
	                temp->height = 1;
	                return temp;
	        }
	        if(comp(n->a,a)<=0) n->left= Insert(n->left,a);
	        else n->right = Insert(n->right,a);
	        return Rebalance(n);
	}

Set * AVLadd(Set* s, box a){
   AVL* n = (AVL *) s;
   n->root = Insert(n->root,a);
  return s;
}
void print(node *n){
unsigned long v = vol(n->a);
printf("Box(H = %lu, W = %lu, D = %lu, A = %lu, O = %s)\n",n->a.h,n->a.w,n->a.d,v,n->a.o);
}
void PrintPreorder(node *n)
	{
	        if(n==NULL)
	        {
	                return;
	        }
	        print(n);
	        PrintPreorder(n->left);
	        PrintPreorder(n->right);
	}

void AVLpreorder(Set* s){
	AVL * n = (AVL *) s;
        printf("%s\n","Preorder:");
	PrintPreorder(n->root);
}

void Printinorder(node *n)
	{
	        if(n==NULL)
	        {
	                return;
	        }
	        Printinorder(n->left);
	        print(n);
	        Printinorder(n->right);
	}

void AVLinorder(Set* s){
	AVL * n = (AVL *) s;
        printf("%s\n","Inorder:");
	Printinorder(n->root);
}

void Printpostorder(node *n)
	{
	        if(n==NULL)
	        {
	                return;
	        }
	        Printpostorder(n->left);
	        Printpostorder(n->right);
            print(n);
	}

void AVLpostorder(Set* s){
	AVL * n = (AVL *) s;
        printf("%s\n","Postorder:");
	Printpostorder(n->root);
}

size_t H(node* n){
 if(n==NULL){return 0;};
 return n->height;
}

node * RecalcHeight(node *n){
 if(n!= NULL){
 if(H(n->left)>=H(n->right)){
  n->height = H(n->left) +1;
 } else if(H(n->left)<H(n->right)){
  n->height = H(n->right) +1;
 }
 }
 return n;
}

bool Balanced(node *n){
if(n==NULL) return true;
size_t diff = H(n->left) - H(n->right);
if(-1<=diff&&diff<=1) return true;
return false;
}

node * RotateRight(node *n){
  if(n==NULL) return n;
  if(n->left == NULL) return n;
  node *newroot = n->left;
  n->left = newroot->right;
  newroot->right = n;
  RecalcHeight(n);
  RecalcHeight(newroot);
  return newroot;
}

node * RotateLeft(node *n){
  if(n==NULL) return n;
  if(n->right == NULL) return n;
  node *newroot = n->right;
  n->right = newroot->left;
  newroot->left = n;
  RecalcHeight(n);
  RecalcHeight(newroot);
  return newroot;
}

node * Rebalance(node *n){
if(n==NULL) return n;
if(H(n->left) > H(n->right)+1) {
if(H(n->left->right)>H(n->left->left)) {n->left = RotateLeft(n->left);}
 return RotateRight(n);
} else if(H(n->right) > H(n->left)+1){
if(H(n->right->left)>H(n->right->right)){n->right = RotateRight(n->right);}
 return RotateLeft(n);
}
n = RecalcHeight(n);
return n;
}

int comp2(box a,unsigned long vb){
 unsigned long va = vol(a);
 if(va>vb) return 1;
 else if(va<vb) return -1;
 else return 0;
}

node * Remove(node *n, unsigned long v, bool *deleted){
if(n==NULL) return n;
if(comp2(n->a,v)==1){
n->left = Remove(n->left,v,deleted);
} else if(comp2(n->a,v)==-1){
n->right = Remove(n->right,v,deleted);
} else {
  deleted = true;
  if(n->left == NULL){
  node * newroot = n->right;
  free(n);
  return newroot;
  } else {
  n->left = RemoveHelp(n->left,n);
  }
}
return Rebalance(n);
}

node * RemoveHelp(node *n, node *replace){
if(n==NULL) return n;
if(n->right!=NULL){
n->right = RemoveHelp(n->right, replace);
return Rebalance(n);
} else {
replace->a = n->a;
node *left = n->left;
free(n);
return left;
}
}

unsigned long vol(box b){
 unsigned long v = b.d*b.h*b.w;
  return v;
}

void count(node *n, unsigned long v)
	{
	        if(n==NULL)
	        {
	                return;
	        }
            if(vol(n->a) == v) {c++;};
	        count(n->left,v);
	        count(n->right,v);
	}

int AVLcount(Set* s, unsigned long v){
   AVL * n = (AVL *) s;
   c = 0;
   count(n->root,v);
   return c;
}

Set * AVLremove(Set* s, unsigned long v){
  AVL * n = (AVL *) s;
  bool *f = false;
  n->root = Remove(n->root,v,f);
  return s;
}

Set* AVLremoveall(Set* s, unsigned long v){
  AVL * n = (AVL *) s;
  int c = AVLcount(s,v);
  for(int i = 0; i<c;i++){
  bool *f = false;
  n->root = Remove(n->root,v,f);
  }
  return s;
}

void deletetree(node *n){
   if(n==NULL) return;
   deletetree(n->left);
   deletetree(n->right);
   free(n);
}
void AVLdestroy(Set*s){
  AVL * avl = (AVL *) s;
  deletetree(avl->root);
  free(avl);
}



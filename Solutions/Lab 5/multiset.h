/*
 * multiset.h
 *
 *  Created on: Oct 17, 2016
 *      Author: gh0st
 */

#ifndef MULTISET_H_
#define MULTISET_H_

#include<stdlib.h>

typedef struct _box box;
struct _box{
 char o[22];
 unsigned long h;
 unsigned long w;
 unsigned long d;
};

typedef struct _multiset_interface Set;
struct _multiset_interface{
   Set * (*add)(Set*, box);
   int (*count)(Set*, unsigned long);
   Set * (*remove)(Set*, unsigned long);
   Set * (*removeall)(Set*, unsigned long);
   void (*preorder)(Set*);
   void (*inorder)(Set*);
   void (*postorder)(Set*);
   void (*destroy)(Set*);
};

#endif /* MULTISET_H_ */

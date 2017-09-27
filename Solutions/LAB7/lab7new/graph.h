#ifndef __graph_h_
#define __graph_h_

#include<stdlib.h>
#include<stdio.h>
#include <string.h>

typedef struct _edge_data EData;
typedef struct _vertex_data VData;
typedef struct _edge Edge;
typedef struct _vertex Vertex;
typedef struct _edge_list_node ENode;
typedef struct _edge_list EList;
typedef struct _vertex_list_node VNode;
typedef struct _vertex_list VList;

struct _edge_data{
    int start_time, end_time, cost;
};


struct _vertex_data{
    char * apc;
};

struct _vertex{
VData * VD;
EList * EL;
};

struct _edge{
    Vertex * sourceV;
    Vertex * targetV;
    EData * ED;
};

struct _edge_list_node{
 Edge * E;
 ENode * next;
};

struct _edge_list{
ENode * first;
size_t size;
};

struct _vertex_list_node{
 Vertex * V;
 VNode * next;
};

struct _vertex_list{
VNode * first;
size_t size;
};


typedef struct _graph_interface Graph;
struct _graph_interface{
   Vertex (*newVertex)(Graph*, VData*);
   Edge (*newEdge)(Graph*, EData*, Vertex, Vertex);
   Vertex* (*getVertexOf)(Graph*,VData*);

   /*VData * (*getVData)(Graph*, Vertex);
   EData * (*getEData)(Graph*, Edge);*/

   void (*destroy)(Graph*);
};
Graph * createGraph();

#endif












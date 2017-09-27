#ifndef __tree_h_
#define __tree_h_

#include<stdlib.h>

typedef struct _graph_interface Graph;
struct _graph_interface{
   Vertex (*newVertex)(Graph*, VData*);
   VData * (*getVData)(Graph*, Vertex);
   Edge (*newEdge)(Graph*, EData*, Vertex, Vertex);
   EData * (*getEData)(Graph*, Edge);

   void (*destroy)(List*);
};






#endif












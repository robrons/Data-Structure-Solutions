#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

VList *vl = NULL;
void VLinsert(Vertex*, size_t);
void ELinsert(EList*, Edge*, size_t);
Vertex GnewVertex(Graph*, VData*);
Edge GnewEdge(Graph*, EData*, Vertex, Vertex);
Vertex* GgetVertexOf(Graph*,VData*);
VNode * newVNode(Vertex*, VNode*);
ENode * newENode(Edge*, ENode*);
VNode * getVNode(VNode*, size_t);
ENode * getENode(ENode*, size_t);
void Gdestroy(Graph*);

Graph * createGraph(){
    Graph * g = (Graph*)malloc(sizeof(Graph));
    g->newEdge = GnewEdge;
    g->newVertex = GnewVertex;
    g->getVertexOf = GgetVertexOf;
    g->destroy = Gdestroy;
    vl = (VList*)malloc(sizeof(VList));
    vl->size = 0;
    vl->first = NULL;
    return g;
}

VNode * newVNode(Vertex* v,VNode * next){
    VNode * vn = malloc(sizeof(VNode));
    vn->V = v;
    vn->next = next;
    return vn;
}

ENode * newENode(Edge* e,ENode * next){
    ENode * en = malloc(sizeof(ENode));
    en->E = e;
    en->next = next;
    return en;
}

Vertex * recGetVertex(VNode *vn, VData *vd){
if(vn==NULL) return NULL;
if(vn->V->VD==vd) return vn->V;
return recGetVertex(vn->next,vd);
}

Vertex * GgetVertexOf(Graph* g,VData* vd){
return recGetVertex(vl->first,vd);
}

Edge GnewEdge(Graph* g, EData* ed, Vertex source, Vertex target){
Edge *e = (Edge*)malloc(sizeof(Edge));
e->ED = ed;
if(GgetVertexOf(g,source.VD)==NULL){
    source = GnewVertex(g,NULL);
}
if(GgetVertexOf(g,target.VD)==NULL){
    target = GnewVertex(g,NULL);
}

e->sourceV = &source;
e->targetV = &target;
ELinsert(e->sourceV->EL,e,e->sourceV->EL->size);
ELinsert(e->targetV->EL,e,e->targetV->EL->size);

return *e;
}

Vertex GnewVertex(Graph* g, VData* vd){
Vertex *v = (Vertex*)malloc(sizeof(Vertex));
v->VD = vd;
v->EL = NULL;
VLinsert(v,vl->size);

return *v;
}

void VLinsert(Vertex* v, size_t i){
printf("test\n");
if(i==0){
vl = (VList*)malloc(sizeof(VList));
vl->first = newVNode(v, NULL);
} else {
        VNode * prior = getVNode(vl->first, i-1);
        prior->next = newVNode(v, prior->next);
  }
vl->size++;
}

void ELinsert(EList* el, Edge* e, size_t i){
if(el==NULL){
el = (EList*)malloc(sizeof(EList));
el->size = 0;
el->first = newENode(e, NULL);
} else {
        ENode * prior = getENode(el->first, i-1);
        prior->next = newENode(e, prior->next);
  }
el->size++;
}

VNode * getVNode(VNode* vn, size_t i){
if(vn==NULL || i == 0) return vn;
return getVNode(vn->next, i-1);
}

ENode * getENode(ENode* en, size_t i){
if(en==NULL || i == 0) return en;
return getENode(en->next, i-1);
}

void Gdestroy(Graph* g){
  free(g);
  free(vl);
}

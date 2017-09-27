#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"
#include "graph.h"

 Graph * g = NULL;


void AcreateFlight(Airport*, char*, char*, int, int, int);
void AlistFlight(Airport*, char*);
void AlistAllFlights(Airport*, char*);
void AdestroyAirport(Airport*);


Airport * createAirport(){
    Airport * a = NULL;
        a = (Airport*)malloc(sizeof(Airport));
        a->createFlight = AcreateFlight;
        a->listAllFlights = AlistAllFlights;
        a->listFlights = AlistFlight;
        a->destroyAirport = AdestroyAirport;
        g = createGraph();
        return (Airport*) a;
}

void AcreateFlight(Airport* a, char* apc1, char* apc2, int cost, int start_time, int end_time){
EData * ed = (EData*)malloc(sizeof(EData));
ed->cost = cost;
ed->start_time = start_time;
ed->end_time = end_time;
VData *vd1 = (VData*)malloc(sizeof(VData));
VData *vd2 = (VData*)malloc(sizeof(VData));
vd1->apc = apc1;
vd2->apc= apc2;
g->newEdge(g,ed,g->newVertex(g,vd1),g->newVertex(g,vd2));

}

void AlistFlight(Airport* a, char* apc){


}

void AlistAllFlights(Airport* a, char* apc){

}

void AdestroyAirport(Airport* a){
  free(a);
}

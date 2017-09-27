#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"


int main()
{
   char command[30];
   Airport * a = NULL;
   a = createAirport();

   while(scanf("%s", command) > 0){
   if(strcmp(command, "Flight") == 0){
   char apc1[5];
   char apc2[5];
   int cost, start_time, end_time;
   scanf("%s",apc1);
   scanf("%s",apc2);
   scanf("%d",&cost);
   scanf("%d",&start_time);
   scanf("%d",&end_time);
   a->createFlight(a,apc1,apc2,cost,start_time,end_time);
   } else if(strcmp(command, "List") == 0){
        char apc[5];
        char apc2[5];
        scanf("%s",apc);
        if(strcmp(apc,"*")==0){
            scanf("%s",apc2);
            a->listAllFlights(a,apc2);
        } else{
            a->listFlights(a,apc);
        }
   }
   }

   if(a){
   a->destroyAirport(a);
   }
   return 0;
}

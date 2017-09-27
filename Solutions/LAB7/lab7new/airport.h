#ifndef __airport_h_
#define __airport_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _airport_interface Airport;
struct _airport_interface{
   void (*createFlight)(Airport*, char*, char*, int, int, int);
   void (*listFlights)(Airport*, char*);
   void (*listAllFlights)(Airport*, char*);
   void (*destroyAirport)(Airport*);
};
Airport * createAirport();

#endif

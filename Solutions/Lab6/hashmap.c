#include"hashmap.h"
#include"trackedmemory.h"

#define NEVER_OCCUPIED 0
#define OCCUPIED 1
#define PREV_OCCUPIED 2


Map * HMadd (Map*, Key, Value);
Map * HMremove(Map*, Key);
Map * HMlookup(Map*, Key, Value**);
void HMdestroy(Map*);

typedef struct _oa_entry entry;
struct _oa_entry{
  Key k;
  Value v;
  char state;
};


typedef struct _hash_map HMap;
struct _hash_map{
  Map mi;
  entry * T;
  my_size_t * primes;
  my_size_t pts;
  my_size_t ts;
  my_size_t ne;
  my_size_t p1;
  my_size_t p2;
  double load;
  char flag;
};

my_size_t hash(void * d, my_size_t n, my_size_t p, my_size_t ts){
  my_size_t a = 0,i = 0;
  unsigned char * e = (char*)d;
  while(i < n){
    a = a*p + e[i];
    i++;
  }
  return a % ts;
}

Map * newHashMap(char flag){
   HMap * m = (HMap*)MALLOC(sizeof(HMap));
   m->mi.add = HMadd;
   m->mi.remove = HMremove;
   m->mi.lookup = HMlookup;
   m->mi.destroy = HMdestroy;
   m->primes = (my_size_t *)MALLOC(sizeof(my_size_t)*20);
   m->primes[0] = 37;
   m->primes[1] = 101;
   m->primes[2] = 307;
   m->primes[3] = 1019;
   m->primes[4] = 2011;
   m->primes[5] = 4201;
   m->primes[6] = 8999;
   m->primes[7] = 20051;
   m->primes[8] = 40039;
   m->primes[9] = 80021;
   m->primes[10] = 160001;
   m->primes[11] = 320057;
   m->primes[12] = 640009;
   m->primes[13] = 1280023;
   m->primes[14] = 2800001;
   m->primes[15] = 5600027;
   m->primes[16] = 11200001;
   m->primes[17] = 22400009;
   m->primes[18] = 32452843;
   m->primes[19] = 43489877;
   m->pts = 0;
   m->ts = m->primes[m->pts];
   m->ne = 0;
   m->T = (entry*)CALLOC(sizeof(entry), m->ts);
   m->p1 = 29;
   m->p2 = 17;
   m->load = 0.7;
   m->flag = flag;
   return (Map*)m;
}

void resize(HMap*);

Map * HMadd (Map*m, Key k, Value v){
  HMap * hm = (HMap*)m;
  if(hm == NULL) return m;
  resize(hm);
  size_t start = hash(&k, sizeof(Key), hm->p1, hm->ts);
  size_t offset = hash(&k, sizeof(Key), hm->p2, hm->ts);
  size_t p = start;
  size_t i = 0;
  size_t inserted = 0;

  char keyText[21], valueText[21];
  printKey(k, keyText, 21);
  printValue(v, valueText, 21);
  if(hm->flag)
    printf("adding %s %s at %lu\n", keyText, valueText, start);

  while(!inserted&&i<hm->ts){
      if(hm->T[p].state == NEVER_OCCUPIED||hm->T[p].state == PREV_OCCUPIED){
       hm->T[p].k = k;
       hm->T[p].v = v;
       hm->T[p].state = OCCUPIED;
       hm->ne++;
       inserted = 1;
    } else if(hm->T[p].state == OCCUPIED){
            if(keyCompare(k,hm->T[p].k)!=0) {
                p = (p+offset)%hm->ts;
                i++;
      }             else {return m;}
      }
  }

  return m;
}

Map * HMremove(Map*m, Key k){
  HMap * hm = (HMap*)m;
  if(hm==NULL) return m;
  size_t start = hash(&k, sizeof(Key), hm->p1, hm->ts);
  size_t offset = hash(&k, sizeof(Key), hm->p2, hm->ts);
  size_t p = start;
  size_t found = 0;
  size_t i = 0;

  while(!found&&i<hm->ts){
    if(hm->T[p].state == NEVER_OCCUPIED){
        return m;
    } else if(hm->T[p].state == PREV_OCCUPIED){
        p = (p+offset)%hm->ts;
        i++;
    }   else {
            if(keyCompare(k,hm->T[p].k)==0){
                found = 1;
                hm->T[p].state = PREV_OCCUPIED;
                hm->ne--;
        }
    }
  }

  return m;
}

Map * HMlookup(Map* m, Key k, Value** v){
  HMap * hm = (HMap*)m;
  char keyText[21];
  printKey(k, keyText, 21);
  size_t start = hash(&k, sizeof(Key), hm->p1, hm->ts);
  size_t offset = hash(&k, sizeof(Key), hm->p2, hm->ts);
  size_t p = start;
  size_t found = 0;
  size_t i = 0;

  while(!found && i<hm->ts){
  if(hm->T[p].state == NEVER_OCCUPIED){
         *v = NULL;
         found = 1;
    } else if(hm->T[p].state == PREV_OCCUPIED){
        p = (p+offset)%hm->ts;
        i++;
    } else if(hm->T[p].state == OCCUPIED){
                if(keyCompare(k,hm->T[p].k)==0){
                    found = 1;
                    *v = hm->T[p].v;
                } else {
                         p = (p+offset)%hm->ts;
                         i++;
            }
        }
    }

    if(hm->flag && *v){
        char valueText[21];
        printValue(*v, valueText, 21);
        printf("lookup %s at %lu found %s\n", keyText, start, valueText);
    } else if(hm->flag){
            printf("lookup %s at %lu undefined\n", keyText, start);
    }
  return m;
}

void HMdestroy(Map*m){
  HMap * hm = (HMap*)m;
  FREE(hm->T);
  FREE(hm->primes);
  FREE(hm);
}


void resize(HMap*hm){
  double current_load = ((double)hm->ne/(double)hm->ts);
  if(current_load >= hm->load){
    hm->pts++;
    size_t newsize = hm->primes[hm->pts];
    entry * newTable = (entry*)CALLOC(sizeof(entry), newsize);
    size_t i;
    for(i=0; i<hm->ts; i++){
        if(hm->T[i].state == OCCUPIED){
            size_t istart = hash(&(hm->T[i].k), sizeof(Key), hm->p1, newsize);
            size_t ioffset = hash(&(hm->T[i].k), sizeof(Key), hm->p2,newsize);
            size_t j = 0, p = istart, placed = 0;
            while(placed == 0 && j < newsize){
                if(newTable[p].state == NEVER_OCCUPIED){
                    placed = 1;
                    newTable[p].k = hm->T[i].k;
                    newTable[p].v = hm->T[i].v;
                    newTable[p].state = OCCUPIED;
                } else {
                        p = (p+ioffset)%newsize;
                }

            }
    }
  }
  free(hm->T);
  hm->T = newTable;
  hm->ts = newsize;
}
}




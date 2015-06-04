#include <stdio.h>
#include <pthread.h>

#define NLOOP 5000

int counter;

void *doit(void *);

int main(){

  pthread_t tidA, tidB;
  pthread_create(&tidA, NULL, doit, NULL);
  pthread_create(&tidB, NULL, doit, NULL);

  pthread_join(tidA, NULL);
  pthread_join(tidB, NULL);

  return 0;
}

void *doit(void *vptr){
  int i, val;
  for(i=0; i<NLOOP; i++){
    val = counter;
    printf("%d: %d\n", pthread_self(), val+1);
    counter = val + 1;
  }
  return NULL;
}

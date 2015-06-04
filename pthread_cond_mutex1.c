#include <pthread.h>
#include <stdio.h>

pthread_cond_t taxiCond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t taxiMutex = PTHREAD_MUTEX_INITIALIZER;

void *traveler_arrive(void *name){
  printf("Traveler %s needs a taxi now!\n", (char *)name);
  pthread_mutex_lock(&taxiMutex);
  pthread_cond_wait(&taxiCond, &taxiMutex);
  pthread_mutex_unlock(&taxiMutex);
  printf("Traveler %s now got a taxi!\n", (char *)name);
  pthread_exit(NULL);
}

void *taxi_arrive(void *name){
  printf("Taxi %s arrives\n", (char *)name);
  pthread_cond_signal(&taxiCond);
  pthread_exit(NULL);
}

int main(){

  //taxiCond = PTHREAD_COND_INITIALIZER;
  //taxiMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_t thread;
  pthread_attr_t threadAttr;
  pthread_attr_init(&threadAttr);

  pthread_create(&thread, &threadAttr, taxi_arrive, (void *)("Jack"));
  sleep(1);
  pthread_create(&thread, &threadAttr, traveler_arrive, (void *)("Susan"));
  sleep(1);
  pthread_create(&thread, &threadAttr, taxi_arrive, (void *)("Mike"));
  sleep(1);

  return 0;
}

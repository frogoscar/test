#include <stdio.h>
#include <time.h>

int main(){

  double cpu_time_used;
  clock_t start = clock();

  int i;
  for(i=0; i<1000000000; i++);

  clock_t end = clock();
  cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;

  printf("CLOCKS_PER_SEC is %d\n", CLOCKS_PER_SEC);

  printf("Time cumsumption is %f seconds\n", cpu_time_used);

  return 0;
}

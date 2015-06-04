#include <stdio.h>
#include <sys/time.h>

int main(){

  struct timeval t_start, t_end;

  long cost_time = 0;

  //get start time
  gettimeofday(&t_start, NULL);
  long start = ((long)t_start.tv_sec) * 1000 + (long)t_start.tv_usec/1000;
  printf("Start time : %ld ms\n", start);

  sleep(2);

  // get end time
  gettimeofday(&t_end, NULL);
  long end = ((long)t_end.tv_sec) * 1000 + (long)t_end.tv_usec/1000;
  printf("End time : %ld ms\n", end);

  // calculate time interval
  cost_time = end - start;
  printf("Cost time : %ld ms\n", cost_time);

  return 0;
}

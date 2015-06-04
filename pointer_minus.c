#include <stdio.h>

int main(){
  int a[2];
  long nbytes;

  printf("Adress of a[0] is %x\n", &a[0]);
  printf("Adress of a[1] is %x\n", &a[1]);

  nbytes = (long)&a[1] - (long)&a[0];

  printf("Minus of address is %ld\n", nbytes);

  printf("Minus of pointer is %d\n", &a[1] - &a[0]);

  return 0;
}

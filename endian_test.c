#include <stdio.h>

int main(){
  union check{
    int i;
    char ch;
  }c;

  c.i = 1;

  printf((c.ch == 1) ? "Little Endian\n" : "Big Endian\n");

  return 0;
}

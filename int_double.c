#include<stdio.h>
#include<math.h>

int main(){
  double latitude1 = 43.625411;
  double latitude2 = -43.625411;

  int zhengshu1 = (int)latitude1;
  int zhengshu2 = (int)latitude2;

  printf("Zhengshu1 of latitude1 is %d\n", zhengshu1);
  printf("Zhengshu2 of latitude2 is %d\n\n", zhengshu2);

  printf("Round of latitude1 is %lf\n", round(latitude1));
  printf("Round of latitude2 is %lf\n", round(latitude2));

  return 0;
}

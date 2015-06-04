#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main()
{
    int num,choiceNum;
    int max=100,min=0;
    int clickNum = 0;
    int isContine=1;
    printf("you put max num:");
    scanf("%d",&max);


    srand(time(NULL));
    num = (rand() % (max-min+1))+min;
    printf("num is %d\n", num);

    do{
        printf("you put num:");
        scanf("%d", &choiceNum);

        ++clickNum;

        if(choiceNum > num)
        {
            printf("too big\n");
        }else if(choiceNum < num)
        {
            printf("too small\n");
        }else{
            printf("you are right,you click %d\n",clickNum);
            printf("你还要继续吗?1:0\n");
            scanf("%d",&isContine);
            if(isContine==1){
                srand(time(NULL));
                num = (rand() % (max-min+1))+min;
                printf("num is %d\n", num);
            }
        }
    }while(isContine);


    return 0;
}

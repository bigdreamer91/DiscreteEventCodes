

#include <stdio.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM 1000000


  int main(void)
{ 
    long index = 0,x,i,w,iterate=0,sum=0;
    double p;
    
    i = 2;
    w = 1;
    
    
    while(index < MAXIMUM){
        x = 1;
        w=1;
        i=2;
        index++;
        iterate = 0;
    //    printf("Inside while loop 1\n");
        p = (double)w / (w + i);
     //   printf("%6.2f\n",p);
     //   printf("x - %ld w - %ld i - %ld p - %6.2f\n",x,w,i,p);
        while(Bernoulli(p) == 0){
            x++;
            i++;
            iterate++;
            p = (double)w / (w + i);
           // printf("Inside while loop 2\n");
           // printf("x - %ld w - %ld i - %ld p - %6.2f\n",x,w,i,p);
           // printf("%6.2f\n",p);
        }
        printf("%ld\n",x);
        sum+=iterate;
        //w++;
    }
    printf("# of runs - %6.2f\n",(double)sum/index);
  return (0);
}

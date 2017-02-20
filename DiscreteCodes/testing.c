

#include <stdio.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"

#define HALF_PI (2.0 * atan(1.0))          /* 1.5707963...           */
#define MAXIMUM 1000


  int main(void)
{ 
    double x,u,temp;
    long index = 0;
    
    while(index < MAXIMUM){
        index++;
        SelectStream(1);
        u = Erlang(6, 2.5);
        SelectStream(2);
        x = Lognormal(5.4, 0.75);
        //x = 98.54 + (22.44 * u);
        printf("%6.2f\n",u);
    }
    
  return (0);
}

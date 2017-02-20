

#include <stdio.h>
#include <math.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM 1000000


  int main(void)
{ 
    long index = 0,x;
    double u;
    
    
    while(index < MAXIMUM){
        index++;
        u = Random();
        x = ((2*u)/(1-u));
        printf("%ld\n",x);
    }
    
  return (0);
}

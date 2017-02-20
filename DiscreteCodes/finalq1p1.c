

#include <stdio.h>
#include <math.h>
#include "rngs.h"

#define HALF_PI (2.0 * atan(1.0))          /* 1.5707963...           */
#define MAXIMUM 100


   double Uniform(double a, double b)      
/* --------------------------------------------
 * generate a Uniform random variate, use a < b 
 * --------------------------------------------
 */
{
  return (a + (b - a) * Random());
}


  int main(void)
{ 
    double x,u,temp;
    long index = 0;
    
    while(index < MAXIMUM){
        index++;
        u = Random();
        x = tan(u * HALF_PI);
        printf("%6.2f\n",x);
    }
    
  return (0);
}

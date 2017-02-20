//
//  q3.c
//  ass7q3
//
//  Created by Geethanjali Jeevanatham on 10/27/15.
//  Copyright (c) 2015 Geethanjali Jeevanatham. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "rng.h"
#include "rvms.h"

#define STOP 10L

double Uniform(double a, double b)
/* --------------------------------------------
 * generate a Uniform random variate, use a < b
 * --------------------------------------------
 */
{
    return (a + (b - a) * Random());
}

int main(void){
     long index = 0,d;
     double alpha, beta, u;
     while(index < STOP){
     index++;
     alpha = cdfBinomial(100,0.1,3);
     beta = 1.0 - cdfBinomial(100,0.1,16);
     u = Uniform(alpha, 1.0 - beta);
     d = idfBinomial(100,0.1,u);
     printf("%ld\n",d);
     }
}

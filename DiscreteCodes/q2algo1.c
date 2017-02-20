//
//  q2.c
//  ass7q3
//
//  Created by Geethanjali Jeevanatham on 10/27/15.
//  Copyright (c) 2015 Geethanjali Jeevanatham. All rights reserved.
//

#include <stdio.h>
#include "rng.h"
#include "rvms.h"

#define STOP 10L
double Uniform(double a, double b)
/* ===========================================================
 * Returns a uniformly distributed real number between a and b.
 * NOTE: use a < b
 * ===========================================================
 */
{
    return (a + (b - a) * Random());
}


int main(void){
    long x,index, i = 0, sum=0;
    double u;
    PutSeed(123456789);
    while(i < STOP){
        i++;
        x = 0;
        index = 0;
    u = Uniform(0.0,1.0);
    //printf("u - %lf\n",u);
   // printf("cdfPoisson(25, %ld) - %lf\n",x,cdfPoisson(25, x));
    while(cdfPoisson(25.0, x)<=u){
        index++;
        x++;
       // printf("x - %ld\n",x);
       // printf("cdfPoisson(25, %ld) - %lf\n",x,cdfPoisson(25, x));
    }
    //printf("%ld\n",x);
    //printf("%ld\n",index);
        sum += index;
    }
    printf("avg - %ld",sum/i);
}
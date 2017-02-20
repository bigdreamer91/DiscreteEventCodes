//
//  main.c
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
    double u;
    while(index < STOP){
        //index++;
        u = Random();
        d = 9;
       //printf("u %6.2f - cdfBinomial(100,0.1,10) %6.2f\n",u,cdfBinomial(100,0.1,10));
       // printf("cdfBinomial(100,0.1,4) %6.2f\n",cdfBinomial(100,0.1,4));
        //printf("cdfBinomial(100,0.1,3) %6.2f\n",cdfBinomial(100,0.1,3));
        if(cdfBinomial(100,0.1,d)<=u){
            while(cdfBinomial(100,0.1,d)<=u){
                //printf("cdfBinomial(100,0.1,d) %6.2f\n",cdfBinomial(100,0.1,d));
                d++;
               // printf("After increment cdfBinomial(100,0.1,d) %6.2f\n",cdfBinomial(100,0.1,d));
            }
        }
        else if(cdfBinomial(100,0.1,4)<=u){
            while(cdfBinomial(100,0.1,d-1)>u){
               // printf("cdfBinomial(100,0.1,d-1) %6.2f\n",cdfBinomial(100,0.1,d-1));
                d--;
               // printf("After decrement cdfBinomial(100,0.1,d-1) %6.2f\n",cdfBinomial(100,0.1,d-1));
            }
        }
        else{
            d = 4;
        }
        
        if(d <= 16 && d >= 4){
             printf("%ld\n",d);
             index ++;
        }
        else{
            continue;
        }
    }
}

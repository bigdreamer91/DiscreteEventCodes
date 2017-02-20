

#include <stdio.h>
#include <math.h>
#include "rvgs.h"
#include "rvms.h"

#define STOP 100000

int main(void){
    long index = 0,count = 0;
    double mean,var,diffx,sd,t,estimatel,estimateh,x;
    int n = 0,val;
    while(index < STOP){
        index++;
        printf("index - %ld\n ",index);
        diffx = 0.0;
        mean = 0.0;
        var = 0.0;
        n=0;
        val = 1000;
        while(n<val){
            n++;
            printf("n - %d ",n);
            x = Exponential(1.0);
            printf("x - %6.2f ",x);
            diffx = x - mean;
            printf("diffx - %6.2f ",diffx);
            var += (diffx * diffx * (n-1)/n);
            printf("var - %6.2f ",var);
            mean += (diffx/n);
            printf("mean - %6.2f\n",mean);
        }
        sd = sqrt(var / n);
        t = idfStudent((val - 1), 0.975);
        estimatel = mean - ((t * sd)/sqrt(n-1));
        estimateh = mean + ((t * sd)/sqrt(n-1));
        if((estimateh >= 1)&&(estimatel <= 1)){
            count++;
            printf("1.0 is in interval, count is %ld\n",count);
        }
        printf("Interval estimate - %6.2f <= mu <= %6.2f\n",estimatel,estimateh);
    }
    printf("Frequency of 1.0 in interval is %6.4f",((double)count/index));
    
}

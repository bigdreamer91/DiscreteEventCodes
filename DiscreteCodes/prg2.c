//
//  prg2.c
//  
//
//  Created by Geethanjali Jeevanatham on 9/21/15.
//
//

#include <stdio.h>
#include <math.h>

#define m 2147483647L
#define a 48271L

int ga(int x){
    int q = m/16375;
    int r = m%16375;
    
    long int t;
    
    t = 16375 * (x % q) - r * (x / q);
    if (t > 0)
        return (t);
    else
        return (t + m);
}

int g(int x){
    long int q = m/a;
    long int r = m%a;
    long int t;
    
    t = a * (x % q) - r * (x / q);
    if (t > 0)
        return (t);
    else
        return (t + m);
}

int main(void){
    
    //long int m = 2147483647L;
    long int x = a;
    //long int temp;
    //int stream = 1028;
    //long int moddivstr = m / stream;
    long int j = 0,i = 1;
    //double t;
    
    while(x!=1){
        if(i == m - 2)
             printf("x is %ld and i is %ld\n",x,i);
        i++;
        x = g(x);
    }
    
    printf("last stored x value is %ld and i is %ld\n",x,i);
    
    //printf("maximal jump j is %ld and a^j mod m is %ld\n",j, temp);
    
}

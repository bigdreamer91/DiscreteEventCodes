#include <stdio.h>
#include <math.h>

#define m 2147483647L
#define a 48271L

long int g(long int x){
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
     long int temp;
     int stream = 1028;
     long int moddivstr = m / stream;
     long int j = 0,i = 1;
     double t;
    
    while(x!=1){
        if((m%x < m/x)){
            printf("x is %ld and i is %ld\n",x,i);
            if(i > j){
                j = i;
                temp = x;
            }
        }
        i++;
        if(i>=moddivstr)
            break;
        x = g(x);
    }
    
    printf("maximal jump j is %ld and a^j mod m is %ld\n",j, temp);
    
}
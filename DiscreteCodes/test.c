//
//  test.c
//  
//
//  Created by Geethanjali Jeevanatham on 10/2/15.
//
//

#include <stdio.h>
#include <time.h>

#define STOP       100
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static long seed = DEFAULT;    /* seed is the state of the generator        */
static long seedone = DEFAULT;

double Random(int x)
/* ---------------------------------------------------------------------
 * Random is a Lehmer generator that returns a pseudo-random real number
 * uniformly distributed between 0.0 and 1.0.  The period is (m - 1)
 * where m = 2,147,483,647 amd the smallest and largest possible values
 * are (1 / m) and 1 - (1 / m) respectively.
 * ---------------------------------------------------------------------
 */
{
    const long Q = MODULUS / MULTIPLIER;
    const long R = MODULUS % MULTIPLIER;
    long temp = 0;
    long t;
    
    if(x==1){
    
    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    if (t > 0)
        seed = t;
    else
        seed = t + MODULUS;
    temp = seed;
    }
    else{
        t = MULTIPLIER * (seedone % Q) - R * (seedone / Q);
        if (t > 0)
            seedone = t;
        else
            seedone = t + MODULUS;
        temp = seedone;
    }
    return ((double) temp / MODULUS);
}


void PutSeed(long x, int y)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to initialize or reset the state of
 * the random number generator according to the following conventions:
 *    if x > 0 then x is the initial seed (unless too large)
 *    if x < 0 then the initial seed is obtained from the system clock
 *    if x = 0 then the initial seed is to be supplied interactively
 * --------------------------------------------------------------------
 */
{
    char ok = 0;
    
    if (x > 0L)
        x = x % MODULUS;                          /* correct if x is too large  */
    if (x < 0L)
        x = ((unsigned long) time((time_t *) NULL)) % MODULUS;
    if (x == 0L)
        while (!ok) {
            printf("\nEnter a positive integer seed (9 digits or less) >> ");
            scanf("%ld", &x);
            ok = (0L < x) && (x < MODULUS);
            if (!ok)
                printf("\nInput out of range ... try again\n");
        }
    if (y == 1)
        seed = x;
    else
        seedone = x;
}


void GetSeed(long *x)
/* --------------------------------------------------------------------
 * Use this (optional) procedure to get the current state of the random
 * number generator.
 * --------------------------------------------------------------------
 */
{
    *x = seed;
}


void TestRandom(void)
/* -------------------------------------------------------------------
 * Use this (optional) procedure to test for a correct implementation.
 * -------------------------------------------------------------------
 */
{
    long   i;
    long   x;
    double u;
    
    PutSeed(1,1);                                /* set initial state to 1 */
    for(i = 0; i < 10000; i++)
        u = Random(1);
    GetSeed(&x);                               /* get the new state      */
    if (x == CHECK)
        printf("\n The implementation of Random is correct\n");
    else
        printf("\n\a ERROR - the implementation of Random is not correct\n");
}


double Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
    //return (a + (long) ((b - a + 1) * Random(1)));
    return Random(1);
}

double GetDemand(void)
/* ------------------------
 * generate the next demand
 * ------------------------
 */
{
    return (Equilikely(10, 50));
}

double Uniform(double a, double b){
    //return (a + (b - a) * Random(0));
    return Random(0);
}

double GetDeliveryLag(void){
    return Uniform(0.0,1.0);
}


int main(void){
    long index = 0;
    PutSeed(123456789, 1);
    PutSeed(123456789, 0);
    while(index < STOP){
        index++;
        printf("Demand is %6.2f and Delivery Lag is %6.2f\n", GetDemand(), GetDeliveryLag());
        
    }
}
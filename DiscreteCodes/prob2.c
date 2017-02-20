//
//  prob2.c
//  
//
//  Created by Geethanjali Jeevanatham on 10/4/15.
//
//

#include <stdio.h>
#include <time.h>


#define MODULUS    2147483647UL /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static unsigned long seed = DEFAULT;    /* seed is the state of the generator        */


double Random(void)
/* ---------------------------------------------------------------------
 * Random is a Lehmer generator that returns a pseudo-random real number
 * uniformly distributed between 0.0 and 1.0.  The period is (m - 1)
 * where m = 2,147,483,647 amd the smallest and largest possible values
 * are (1 / m) and 1 - (1 / m) respectively.
 * ---------------------------------------------------------------------
 */
{
    const unsigned long Q = MODULUS / MULTIPLIER;
    const unsigned long R = MODULUS % MULTIPLIER;
    unsigned long t;
    unsigned long temp1,temp2;
    
    temp1 = MULTIPLIER * (seed % Q);
    temp2 = R * (seed / Q);
    
    if(temp1 < temp2){
        seed = temp1 - temp2 + MODULUS;
    }
    else if(temp1 > temp2){
        seed = temp1 - temp2;
    }
    
    
    return seed;
}


void PutSeed(unsigned long x)
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
    
    if (x > 0UL)
        x = x % MODULUS;                          /* correct if x is too large  */
    /*if (x < 0UL)
        x = ((unsigned long) time((time_t *) NULL)) % MODULUS;*/
    if (x == 0UL)
        while (!ok) {
            printf("\nEnter a positive integer seed (9 digits or less) >> ");
            scanf("%ld", &x);
            ok = (0UL < x) && (x < MODULUS);
            if (!ok)
                printf("\nInput out of range ... try again\n");
        }
    seed = x;
}


void GetSeed(unsigned long *x)
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
    unsigned long   x;
    double u;
    
    PutSeed(1);                                /* set initial state to 1 */
    for(i = 0; i < 10000; i++)
        u = Random();
    GetSeed(&x);                               /* get the new state      */
    if (x == CHECK)
        printf("\n The implementation of Random is correct\n");
    else
        printf("\n\a ERROR - the implementation of Random is not correct\n");
}

int main(void){
    unsigned long x;
    PutSeed(1);
    while(x!=1){
        x = Random();
        printf("x is %lu\n",x);
    }
}
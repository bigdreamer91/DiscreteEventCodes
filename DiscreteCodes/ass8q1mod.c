//
//  prob4mod.c
//  
//
//  Created by Geethanjali Jeevanatham on 10/3/15.
//
//

//
//  prob4.c
//
//
//  Created by Geethanjali Jeevanatham on 10/3/15.
//
//

#include <stdio.h>
#include <time.h>



#define STOP     100000                      /* number of time intervals       */
#define sqr(x)   ((x) * (x))
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static long seed = DEFAULT;    /* seed is the state of the generator        */
static long seedone = DEFAULT;
int a[52] = {
               1,2,3,4,5,6,7,8,9,10,11,12,13,
               1,2,3,4,5,6,7,8,9,10,11,12,13,
               1,2,3,4,5,6,7,8,9,10,11,12,13,
               1,2,3,4,5,6,7,8,9,10,11,12,13,
};

double Random()
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
    
    
    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    if (t > 0)
        seed = t;
    else
        seed = t + MODULUS;
    
    return ((double) seed / MODULUS);
}


void PutSeed(long x)
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
    
    seed = x;
    
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
    
    PutSeed(1);                                /* set initial state to 1 */
    for(i = 0; i < 10000; i++)
        u = Random();
    GetSeed(&x);                               /* get the new state      */
    if (x == CHECK)
        printf("\n The implementation of Random is correct\n");
    else
        printf("\n\a ERROR - the implementation of Random is not correct\n");
}


long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
    return (a + (long) ((b - a + 1) * Random()));
}

int main(void){
    
    long index = 0,total = 0;
    int m, i, j, temp, k, score;
    for(i=0;i<52;i++){
        j = Equilikely(i , 51);
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    for(i=0;i<52;i++){
        printf("%d    ",a[i]);
        k++;
    }
    printf("\na size is %d\n",k);
    while(index < STOP){
        index++;
        //printf("index is %ld     ",index);
        i = 0;
        score = 0;
        //k = 52;
        //printf("score is %d\n",score);
        
        
        for(m=0; m<2; m++){
            j = Equilikely(1,52);
            //printf("j is %d a[j-1] is %d\n",j,a[j-1]);
            if(a[j-1] > score){
                score = a[j-1];
                i++;
            }
            
            printf("score is %d\n", score);
            /*temp = a[j-1];
            //printf("temp is %d and a[k] is %d\n", temp, a[k-1]);
            a[j-1] = a[k-1];
            a[k-1] = temp;
            k--;
            //printf("k is %d\n",k);*/
           
        }
        printf("%d\n", score);
        if(i == 2){
            total++;
        }
        
    }
    printf(" total is %ld Avg Total is %6.2f\n", total, (double)total/index);
}

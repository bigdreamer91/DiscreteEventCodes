//
//  prob3.c
//  
//
//  Created by Geethanjali Jeevanatham on 10/4/15.
//
//

#include <stdio.h>
#include <time.h>



#define STOP     10000                     /* number of time intervals       */
#define sqr(x)   ((x) * (x))
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static long seed = DEFAULT;    /* seed is the state of the generator        */
static long seedone = DEFAULT;

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
    int n,i,m,j,x,current,yes,temp,count = 0;
    long index = 0;
    printf("Enter value of n: ");
    scanf("%d",&n);
    int a[n+1];
    while(index < STOP){
        printf("\n\nArray --> ");
        for(i=1;i<=n;i++){
            a[i] = i;
            printf("%d  ",a[i]);
        }        index++;
        printf("\nindex is %ld\n",index);
        x=1;
        current=1;
        for(m=1;m<=n;m++){
            printf("loop m is %d\n",m);
            if(m==current){
                printf("inside m==current loop\n");
                j = Equilikely(x,n);
                printf("j is %d a[j] is %d\n",j, a[j]);
                if(a[j]==1){
                    yes = 1;
                    break;
                }
                else if(a[j]==n){
                    yes = 0;
                    break;
                }
                else if(a[j] > current && a[j] < n){
                    temp = a[current];
                    a[current] = a[j];
                    a[j] = temp;
                    current = a[current];
                    printf("modified current %d\n",current);
                    x++;
                }
                printf("Modified Array --> ");
                for(i=1;i<=n;i++){
                    //a[i] = i;
                    printf("%d  ",a[i]);
                }
                printf("\nx is %d\n",x);
            }
            else if(m < current){
                printf("inside m < current loop\n");
                x++;
                printf("x is %d\n",x);
            }
            
        }
        printf("The passenger gets his seat is %d\n",yes);
        count += yes;
        printf("count is %d\n",count);
    }
    printf("Probability passenger gets seat is %6.2f\n", (double)count/index);
}

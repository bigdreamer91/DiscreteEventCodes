
/* ------------------------------------------------------------------------- 
 * This program - an extension of program ssq1.c - simulates a single-server 
 * FIFO service node using Exponentially distributed interarrival times and 
 * Uniformly distributed service times (i.e. a M/U/1 queue). 
 *
 * Name              : ssq2.c  (Single Server Queue, version 2)
 * Author            : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 9-11-98
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>  
#include <time.h>


#define LAST         10000L                   /* number of jobs processed */
#define START        0.0                      /* initial time             */ 
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */
#define MULTIPLIER 48271L      /* use 16807 for the "minimal standard"      */
#define CHECK      399268537L  /* use 1043616065 for the "minimal standard" */
#define DEFAULT    123456789L  /* initial seed, use 0 < DEFAULT < MODULUS   */

static long seed = DEFAULT;    /* seed is the state of the generator        */


double Random(void)
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
    long t;
    
    
    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    //printf("t value is %ld\n",t);
    if (t > 0)
        seed = t;
    else
        seed = t + MODULUS;
    //printf("Seed is %ld\n",seed);
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



   double Exponential(double m)                 
/* ---------------------------------------------------
 * generate an Exponential random variate, use m > 0.0 
 * ---------------------------------------------------
 */
{
  double val = Random();
    //printf("Random val (Exponential) is %6.2f\n",val);
  return (-m * log(1.0 - val));
}


   double Uniform(double a, double b)           
/* --------------------------------------------
 * generate a Uniform random variate, use a < b 
 * --------------------------------------------
 */
{
    double val = Random();
    //printf("Random val (Uniform) is %6.2f\n",val);
  return (a + (b - a) * val);
}


   double GetArrival(void)
/* ------------------------------
 * generate the next arrival time
 * ------------------------------
 */ 
{       
  static double arrival = START;                                        

  arrival += Exponential(2.0);
  return (arrival);
}


   double GetService(void)
/* ------------------------------
 * generate the next service time
 * ------------------------------
 */ 
{
  return (Exponential(1.4));
}


  int main(void)
{
  long   index     = 0;                         /* job index            */
  double arrival   = START;                     /* time of arrival      */
  double delay;                                 /* delay in queue       */
  double service;                               /* service time         */
  double wait;                                  /* delay + service      */
  double departure = START;                     /* time of departure    */
  struct {                                      /* sum of ...           */
    double delay;                               /*   delay times        */
    double wait;                                /*   wait times         */
    double service;                             /*   service times      */
    double interarrival;                        /*   interarrival times */
  } sum = {0.0, 0.0, 0.0};  

  PutSeed(987654321);

  while (index < LAST) {
   
    index++;
    arrival      = GetArrival();
    if (arrival < departure)
      delay      = departure - arrival;         /* delay in queue    */
    else
      delay      = 0.0;                         /* no delay          */
    
    //printf("arrival is %6.2f\n",arrival);
    service      = GetService();
    //printf("%6.2f\n",service);
    wait         = delay + service;
    //printf("%6.2f\n",wait);
    departure    = arrival + wait;              /* time of departure */
    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
  } 
  sum.interarrival = arrival - START;

  printf("\nfor %ld jobs\n", index);
  printf("   departure ............... = %6.2f\n",departure);
  printf("   average interarrival time = %6.2f\n", sum.interarrival / index);
  printf("   average wait ............ = %6.2f\n", sum.wait / index);
  printf("   average delay ........... = %6.2f\n", sum.delay / index);
  printf("   average service time .... = %6.2f\n", sum.service / index);
  printf("   average # in the node ... = %6.2f\n", sum.wait / departure);
  printf("   average # in the queue .. = %6.2f\n", sum.delay / departure);
  printf("   utilization ............. = %6.2f\n", sum.service / departure); 

  return (0);
}

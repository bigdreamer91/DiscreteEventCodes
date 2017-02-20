/* ------------------------------------------------------------------------
 * This program illustrates an array-based algorithm for tallying a 
 * continuous-data histogram for data read from standard input (stdin).
 * Like program uvs, a compiled version of this program supports file
 * redirection.
 *
 * The MIN, MAX, K parameters are "tuned" to the datafile uvs.dat.
 * For other datafiles these parameters must be adjusted -- you might
 * want to process the datafile with program uvs first to get a handle on
 * appropriate values for these three parameters.
 * 
 * Name              : cdh.c  (Continuous Data Histogram)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 12-27-95
 * ------------------------------------------------------------------------ 
 */

#include <stdio.h>
#include <math.h> 
#include <time.h>

#define  RUNS    10000
#define  MIN     0.0
#define  MAX     2.0
#define  K       20                          /* number of histogram bins   */
#define  DELTA   ((MAX - MIN) / K)           /* histogram bin size (width) */
#define  sqr(x)  ((x) * (x))
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



  int main(void)
{
  double x;                                      /* data value          */
  long   j;                                      /* histogram bin index */
  long   index    = 0;                           /* sample size         */
  long   count[K] = {0.0};                       /* bin count           */
  double midpoint[K];                            /* bin midpoint        */
  struct {                                       
    long lo;
    long hi;
  } outliers      = {0, 0};
  double sum      = 0.0;
  double sumsqr   = 0.0;
  double mean;
  double stdev;

  for (j = 0; j < K; j++) 
    midpoint[j] = MIN + (j + 0.5) * DELTA;
    
  PutSeed(12345);

  while (index < RUNS) {                         /* tally the data */
    //scanf("%lf\n", &x);
    x = Random() + Random();
    index++;
    if ((x >= MIN) && (x < MAX)) {
      j = (long) ((x - MIN) / DELTA);
      count[j]++;
    }
    else if (x < MIN)
      outliers.lo++;
    else
      outliers.hi++;
  }

  for (j = 0; j < K; j++)                        /* histogram mean */
    sum += midpoint[j] * count[j];
  mean   = sum / index;

  for (j = 0; j < K; j++)                        /* histogram stdev */
    sumsqr += sqr(midpoint[j] - mean) * count[j];
  stdev     = sqrt(sumsqr / index);

  printf("  bin     midpoint     count   proportion    density\n\n");
  for (j = 0; j < K; j++) { 
    printf("%5ld", j + 1);                                    /* bin        */
    printf("%12.3f", midpoint[j]);                            /* midpoint   */
    printf("%10ld", count[j]);                                /* count      */
    printf("%12.3f", (double) count[j] / index);              /* proportion */
    printf("%12.3f\n", (double) count[j] / (index * DELTA));  /* density    */
  }
  printf("\nsample size .... = %7ld\n", index);
  printf("mean ........... = %7.3f\n", mean);
  printf("stdev .......... = %7.3f\n\n", stdev);
  if (outliers.lo > 0)
    printf("NOTE: there were %ld low outliers\n", outliers.lo);
  if (outliers.hi > 0)
    printf("NOTE: there were %ld high outliers\n", outliers.hi);

  return (0);
}

/* ------------------------------------------------------------------------- 
 * A Monte Carlo simulation of Galileo's three dice experiment. 
 * 
 * Name              : galileo.c 
 * Author            : Steve Park & Dave Geyer 
 * Language          : ANSI C
 * Latest Revision   : 9-11-98
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <time.h>


#define N 10000L                          /* number of replications */
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


   long Equilikely(long a, long b)        
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b 
 * ------------------------------------------------
 */
{
  return (a + (long) ((b - a + 1) * Random()));
}


  int main(void)
{
  long   i;                               /* replication index      */
  long   tempa, tempb;
  long   x;                               /* sum of three dice      */
  long   count[19] = {0};                 /* histogram              */
  long   val[13]  = {1,2,2,3,3,4,4,5,5,6,6,6,6};
  double p[19]     = {0.0};               /* probability estimates  */

  PutSeed(0);

  for (i = 0; i < N; i++) {
    tempa = Equilikely(1,13);
    tempb = Equilikely(1,13);

    x = val[tempa-1] + val[tempb-1];
    count[x]++;
  }

  for (x = 3; x < 19; x++)                /* estimate probabilities */
    p[x] = (double) count[x] / N;

  printf("\nbased on %ld replications ", N);
  printf("the estimated probabilities are:\n\n");
  for (x = 3; x < 19; x++)
    printf("p[%2ld] = %5.3f\n", x, p[x]);
  printf("\n");

  return (0);
}

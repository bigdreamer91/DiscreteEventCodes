/* ------------------------------------------------------------------------- 
 * This program - an extension of program sis1.c - simulates a simple (s,S) 
 * inventory system using Equilikely distributed demands. 
 * 
 * Name              : sis2.c  (Simple Inventory System, version 2)
 * Authors           : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 8-28-97 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <time.h>


#define MINIMUM  60                       /* 's' inventory policy parameter */
#define MAXIMUM  80                        /* 'S' inventory policy parameter */
#define STOP     100                       /* number of time intervals       */
#define sqr(x)   ((x) * (x))
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


long Equilikely(long a, long b)
/* ------------------------------------------------
 * generate an Equilikely random variate, use a < b
 * ------------------------------------------------
 */
{
    return (a + (long) ((b - a + 1) * Random(1)));
}

long GetDemand(void)
/* ------------------------
 * generate the next demand
 * ------------------------
 */
{
    return (Equilikely(10, 50));
}

double Uniform(double a, double b){
    return (a + (b - a) * Random(0));
}

double GetDeliveryLag(void){
    return Uniform(0.0,1.0);
}


  int main(void)
{
  long index     = 0;                      /* time interval index     */
  long inventory = MAXIMUM;                /* current inventory level */
  long demand;                             /* amount of demand        */
  long order;                              /* amount of order         */
  double lag;
  double l_t_value;
  long new_inventory;
  struct {                                 /* sum of ...              */
    double setup;                          /*   setup instances       */
    double holding;                        /*   inventory held (+)    */
    double shortage;                       /*   inventory short (-)   */
    double order;                          /*   orders                */
    double demand;                         /*   demands               */
  } sum = {0.0, 0.0, 0.0, 0.0, 0.0}; 

  PutSeed(123456789,1);
  PutSeed(123456789,0);

  while (index < STOP) {
      l_t_value = 0;
    index++;
      printf("Inventory is %ld\n",inventory);
    if (inventory < MINIMUM) {             /* place an order */
        printf("Inside less than minimum if loop \n");
      order         = MAXIMUM - inventory;
        printf("Order is %ld\n",order);
      sum.setup++;
        printf("Setup is %6.2f\n",sum.setup);
      sum.order    += order;
        printf("Sum Order is %6.2f\n",sum.order);
      lag = GetDeliveryLag();
        printf("Delivery lag is %6.2f\n", lag);
        demand = GetDemand();
        printf("Demand is %ld\n",demand);
        sum.demand += demand;
        printf("Summ of demand is %6.2f\n",sum.demand);
        new_inventory = inventory - (int)(demand * lag);
        printf("inventory - (demand * lag) is %ld", new_inventory);
      
        if(inventory < 0 && new_inventory < 0){
            printf("Inside first if cond\n");
            sum.shortage += (-0.5 * (inventory + new_inventory) * lag);
            printf("shortage cost is %6.2f and sum.shortage is %6.2f\n", (-0.5 * (inventory + new_inventory) * lag), sum.shortage);
            l_t_value += (-0.5 * (inventory + new_inventory) * lag);
        }
        else if(inventory > 0 && new_inventory < 0){
            printf("Inside second if cond\n");
            sum.holding += sqr(inventory) / (2.0 * demand);
            l_t_value += sqr(inventory) / (2.0 * demand);
            sum.shortage += sqr((int)(demand * lag) - inventory) / (2.0 * demand);
            l_t_value += sqr((int)(demand * lag) - inventory) / (2.0 * demand);
            printf("shortage cost is %6.2f and sum.shortage is %6.2f\n", (sqr((int)(demand * lag) - inventory) / (2.0 * demand)), sum.shortage);
            printf("holding cost is %6.2f and sum.holding cost is %6.2f\n", (sqr(inventory) / (2.0 * demand)),sum.holding);
        }
        else if(inventory > 0 && new_inventory > 0){
            printf("Inside third if cond\n");
            //printf(" inventory + new inventory %ld, ", (inventory + new_inventory))
            sum.holding += (0.5 * (inventory + new_inventory) * lag);
            l_t_value += (0.5 * (inventory + new_inventory) * lag);
            printf("holding cost is %6.2f and sum.holding cost is %6.2f\n", (0.5 * (inventory + new_inventory) * lag),sum.holding);
        }
        printf("Outside the if con\n");
        sum.holding += 0.5 * ((MAXIMUM - (int)(lag * demand)) + (MAXIMUM - demand)) * (1 - lag);
        l_t_value += 0.5 * ((MAXIMUM - (int)(lag * demand)) + (MAXIMUM - demand)) * (1 - lag);
        printf("holding cost is %6.2f and sum.holding cost is %6.2f\n", (0.5 * (MAXIMUM - (int)(lag * demand)) * (MAXIMUM - demand) * (1 - lag)),sum.holding);
        printf("l(t) value calculated on this interval is %6.2f\n", l_t_value);
        inventory = MAXIMUM;
    }
    else {                                  /* no order       */
        printf("Inside the else loop inventory > s\n");
    demand          = GetDemand();
        printf("Demand is %ld\n", demand);
    sum.demand     += demand;
        printf("Sum.demand is %6.2f\n", sum.demand);
        if(inventory > demand){
            sum.holding  += (inventory - 0.5 * demand);
            printf("holding cost is %6.2f and sum.holding is %6.2f\n",(inventory - 0.5 * demand), sum.holding);
        }
        else{
            sum.holding  += sqr(inventory) / (2.0 * demand);
            printf("holding cost is %6.2f and sum.holding is %6.2f\n",(sqr(inventory) / (2.0 * demand)), sum.holding);
            sum.shortage += sqr(demand - inventory) / (2.0 * demand);
            printf("Shortage cost is %6.2f and sum.shortage is %6.2f\n", (sqr(demand - inventory) / (2.0 * demand)), sum.holding);
        }
    }
      printf("Outside the main if else loop\n");
    inventory     -= demand;
  } 

  if (inventory < MAXIMUM) {               /* force the final inventory to */
    order      = MAXIMUM - inventory;      /* match the initial inventory  */
    sum.setup++;
    sum.order += order;
    inventory += order;
  }

    printf("Avg shortage %6.2f\n",sum.shortage/index);
    printf("Avg holding %6.2f\n",sum.holding/index);
    printf("Avg setup %6.2f\n",sum.setup/index);
    printf("Dependent cost is %6.2f\n", (700 * (sum.shortage/index))+(25 * (sum.holding/index))+ (1000 * (sum.setup/index)));
  return (0);
}

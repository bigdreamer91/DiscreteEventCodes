/* -------------------------------------------------------------------------  
 * This program is a next-event simulation of a simple inventory system with 
 * a Poisson demand process, backlogging, and a Uniform(0,1) delivery lag. 
 *
 * Name              : sis3.c  (Simple Inventory System, version 3) 
 * Author            : Steve Park & Dave Geyer 
 * Language          : ANSI C 
 * Latest Revision   : 10-19-98 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>
#include <math.h>
#include "rngs.h"

#define MINIMUM    20             /* 's' inventory policy parameter >= 0 */
#define MAXIMUM    80             /* 'S' inventory policy parameter > s  */
#define START      0.0
#define STOP       100.0
#define INFINITY   (100.0 * STOP)
 

   double Exponential(double m)
/* ---------------------------------------------------
 * generate an Exponential random variate, use m > 0.0 
 * ---------------------------------------------------
 */
{
  return (-m * log(1.0 - Random()));
}


   double Uniform(double a, double b)  
/* --------------------------------------------
 * generate a Uniform random variate, use a < b 
 * --------------------------------------------
 */
{
  return (a + (b - a) * Random());  
}


   double GetDemand(void)
/* --------------------------------------------------------------
 * generate the next demand instance (time) with rate 30 per time 
 * interval and exactly one unit of demand per demand instance 
 * --------------------------------------------------------------
 */
{             
  static double time = START;
                            
  SelectStream(0);
  time += Exponential(1.0 / 30.0);
  //printf("%ld\n",(long)time);
  return (time);
}


   double GetLag(void)
/* ------------------------------
 * generate a delivery lag (time) 
 * ------------------------------
 */
{                                         
  SelectStream(1);
  return (Uniform(0.5, 2.0));
}


   double Min(double a, double b, double c)    
/* ----------------------------------------
 * return the smallest of a, b, c
 * ----------------------------------------
 */
{
  double t = a;

  if (b < t)
    t = b;
  if (c < t)
    t = c;
  return (t);
}


  int main(void)
{
  long inventory = MAXIMUM;            /* current inventory level */
    long order[3]     = {0,0,0};                  /* current order level     */
    double lag = 0.0;
    int i,l=0,k=0,m=0;
    double j;
  struct {
    double demand;                     /* next demand time                */
    double review;                     /* next inventory review time      */
    double arrive[3];                     /* next order arrival time         */
    double current;                    /* current time                    */
    double next;                       /* next (most imminent) event time */
  } t;
  struct {                             /* sum of -                */
    double setup;                      /*   setup instances       */
    double holding;                    /*   inventory held (+)    */
    double shortage;                   /*   inventory short (-)   */
    double order;                      /*   orders                */
    double demand;                     /*   demands               */
    double lag;                        /*   lags                  */
  } sum          = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  PlantSeeds(0);
  t.current = START;
  t.demand  = GetDemand();              /* schedule the first demand */
  t.review  = t.current + 1.0;          /* schedule the first review */
  t.arrive[0]  =   t.arrive[1] = t.arrive[2] = INFINITY;              /* no order arrival pending  */

  while (t.current < STOP) {
      printf("t.current - %6.2f and t.demand - %6.2f and k - %d and order[0] - %ld and order[1] - %ld and order[2] - %ld and lag = %6.2f and m - %d, t.arrive[0] - %6.2f and t.arrive[1] - %6.2f and t.arrive[2] - %6.2f and inventory - %ld\n",t.current,t.demand,k, order[0], order[1], order[2],lag,m,t.arrive[0],t.arrive[1], t.arrive[2],inventory);
    t.next          = Min(t.demand, t.review, t.arrive[0]);
    if (inventory > 0)
      sum.holding  += (t.next - t.current) * inventory;
    else
      sum.shortage -= (t.next - t.current) * inventory;
    t.current       = t.next;

    if (t.current == t.demand) {        /* process an inventory demand */
      sum.demand++;
      inventory--;
      t.demand = GetDemand();
    }

    else if (t.current == t.review) {   /* process inventory review */
      if (inventory < MINIMUM) {
          lag = 0.0;
          if(order[0] > 0){
             order[k]      = MAXIMUM - inventory - order[0];
              k++;
          }
          else if(order[0] == 0){
              order[0] = MAXIMUM - inventory;
              k++;
          }
          //order = MAXIMUM - inventory;
        lag        = GetLag();
        sum.setup++;
        sum.order += order[k-1];
        sum.lag   += lag;
        t.arrive[m]   = t.current + lag;
          m++;
      }
      t.review  = t.current + 1.0;
    }

    else {                           /* process an inventory order arrival*/
      inventory += order[0];
      order[0]      = 0;
      t.arrive[0]   = INFINITY;
        j = t.arrive[0];
        l = 0;
        for(i=0;i<3;i++){
            if(t.arrive[i] < j){
                j = t.arrive[i];
                l = i;
            }
        }
        if(l>0){
        t.arrive[0] = j;
        t.arrive[l] = INFINITY;
        order[0] = order[l];
        order[l] = 0;
            m--;
            k--;
        }
        else{
            m--;
            k--;
        }
    }
  } 

  if (inventory < MAXIMUM) {          /* adjust the final inventory level */
    order[0]      = MAXIMUM - inventory;
    sum.setup++;
    sum.order += order[0];
    inventory += order[0];
  }

 printf("\nfor %ld time intervals ", (long) STOP);
  printf("with an average demand of %6.2f\n", sum.demand / STOP);
  if (sum.setup > 0.0)
    printf("an average lag of %4.2f", sum.lag / sum.setup);
  printf(" and policy parameters (s, S) = (%d, %d)\n\n", MINIMUM, MAXIMUM);
  printf("   average order ............ = %6.2f\n", sum.order / STOP);
  printf("   setup frequency .......... = %6.2f\n", sum.setup / STOP);
  printf("   average holding level .... = %6.2f\n", sum.holding / STOP);
  printf("   average shortage level ... = %6.2f\n\n", sum.shortage / STOP);

  return (0);
}

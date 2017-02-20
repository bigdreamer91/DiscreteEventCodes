
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

#include "rngs.h"


#define LAST         10000L                   /* number of jobs processed */
#define START        0.0                      /* initial time             */ 
#define MODULUS    2147483647L /* DON'T CHANGE THIS VALUE                   */


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
    SelectStream(0);
  arrival += Exponential(2.0);
  return (arrival);
}


   double GetService(void)
/* ------------------------------
 * generate the next service time
 * ------------------------------
 */ 
{
   SelectStream(1);
  return (Uniform(1.0,2.0));
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

  //PutSeed(987654321);
    PlantSeeds(123456789);

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

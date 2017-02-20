
/* -------------------------------------------------------------------------
 * This program simulates a single-server FIFO service node using arrival
 * times and service times read from a text file.  The server is assumed
 * to be idle when the first job arrives.  All jobs are processed completely
 * so that the server is again idle at the end of the simulation.   The
 * output statistics are the average interarrival time, average service
 * time, the average delay in the queue, and the average wait in the service 
 * node. 
 *
 * Name              : ssq1.c  (Single Server Queue, version 1)
 * Authors           : Steve Park & Dave Geyer
 * Language          : ANSI C
 * Latest Revision   : 9-01-98
 * Compile with      : gcc ssq1.c 
 * ------------------------------------------------------------------------- 
 */

#include <stdio.h>                              

#define FILENAME   "ssq1.dat"                  /* input data file */
#define START      0.0

/* =========================== */
   double GetArrival(FILE *fp)                 /* read an arrival time */
/* =========================== */
{ 
  double a;

  fscanf(fp, "%lf", &a);
  return (a);
}

/* =========================== */
   double GetService(FILE *fp)                 /* read a service time */
/* =========================== */
{ 
  double s;

  fscanf(fp, "%lf\n", &s);
  return (s);
}

/* ============== */
   int main(void)
/* ============== */
{
  FILE   *fp;                                  /* input data file      */
  long   index     = 0;                        /* job index            */
  long   jobs      = 0;
  double attime    = 400;
  double arrival   = START;                    /* arrival time         */
  double delay;                                /* delay in queue       */
  double maxdelay = 0.0;
  double service;                              /* service time         */
  double wait;                                 /* delay + service      */
  double departure = START;                    /* departure time       */
  struct {                                     /* sum of ...           */
    double delay;                              /*   delay times        */
    double wait;                               /*   wait times         */
    double service;                            /*   service times      */
    double interarrival;                       /*   interarrival times */
  } sum = {0.0, 0.0, 0.0};

  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open input file %s\n", FILENAME);
    return (1);
  }

  while (!feof(fp)) {
    index++;
    arrival      = GetArrival(fp);
    if (arrival < departure) {
      delay      = departure - arrival;        /* delay in queue    */
      if (delay > maxdelay)
        maxdelay = delay;
    }
    else {
      delay      = 0.0;                        /* no delay          */
    }
    service      = GetService(fp);
    wait         = delay + service;
    departure    = arrival + wait;             /* time of departure */
    if (attime > arrival && attime < departure)
        jobs++;
    sum.delay   += delay;
    sum.wait    += wait;
    sum.service += service;
  }
  sum.interarrival = arrival - START;

  printf("\nfor %ld jobs\n", index);
  printf("no. of jobs in service node at %6.2f is = %ld\n", attime,jobs);
  printf("   average interarrival time = %6.2f\n", sum.interarrival / index);
  printf("   max delay is = %6.2f\n",maxdelay);
  printf("   average service time .... = %6.2f\n", sum.service / index);
  printf("   average delay ........... = %6.2f\n", sum.delay / index);
  printf("   average wait ............ = %6.2f\n", sum.wait / index);
  printf("   departure is %6.2f\n",departure);
  printf("   arrival is %6.2f\n", arrival);
  printf("   portion of jobs in queue is %6.2f\n", ((index / departure)*(sum.delay/index)));
  printf("   server utilization is %6.2f\n", ((index / departure)*(sum.service/index)));
  printf("   traffic intensity is %6.2f\n", ((index / arrival)*(sum.service/index)));

  fclose(fp);
  return (0);
}

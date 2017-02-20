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
#include <stdlib.h>
#include <time.h>
#include "rng.h"


#define STOP     360000                       /* number of time intervals       */
#define sqr(x)   ((x) * (x))

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
    long index     = 0;                      /* time interval index     */
    long x;
    PutSeed(721333692);
    
    while (index < STOP) {
        index++;
        x = labs(Equilikely(1, 6) - Equilikely(1, 6));
        printf("%ld\n",x);
    }
    
        return (0);
}

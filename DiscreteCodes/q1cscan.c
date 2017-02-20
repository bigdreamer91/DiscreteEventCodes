//
//  linkedmain.c
//  assignmentprob
//
//  Created by Geethanjali Jeevanatham on 12/11/15.
//  Copyright (c) 2015 Geethanjali Jeevanatham. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "rvgs.h"
#include "rngs.h"

#define START         0.0              /* initial time                   */
#define STOP      2000100.0              /* terminal (close the door) time */
#define INFTY    (1000000000.0 * STOP)      /* must be much larger than STOP  */

struct node{
    long index;
    long cylindernum;
    long numsectors;
    double latency;
    double arrival;
    double completion;
    struct node* next;
}*head;

double Min(double a, double c)
/* ------------------------------
 * return the smaller of a, b
 * ------------------------------
 */
{
    if (a < c)
        return (a);
    else
        return (c);
}

double GetArrival()
/* ---------------------------------------------
 * generate the next arrival time, with rate 1/2
 * ---------------------------------------------
 */
{
    static double arrival = START;
    
    SelectStream(0);
    arrival += Exponential(2.0);
    return (arrival);
}

void delete(long position){
    struct node* temp1, *temp2;
    long size=0,i;
    temp1 = head;
    while(temp1!=NULL){
        temp1 = temp1->next;
        size++;
    }
    
    if(position==1){
        temp2 = head;
        head = temp2->next;
        temp2 = NULL;
    }
    else if(position==size){
        temp1 = head;
        for(i=0;i<size-2;i++){
            temp1 = temp1->next;
        }
        temp1->next = NULL;
    }
    else{
        temp1 = head;
        for(i=0;i<position-2;i++){
            temp1 = temp1->next;
        }
        temp2 = temp1->next;
        temp1->next = temp2->next;
        temp2->next = NULL;
    }
    
}

void append(struct node* temp){
    
    int true = 1;
    if(head->next == NULL){
        head->next = temp;
        printf("added at beginning\n");
    }
    
    else
    {
        
        struct node *current = head;
        while(true) {
            if(current->next == NULL)
            {
                current->next = temp;
                printf("added later\n");
                break;
            }
            current = current->next;
        };
    }
}

int main(void){
    
    struct node* temp, *p, *q, *g, *temp1, *temp2, *temp3, *final;
    
    double tarrival,tcompletion,t,completion,seek,latency,transfer=0.004,seekmin=0.0,delay,longdelay,sumdelay=0.0,temptcompletion,sumseek=0.0;
    int s=0,r=0;
    long position,cylindernum,numsectors,numbers=0,index=0,i,headcylinder=0,d,iterate=0,l,cylindermin,cylindermax,lowestposition,equalposition,maxposition,tempcylinder,sumsectors=0,sumqueue=0,count=0;
    printf("Start\n");
    
    tarrival = GetArrival();
    
    
    head = NULL;
    
   
    tcompletion = INFTY;
   
    
    while ((tarrival<STOP)||(numbers>0)) {
        t = Min(tarrival, tcompletion);
     
        if(t==tarrival){
            count++;
            numbers++;
            latency=0.0;
            SelectStream(1);
            cylindernum = Equilikely(0, 12000);
            SelectStream(2);
            numsectors = Geometric(0.9);
            sumsectors+=numsectors;
            SelectStream(3);
            for(i=0;i<numsectors;i++){
                latency += Uniform(0, 6);
               
            }
            
            if(numbers==1){
                
                seek=0.0;
                
                if(headcylinder==cylindernum){
                    seek = 0.0;
                }
                else{
                    d = labs(headcylinder - cylindernum);
                 
                    seek = (double)((1 + sqrt(d))/2);
                    headcylinder = cylindernum;
                }
                
              
                sumseek+=seek;
                completion = (double)(seek + latency + (numsectors * transfer));
                tcompletion = t + completion;
               

            }
            else{
            index++;
                temp = malloc(sizeof(struct node));
                temp->index = index;
                temp->cylindernum = cylindernum;
                temp->numsectors = numsectors;
                temp->latency = latency;
                temp->arrival = tarrival;
                temp->completion = INFTY;
                temp->next = NULL;
                
                if(head==NULL){
                   
                    head =temp;
                }
                else{
                    append(temp);
                }
            }
            tarrival = GetArrival();
         
            if(tarrival > STOP){
                tarrival = INFTY;
            }
            
        }
        else{
            q = head;
            numbers--;
            sumqueue+=numbers;
          
            s = 0;
            r = 0;
            if(numbers>0){
                
                lowestposition = 0;
                equalposition = 0;
                maxposition = 0;
                iterate = 0;
                
                cylindermin = headcylinder;
                
                while(q!=NULL){
                    iterate++;
                    
                    if(q->cylindernum < cylindermin){
                        cylindermin = q->cylindernum;
                        lowestposition = iterate;
                        temp1 = q;
                    }
                    else if(q->cylindernum == headcylinder){
                        if(s==0){
                            equalposition = iterate;
                            temp2 = q;
                            s++;
                        }
                    }
                    else if(q->cylindernum > headcylinder){
                        if(r==0){
                            cylindermax = q->cylindernum;
                            maxposition = iterate;
                            temp3 = q;
                            r++;
                        }
                        else if(q->cylindernum < cylindermax){
                            cylindermax = q->cylindernum;
                            maxposition = iterate;
                            temp3 = q;
                        }
                    }
                    q = q->next;
                }
                
                          
                tempcylinder = headcylinder;
                
                if(equalposition != 0){
                    l = equalposition;
                    headcylinder = temp2->cylindernum;
                    final = temp2;
                }
                else if(maxposition != 0){
                    l = maxposition;
                    headcylinder = temp3->cylindernum;
                    final = temp3;
                }
                else if(lowestposition != 0){
                    l = lowestposition;
                    headcylinder = temp1->cylindernum;
                    final = temp1;
                }
                
                if(tempcylinder==headcylinder){
                    seek = 0.0;
                }
                else{
                    d = labs(tempcylinder - headcylinder);
                 
                    seek = (double)((1 + sqrt(d))/2);
                    
                }
                
             
                
                
                sumseek+=seek;
                completion = (double)(seek + final->latency + (final->numsectors * transfer));
              

                
                tcompletion = t+completion;
                
                delay = t - final->arrival;
                sumdelay+=delay;
                if(delay>longdelay){
                    longdelay = delay;
                }
                temptcompletion = tcompletion;
                delete(l);
            }
            if(numbers==0){
                tcompletion = INFTY;
            }
         
            
    }
    
    }
        
    printf("count - %ld",count);
    printf("average delay - %6.2f\n",(double)sumdelay/count);
    printf("longest dealy - %6.2f\n",longdelay);
    printf("avg queuelenth - %ld\n",sumqueue/count);
    printf("avg seek - %6.2f\n",sumseek/count);
    printf("sumsectors - %ld\n",sumsectors);
    printf("transfer rate - %6.2f",sumsectors/temptcompletion);
    
       return 0;
}
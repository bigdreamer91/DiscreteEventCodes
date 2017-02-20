
#include <stdio.h>
#include <stdlib.h>
#include "rvgs.h"
#include "rngs.h"

#define START         0.0              /* initial time                   */
#define STOP      1500.0              /* terminal (close the door) time */
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
    arrival += Exponential(1.0);
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
    printf("size - %ld\n",size);
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
    
    struct node* temp, *p, *q, *g, *temp1;
    
    double tarrival,tcompletion,t,tcurrent,completion,seek,latency,transfer=0.004,seekmin=0.0,delay,sumdelay=0,longdelay=0,sumseek=0.0,transferrate = 0.0,temptcompletion,sumqueue=0.0;
    int s=0,r=0;
    long position,cylindernum,numsectors,numbers=0,index=0,i,headcylinder=0,d,iterate=0,l,count=0,sumsectors=0,sumqueuelong=0;
    printf("Start\n");
    
    tarrival = GetArrival();
    
    
    
    head = NULL;
    
   
    tcompletion = INFTY;
  
    tcurrent = START;
    while ((tarrival<STOP)||(numbers>0)) {
        t = Min(tarrival, tcompletion);
        
        if(numbers>0){
            sumqueue+= (t - tcurrent) * (numbers - 1);
        }
        
        tcurrent = t;
        
        if(tcurrent==tarrival){
            numbers++;
            count++;
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
                tcompletion = tcurrent + completion;
                
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
          
            if(numbers>0){
                if(headcylinder==q->cylindernum){
                    seek = 0.0;
                }
                else{
                    d = labs(headcylinder - q->cylindernum);
                    seek = (double)((1 + sqrt(d))/2);
                    headcylinder = q->cylindernum;
                }
                
               
                sumseek+=seek;
                completion = (double)(seek + q->latency + (q->numsectors * transfer));
                tcompletion = tcurrent + completion;
                
                delay = tcurrent - q->arrival;
              
                if(delay>longdelay){
                    longdelay = delay;
                }
                temptcompletion = tcompletion;

                
                delete(1);
            }
            if(numbers==0){
                tcompletion = INFTY;
            }
            
            
        }
    
    }
   
    printf("count - %ld tcurrent - %6.2f\n",count,tcurrent);
    printf("avgdelay - %6.2f\n",(double)sumqueue/index);
    printf("longest dealy - %6.2f\n",longdelay);
    printf("sumqueue - %6.2f\n",sumqueue);
    printf("avg queuelenth - %6.2f\n",sumqueue/tcurrent);
    printf("avg seek - %6.2f\n",sumseek/count);
    printf("transfer rate - %6.2f",sumsectors/tcurrent);
       return 0;
}
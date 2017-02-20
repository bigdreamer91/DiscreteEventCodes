

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM           50
#define START         0.0              /* initial time                   */
#define STOP      10.0              /* terminal (close the door) time */
#define INFINITY   (1000000000.0 * STOP)      /* must be much larger than STOP  */

struct queuenode{
    long index;
    long cylindernum;
    long numsectors;
    double latency;
    double arrival;
    double completion;
    struct queuenode* next;
};

typedef struct queuenode* pointer;

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




int main(void){
    pointer p;
    pointer q;
    pointer root;
    pointer temp;
    root = NULL;
    double tarrival,tcompletion,t,latency,seek,completion,transfer=0.004,seekmin;
    long cylindernum,numsectors,numbers=0,i,head=0,d,index=0,l=0,iterate=0,queuesize=0,s=0,j=0;
    
    
    tarrival = GetArrival();
    printf("Initial tarrival - %6.2f\n",tarrival);
    tcompletion = INFINITY;
    printf("Initial tcompletion - %6.2f\n",tcompletion);
    while((tarrival < STOP)||(numbers > 0)){
        t = Min(tarrival, tcompletion);
        printf("t - %6.2f tarrival - %6.2f tcompletion - %6.2f\n",t,tarrival,tcompletion);
        if(t==tarrival){
            seek = 0.0;
            latency = 0.0;
            numbers++;
            printf("numbers - %ld\n",numbers);
            SelectStream(1);
            cylindernum = Equilikely(0, 12000);
            printf("cylindernum - %ld\n",cylindernum);
            SelectStream(2);
            numsectors = Geometric(0.9);
            printf("numsectors - %ld\n",numsectors);
            SelectStream(3);
            for(i=0;i<numsectors;i++){
                latency += Uniform(0, 6);
                printf("i - %ld val - %6.2f\n",i,latency);
            }
            printf("latency - %6.2f\n",latency);
            if(numbers==1){
                if(head==cylindernum){
                    seek = 0.0;
                }
                else{
                    d = labs(head - cylindernum);
                    printf("d - %ld\n",d);
                    seek = (double)((1 + sqrt(d))/2);
                    head = cylindernum;
                }
                
                printf("seek - %6.2f\n",seek);
                
                completion = (double)(seek + latency + (numsectors * transfer));
                printf("completion - %6.2f\n",completion);
                tcompletion = t+completion;
                printf("tcompletion - %6.2f\n",tcompletion);

            }
            else{
                queuesize++;
                printf("queuesize - %ld\n",queuesize);
                index++;
                printf("index - %ld\n",index);
                temp = malloc(sizeof(struct queuenode));
                temp->index = index;
                temp->cylindernum = cylindernum;
                temp->numsectors = numsectors;
                temp->arrival = tarrival;
                temp->latency = latency;
                temp->completion = tcompletion;
                if(root==NULL){
                    root = temp;
                    root->next = NULL;
                    p = root;
                }
                else{
                    if(p->next == NULL){
                        p->next = temp;
                        p = temp;
                        p->next = NULL;
                    }
                }
            }
            
            tarrival = GetArrival();
            
            if(tarrival > STOP){
                tarrival = INFINITY;
            }
            
        }
        else{
            numbers--;
            printf("numbers - %ld\n",numbers);
            temp = root;
            
            
            if(numbers>0){
                seekmin = 0.0;
                s = 0;
                queuesize--;
                printf("queusize - %ld\n",queuesize);
                while((temp!=NULL)){
                    iterate++;
                    printf("iterate - %ld\n",iterate);
                    
                    if(head== temp->cylindernum){
                        
                        seekmin = 0.0;
                        l = iterate;
                        //seekmin = seek;
                        break;
                    }
                    
                    else{
                        
                        d = labs(head - temp->cylindernum);
                        
                        printf("d - %ld\n",d);
                        
                        seek = (double)((1 + sqrt(d))/2);
                        printf("seek - %6.2f\n",seek);
                        if(s==0){
                            seekmin = seek;
                            s++;
                        }
                        printf("seekmin - %6.2f\n",seekmin);
                        if(seek < seekmin){
                            seekmin = seek;
                            l = iterate;
                            printf("l - %ld\n",l);
                        }
                        
                    }
                    temp = temp->next;

                }
                
                if(l==0){
                    printf("no seek was minimum\n");
                }
                else{
                    printf("seek - %6.2f\n",seekmin);
                    
                    temp = root;
                    while(temp!=NULL){
                        j++;
                        if(j==l){
                            q = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                    
                    printf("q->index - %ld q->cylindernum - %ld q->numsectors - %ld q->latency - %6.2f q->completion - %6.2f q->arrival - %6.2f\n",q->index,q->cylindernum,q->numsectors,q->latency,q->completion,q->arrival);
                    completion = (double)(seekmin + q->latency + (q->numsectors * transfer));
                    tcompletion = t + completion;
                    printf("completion - %6.2f tcompletion - %6.2f\n",completion,tcompletion);
                    temp = root;
                    while(temp!=NULL){
                        if(temp->next->index == q->index){
                            break;
                        }
                        temp = temp->next;
                    }
                    
                    temp->next = q->next;
                    free(q);

                }
                
                
                
            }
            else{
                tcompletion = INFINITY;
            }
        }
    }
    
    temp = root;
    while(temp!=NULL){
        printf("temp->index - %ld temp->cylindernum - %ld temp->numsectors - %ld temp->latency - %6.2f temp->arrival - %6.2f tcompletion - %6.2f\n",temp->index,temp->cylindernum,temp->numsectors,temp->latency,temp->arrival,temp->completion);
        temp = temp->next;
    }
    
    return 0;
}
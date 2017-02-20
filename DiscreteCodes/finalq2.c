

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM           50
#define START         0.0              /* initial time                   */
#define STOP      100.0              /* terminal (close the door) time */
#define INFINITY   (1000000000.0 * STOP)      /* must be much larger than STOP  */

struct machinenode{
    long machinenum;
    double failuretime;
    double servicetime;
    double operationtime;
    struct machinenode* next;
}*headmachine;

struct techniciannode{
    long techniciannum;
    long machinenum;
    double workinghour;
    double servicetime;
    struct techniciannode* next;
}*root;

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

void deletemachine(long position){
    struct machinenode* temp1, *temp2;
    long size=0,i;
    temp1 = headmachine;
    while(temp1!=NULL){
        temp1 = temp1->next;
        size++;
    }
    
    if(position==1){
        temp2 = headmachine;
        headmachine = temp2->next;
        temp2 = NULL;
    }
    else if(position==size){
        temp1 = headmachine;
        for(i=0;i<size-2;i++){
            temp1 = temp1->next;
        }
        temp1->next = NULL;
    }
    else{
        temp1 = headmachine;
        for(i=0;i<position-2;i++){
            temp1 = temp1->next;
        }
        temp2 = temp1->next;
        temp1->next = temp2->next;
        temp2->next = NULL;
    }
    
}

void appendtechnician(struct techniciannode* temp){
    
    int true = 1;
    if(root->next == NULL){
        root->next = temp;
       
    }
    
    else
    {
        
        struct techniciannode *current = root;
        while(true) {
            if(current->next == NULL)
            {
                current->next = temp;
              
                break;
            }
            current = current->next;
        };
    }
}


void appendmachine(struct machinenode* temp){
    
    int true = 1;
    if(headmachine->next == NULL){
        headmachine->next = temp;
       
    }
    
    else
    {
        
        struct machinenode *current = headmachine;
        while(true) {
            if(current->next == NULL)
            {
                current->next = temp;
               
                break;
            }
            current = current->next;
        };
    }
}




int main(void){
    long index = 0,i=0,machinenumtemp,numbers=0,count=3990;
    int l = 0;
    double x,y,minfailure,minservice=5000.0,t,servicetime,failuretime,operationtime;
    
    struct machinenode* temp;
    struct machinenode* p;
    struct machinenode* temp1;
    struct techniciannode* temp2;
    struct techniciannode* temp3;
    struct techniciannode* temp4;
    struct techniciannode* q;
    struct machinenode* temp5;
    
    while(index < 300){
        index++;
        SelectStream(1);
        x = Lognormal(5.4, 0.75);
        
        temp = malloc(sizeof(struct machinenode));
        temp->machinenum = index;
        temp->failuretime = x;
        temp->operationtime = x;
        temp->servicetime = 0.0;
        temp->next = NULL;
        
        
        if(headmachine == NULL){
            headmachine = temp;
        }
        else{
            appendmachine(temp);
        }
        
        
    }
    
  
    
    p = headmachine;
    while (p!=NULL) {
        if(l==0){
            minfailure = p->failuretime;
            l++;
        }
        if(p->failuretime < minfailure){
            minfailure = p->failuretime;
            temp1 = p;
        }
        p = p->next;
    }
    
   
    
    while((minfailure < 4160)){
       
        t = Min(minfailure, minservice);
        
        if(t==minfailure){
            numbers++;
            
           SelectStream(2);
           y = Erlang(6, 2.5);
            temp1->servicetime = y;
            servicetime = minfailure + y;
            
            
                if(root==NULL){
                   
                    temp2 = malloc(sizeof(struct techniciannode));
                    temp2->techniciannum = ++i;
                    temp2->machinenum = temp1->machinenum;
                    temp2->servicetime = servicetime;
                    temp2->workinghour = y;
                    temp2->next = NULL;
                    root = temp2;
                    
                }
                else{
                 temp3 = NULL;
                 q = root;
                 while(q!=NULL){
                      if((q->servicetime==INFINITY)&&(q->workinghour<3840.0)){
                      temp3 = q;
                      break;
                }
                q = q->next;
             }
            
            if(temp3==NULL){
                temp2 = malloc(sizeof(struct techniciannode));
                temp2->techniciannum = ++i;
                temp2->machinenum = temp1->machinenum;
                temp2->servicetime = servicetime;
                temp2->workinghour = y;
                temp2->next = NULL;
                
                appendtechnician(temp2);
                
            }
            else{
                temp3->servicetime = servicetime;
                temp3->workinghour += y;
                temp3->machinenum = temp1->machinenum;
                
            }
          }
            
            temp1->failuretime = INFINITY;
            l = 0;
            p = headmachine;
            while (p!=NULL) {
                if(p->operationtime > 4160){
                    p->operationtime = INFINITY;
                }
                if((l==0)&&(p->operationtime!=INFINITY)){
                    minfailure = p->failuretime;
                    temp1 = p;
                    l++;
                }
                if((p->failuretime < minfailure)&&(p->operationtime!=INFINITY)){
                    minfailure = p->failuretime;
                    temp1 = p;
                }
                p = p->next;
            }
            
            

            
            count--;
            
            if(numbers==1){
            q = root;
            temp4 = NULL;
            l = 0;
            while (q!=NULL) {
                if(q->workinghour > 3840){
                    q->workinghour = INFINITY;
                }
                if((l==0)&&(q->workinghour!=INFINITY)){
                    minservice = q->servicetime;
                    temp4 = q;
                    l++;
                }
                if((q->servicetime < minservice)&&(q->workinghour!=INFINITY)){
                    minservice = q->servicetime;
                    temp4 = q;
                }
                q = q->next;
            }
            
          
        }
        }
        else{
            numbers--;
            
            temp4->servicetime = INFINITY;
            machinenumtemp = temp4->machinenum;
            temp5 = NULL;
            p = headmachine;
            while(p!=NULL){
                if(p->machinenum == machinenumtemp){
                    temp5 = p;
                    break;
                }
                p = p->next;
            }
            
            
            
            if(temp5->operationtime > 4160.0){
                temp5->operationtime = INFINITY;
                
            }
            else{
           SelectStream(1);
            x = Lognormal(5.4, 0.75);
            failuretime = minservice + x;
                
                    temp5->failuretime = failuretime;
                
                    temp5->operationtime += x;
                    
                }
            
            
            
            if(temp4->workinghour > 3840){
                temp4->workinghour = INFINITY;
            }
            
            q = root;
            temp4 = NULL;
            l = 0;
            while (q!=NULL) {
                if(q->workinghour > 3840){
                    q->workinghour = INFINITY;
                }
                if((l==0)&&(q->workinghour!=INFINITY)){
                    minservice = q->servicetime;
                    temp4 = q;
                    l++;
                }
                if((q->servicetime < minservice)&&(q->workinghour!=INFINITY)){
                    minservice = q->servicetime;
                    temp4 = q;
                }
                q = q->next;
            }
         
        }
        
    }
    
    q = root;
    while(q!=NULL){
        if(q->workinghour == INFINITY){
            q = q->next;
        }
        else{
            printf("q->technicianum - %ld q->machinenum - %ld q->servicetime - %6.2f q->workinghours - %6.2f\n",q->techniciannum,q->machinenum,q->servicetime,q->workinghour);
            q = q->next;

        }
            }
    
    p = headmachine;
    while (p!=NULL) {
        if(p->operationtime == INFINITY){
            p = p->next;
        }
        else{
            printf("p->machinenum - %ld p->failuretime - %6.2f p->operationtime - %6.2f p->servicetime - %6.2f\n",p->machinenum,p->failuretime,p->operationtime,p->servicetime);
            p = p->next;
        }
        
    }
    
    return 0;
}


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM 100

struct node{
    long index;
    long val;
    long freq;
    long count;
    long dieroll;
    struct node* next;
    struct node* prev;
};

typedef struct node* pointer;
int arr[6] = {1,2,3,4,4,4};

  int main(void)
{
    pointer head;
    pointer p;
    pointer q;
    pointer r;
    long index = 1,n,runs=0,j,count=0,win=0,k=0,temp=0,i,die=0,sumdie = 0;
    
    head = malloc(sizeof(struct node));
    head->val = 3;
    head->index = index;
    head->freq = 0;
    head->dieroll = 0;
    head->count = 0;
    head->next = NULL;
    head->prev = NULL;
    
    p = head;
    //q = p->next;
    //q = p->next;
    printf("Enter value of n: ");
    scanf("%ld",&n);
    index++;
    
    while(index <= n){
        
        q = malloc(sizeof(struct node));
        q->index = index;
        q->val = 3;
        q->freq = 0;
        q->count = 0;
        q->dieroll = 0;
        q->next = NULL;
        q->prev = NULL;
        //q->prev = p;
        //printf("index - %ld val - %d\n",p->index,p->val);
        p->next = q;
        q->prev = p;
        p = p->next;
        index++;
    }
    q->next = head;
    head->prev = q;

    //head->prev = p;
    
    p = head;
    index = 1;
    
  /*  while(index <= n){
        index++;
        printf("\nindex - %ld val - %ld\n",p->index,p->val);
                    p = p->prev;

        
    } */
    
    p = head;
    
    while(runs < MAXIMUM){
        runs++;
        win = 0;
        die = 0;
        //sumdie = 0;
        while(!win){
           // printf("\n\nStarts p->index - %ld\n",p->index);
            r = p->next;
            count = 0;
            while((r->val == 0)&&(p->val!=0)){
                r = r->next;
                count++;
            }
           // printf(" count - %ld",count);
            if(count == n - 1){
                win++;
              //  printf("p->index %ld Winss !!\n",p->index);
                p->freq++;
                break;
            }
            
          //  printf("p->val - %ld",p->val);
            p->count++;
            if(p->val >= 3){
               // printf("inside >= 3 loop");
                k=0;
                while(k<3){
                    k++;
                    j=Equilikely(1, 6);
                  //  printf("j - %ld",j);
                   // p->count++;
                    p->dieroll++;
                    die++;
                    if(j==1){
                        p->prev->val++;
                      //  printf("p->prev->val - %ld",p->prev->val);
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                    else if(j==2){
                        p->val--;
                       // printf("p->val - %ld",p->val);
                    }
                    else if(j==3){
                        p->next->val++;
                      //  printf("p->next->val - %ld",p->next->val);
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                }
            }
            else{
                temp = p->val;
                k=0;
                while(k < temp){
                    k++;
                    j=Equilikely(1, 6);
                  //  printf("j - %ld",j);
                   // p->count++;
                    p->dieroll++;
                    die++;
                    if(j==1){
                        p->prev->val++;
                      //  printf("p->prev->val - %ld",p->prev->val);
                        p->val--;
                       // printf("p->val - %ld",p->val);
                    }
                    else if(j==2){
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                    else if(j==3){
                        p->next->val++;
                       // printf("p->next->val - %ld",p->next->val);
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }

                }
            }
            p = p->next;
           // printf("\n");
    }
        /*for(i=0;i<n;i++){
            printf("p->index - %ld p->dieroll - %ld p->count - %ld mean = %6.2f\n",p->index,p->dieroll,p->count,(double)p->dieroll/p->count);
            sumdie += p->dieroll;
            p = p->next;
        } */
        //printf("sumdie - %ld die - %ld\n",sumdie,die);
        p = head;
        p = p->next->next;
        printf("%ld\n",p->dieroll);
        for(i=0;i<n;i++){
            p->val = 3;
            p->dieroll = 0;
            p->count = 0;
            p = p->next;
            
        }
  }
    for(i=0;i<n;i++){
        printf("p->index %ld p->freq - %ld\n",p->index,p->freq);
        p=p->next;
    }

    
  return (0);
}

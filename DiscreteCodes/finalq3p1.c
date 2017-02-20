

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include "rvgs.h"

#define MAXIMUM 10000

struct node{
    long index;
    long val;
    long freq;
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
    long index = 1,n,runs=0,j,count=0,win=0,k=0,temp=0,i,die=0;
    
    head = malloc(sizeof(struct node));
    head->val = 3;
    head->index = index;
    head->freq = 0;
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
    
   /* while(index <= n){
        index++;
        printf("\nindex - %ld val - %ld\n",p->index,p->val);
                    p = p->prev;

        
    } */
    
    p = head;
    
    while(runs < MAXIMUM){
        runs++;
        win = 0;
        die = 0;
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
               // printf("p->index %ld Winss !!\n",p->index);
                p->freq++;
                break;
            }
            
           // printf("p->val - %ld",p->val);
            
            if(p->val >= 3){
               // printf("inside >= 3 loop");
                k=0;
                while(k<3){
                    k++;
                    j=Equilikely(1, 6);
                    die++;
                  //  printf("j - %ld die - %ld",j,die);
                    if(j==1){
                        p->prev->val++;
                     //   printf("p->prev->val - %ld",p->prev->val);
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                    else if(j==2){
                        p->val--;
                      //  printf("p->val - %ld",p->val);
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
                    die++;
                  //  printf("j - %ld die - %ld",j,die);
                    if(j==1){
                        p->prev->val++;
                      //  printf("p->prev->val - %ld",p->prev->val);
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                    else if(j==2){
                        p->val--;
                      //  printf("p->val - %ld",p->val);
                    }
                    else if(j==3){
                        p->next->val++;
                    //    printf("p->next->val - %ld",p->next->val);
                        p->val--;
                    //    printf("p->val - %ld",p->val);
                    }

                }
            }
            p = p->next;
          //  printf("\n");
    }
        for(i=0;i<n;i++){
            p->val = 3;
            p = p->next;
        }
        printf("%ld\n",die);
  }
    for(i=0;i<n;i++){
        printf("p->index %ld p->freq - %ld\n",p->index,p->freq);
        p=p->next;
    }

    
  return (0);
}

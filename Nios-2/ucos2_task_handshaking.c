#include <stdio.h>
#include "includes.h"
#include <string.h>

#define DEBUG 1

//semaphores for handshaking
OS_EVENT *aSemaphore;
OS_EVENT *bSemaphore;


/* Definition of Task Stacks */
/* Stack grows from HIGH to LOW memory */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];
OS_STK stat_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define TASK1_PRIORITY 6  // highest priority
#define TASK2_PRIORITY 7
#define TASK_STAT_PRIORITY 12  // lowest priority 

void printStackSize(INT8U prio)
{
    INT8U err;           //error flag for statistics task
    OS_STK_DATA stk_data;
    
    err=OSTaskStkChk(prio, &stk_data);
    if(err==OS_NO_ERR) 
    {
        if(DEBUG==1)
        {
           printf("Task Priority %d - Used: %d; Free: %d\n", prio, stk_data.OSFree, stk_data.OSUsed);
        }
    }
    else
    {
        if (DEBUG==1)
        {
           printf("Stack Check Error!\n");   
        } 
    }
}

/* Prints a message and sleeps for given time interval */
void task1(void* pdata)
{ 
    INT8U err_task1;          //error flag for task 1
  
    while (1)
    { 
        OSSemSet(bSemaphore, 0, &err_task1);     //set key to 0
        OSSemPend(aSemaphore, 0, &err_task1); // Trying to access the key
        if(err_task1==OS_ERR_NONE)
        {
            printf("T0-S0\n");
            OSSemPost(aSemaphore);              // Releasing the key
                   
            OSSemPend(bSemaphore, 0, &err_task1);    // Trying to access the key
            if (err_task1==OS_ERR_NONE) 
            {
                printf("T0-S1\n");
                printf("\n");
            } 
        }                                                                                         
        OSSemPost(bSemaphore); // Releasing the key
    }
}

/* Prints a message and sleeps for given time interval */
void task2(void* pdata)
{
    INT8U err_task2;          //error flag for task 2

    while (1)
    {  
        OSSemPend(aSemaphore, 0, &err_task2); // Trying to access the key
        if(err_task2==OS_ERR_NONE)
        {
            printf("T1-S0\n");
            printf("T1-S1\n");
                                            
        }
        OSSemPost(aSemaphore); // Releasing the key        
        OSSemPost(bSemaphore); // Releasing the key  
    }
}

/* Printing Statistics */
void statisticTask(void* pdata)
{
    INT8U err_task3;
        
//**********************Critical section*******************  
        
    while(1)
    {
        OSSemPend(aSemaphore, 0, &err_task3); // Trying to access the key
        if(err_task3==OS_ERR_NONE)
        {
            //print stack data for all 3 tasks
            printStackSize(TASK1_PRIORITY);
            printStackSize(TASK2_PRIORITY);
            printStackSize(TASK_STAT_PRIORITY);
        }
        OSSemPost(aSemaphore); // Releasing the key
    }
//**********************Non-critical section*******************  
}

/* The main function creates two task and starts multi-tasking */
int main(void)
{
    INT8U err;

    aSemaphore=OSSemCreate(1); // binary semaphore (1 key)
    bSemaphore=OSSemCreate(1); // binary semaphore (1 key)

    //creates task 1
    OSTaskCreateExt
    (task1,                        // Pointer to task code
     NULL,                         // Pointer to argument that is
                                   // passed to task
     &task1_stk[TASK_STACKSIZE-1], // Pointer to top of task stack
     TASK1_PRIORITY,               // Desired Task priority
     TASK1_PRIORITY,               // Task ID
     &task1_stk[0],                // Pointer to bottom of task stack
     TASK_STACKSIZE,               // Stacksize
     NULL,                         // Pointer to user supplied memory
                                   // (not needed here)
     OS_TASK_OPT_STK_CHK |         // Stack Checking enabled 
     OS_TASK_OPT_STK_CLR           // Stack Cleared                                 
    );
               
  //creates task 2             
    OSTaskCreateExt
    (task2,                        // Pointer to task code
     NULL,                         // Pointer to argument that is
                                   // passed to task
     &task2_stk[TASK_STACKSIZE-1], // Pointer to top of task stack
     TASK2_PRIORITY,               // Desired Task priority
     TASK2_PRIORITY,               // Task ID
     &task2_stk[0],                // Pointer to bottom of task stack
     TASK_STACKSIZE,               // Stacksize
     NULL,                         // Pointer to user supplied memory
                                   // (not needed here)
     OS_TASK_OPT_STK_CHK |         // Stack Checking enabled 
     OS_TASK_OPT_STK_CLR           // Stack Cleared                       
    );  
    
    //create statistics task
    if (DEBUG == 1)
    {
        OSTaskCreateExt
        (statisticTask,                // Pointer to task code
         NULL,                         // Pointer to argument that is
                                       // passed to task
         &stat_stk[TASK_STACKSIZE-1],  // Pointer to top of task stack
         TASK_STAT_PRIORITY,           // Desired Task priority
         TASK_STAT_PRIORITY,           // Task ID
         &stat_stk[0],                 // Pointer to bottom of task stack
         TASK_STACKSIZE,               // Stacksize
         NULL,                         // Pointer to user supplied memory
                                     // (not needed here)
         OS_TASK_OPT_STK_CHK |         // Stack Checking enabled 
         OS_TASK_OPT_STK_CLR           // Stack Cleared                              
        );
    }  
    
  OSStart();             //start OS
  return 0;
}
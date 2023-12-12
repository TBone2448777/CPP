//
// Created by Chris Branton on 10/23/2020.
// Updated (down-dated?) to C language 11/05/2023. CWB
//
#include <stdio.h>
#include <stdlib.h>

#include "pcb_queue.h"
#include "process.h"

const int NUM_PROC=20;
const int TIME_SLICE=20; // execution time in milliseconds

// Creates a set of dummy processes.
// TODO: update the execution time to a random number between 10 and 5000.
void makeProcesses(ProcessControlBlock* procQ, int numProcesses)
{
    char printString[32]="Process ";
    char intString[16];
    time_t nowTime;
    srand(time(NULL));
    long execTime;

    for (int i = 0; i < numProcesses; i++)
    {
        execTime = rand()%4990+10;
        time(&nowTime);
        snprintf(intString, 16, "%d", i+1);
        strcat(printString, intString);
        ProcessControlBlock* pcbPtr = (ProcessControlBlock*) malloc(sizeof( ProcessControlBlock));
        initProcess(pcbPtr, i+1, 1, NULL, nowTime, execTime, printString);
        enqueue (pcbPtr);
        printf ("Process %d created\n", i+1);
    }
}

// Retrieves the process at the front of the queue and removes it
ProcessControlBlock* getNextProcess(ProcessControlBlock* procQ)
{
    ProcessControlBlock* pcb = NULL;
    if (!isEmpty(procQ))
    {
        pcb = dequeue(procQ);
    }
    return pcb;
}


// Uses a single method to start and run the process scheduler until it completes
void startScheduler(ProcessControlBlock* procQ)
{
    time_t time = 0;
    ProcessControlBlock* pcb;
    pcb = getNextProcess(procQ);
    while (pcb != NULL)
    { 
        int stillRunning = runProcess(pcb, TIME_SLICE);
        if (stillRunning)
        {
            enqueue(pcb);
        }
        else
        {
            printf("Process %d complete\n", pcb->processId);
            time += printProcessInfo(pcb);
        }
        pcb = getNextProcess(procQ);
    }
    printf("\n\nTotal execution time: %ld\n", time);
}

/*********************************
*
** Main program 
 * 
**********************************/
ProcessControlBlock* inp_arr [SIZE];

int main(int argc, char* argv[])
{
    /* initialize random seed: */
    srand(time(NULL));
    printf ("Starting scheduler\n");
    makeProcesses(*inp_arr, NUM_PROC);
    startScheduler(*inp_arr);
    printf("All processes complete\n");
}
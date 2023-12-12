#include <stdio.h>
#include <stdbool.h>

#include "pcb.h"

const int TIME_SLICE = 20;
ProcessControlBlock procQ[100];

// subtract timeslice and set remaining time
void runProcess(ProcessControlBlock* proc, int time){}
// update process state
void suspendProcess(ProcessControlBlock* proc){
    if (timeElapsed(proc)){
        proc->state = TERMINATED;
    } else{
        proc->state = WAITING;
    }
    if(proc->state != TERMINATED){
        enqueue(procQ, proc);
    }
}
ProcessControlBlock* selectProcess(ProcessControlBlock* procQ){return dequeue(procQ);}
void loadProcess(ProcessControlBlock* proc){}

ProcessControlBlock* currentProcess;

void schedule(){
    while(true){
        runProcess(currentProcess, TIME_SLICE);
        suspendProcess(currentProcess);
        currentProcess = selectProcess(procQ);
        loadProcess(currentProcess);
    }
}
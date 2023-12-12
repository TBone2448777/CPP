#include <stdio.h>
#include <time.h>
#include "pcb.h"

void setCommand(ProcessControlBlock* pcb, char* c){
    strncpy(pcb->comm, c, 255);
}

void InitializeProcessControlBlock(ProcessControlBlock* pcb){
    pcb->state = NEW;    // Current state of the process
    pcb->processId = 0;
    pcb->counter = 0;   // reference count (sort of)
    pcb->priority = 0;
    pcb->parent = NULL;
    pcb->startTime = time(NULL);
    pcb->clockTime = 0;
    pcb->cpuTime = 0;
    pcb->processor = 1;
    pcb->exitCode = 0;
    setCommand(pcb, "");
}

void setParent(ProcessControlBlock* pcb, ProcessControlBlock* p){
    pcb->parent = p;
}

ProcessControlBlock* getParent(ProcessControlBlock* pcb){
    return pcb->parent;
}

int main(int argc, char ** argv){
    char states[][11] = {"NEW", "READY", "RUNNING", "WAITING", "TERMINATED"};
    ProcessControlBlock pcb;
    InitializeProcessControlBlock(&pcb);
    printf("Process %d is initialized with state %s.\n", pcb.processId, states[pcb.state]);
    printf("It is %lu in the stack, with a priority of %lu.\n", pcb.counter, pcb.priority);
    printf("It began at time %lu.\n", pcb.startTime);
    return 0;
}
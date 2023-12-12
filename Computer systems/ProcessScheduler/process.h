#include <stdio.h>
#include <time.h>
#include "pcb.h"

// initialize process
void initProcess(ProcessControlBlock* pcb, long procId, long priority, 
        ProcessControlBlock* parent, time_t startTime, long execTime, char* cmd)
{
        pcb->processId=procId;
        pcb->priority=1;
        pcb->parent=NULL;
        pcb->startTime=time(&(pcb->startTime)); 
        pcb->executionTime = execTime;
        pcb->comm[256];
}

// TODO: update output.
time_t printProcessInfo(const ProcessControlBlock* pcb) 
{
    printf("Time after execution: %ld\n", pcb->cpuTime);
    return pcb->cpuTime;
};

// TODO: change this to subtract the timeSlice and update the executionTime
// Return the updated executionTime. NOTE: this should not be negative
int runProcess(ProcessControlBlock* pcb, int timeSlice)
{
    if (pcb->executionTime - timeSlice < 0){
        pcb->cpuTime = pcb->cpuTime + pcb->executionTime;
        pcb->executionTime = 0;
    } else{
        pcb->cpuTime = pcb->cpuTime + timeSlice;
        pcb->executionTime = pcb->executionTime - timeSlice;
    }
    return pcb->executionTime;
}

// getters and setters
int getPid(const ProcessControlBlock* pcb) {return pcb->processId;}
void setPid(ProcessControlBlock* pcb, int pid) {(*pcb).processId = pid;}
void setCommandLine(ProcessControlBlock* pcb, char* cmd) { strncpy(pcb->comm, cmd, 256); }
char* getCommandLine(ProcessControlBlock* pcb) { return pcb->comm; }

void suspendProcess(ProcessControlBlock* pcb) {};
long getExecutionTime(const ProcessControlBlock pcb) { return 0; };



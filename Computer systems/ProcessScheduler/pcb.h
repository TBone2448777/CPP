/**
// Created by branton on 10/23/2020.
// Loosely based on the Linux Task_struct
 References:
   process-control-block-in-linux.pdf
*/

//#include "other.h"
#include <string.h>
#include <time.h>

#ifndef PCB_H
#define PCB_H

// Enumerated type
enum ProcessState {
    NEW, READY, RUNNING, WAITING, TERMINATED
};

typedef struct pcBlock {
        int executionTime; // Variable added for scheduling assignment
        enum ProcessState state;    // Current state of the process
        int processId;
        long counter;   // reference count (sort of)
        long priority;
        struct pcBlock* parent;
        time_t startTime, clockTime, cpuTime;
        int processor;
        int exitCode;
        // Placeholders for information the OS would need;
        // Defined in other structures -- we will not use them.
        unsigned long long pc;
        char comm[256];
        void* registerFile;
        void* stack;
        unsigned int flags;

        // Normally keep a pointer to list of children and siblings
        void* children;
        void* siblings;
        void* fileSystem;
        void* files;

    } ProcessControlBlock;


#endif

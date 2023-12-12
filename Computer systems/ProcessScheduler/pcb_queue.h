// Circular queue implementation in C

#include <stdio.h>
#include <stdbool.h>
#include "pcb.h"

# define SIZE 100000

// ADT definition
// TODO: check conditions for empty and full queue

bool isEmpty();
bool isFull();
void enqueue(ProcessControlBlock* insert_item);
ProcessControlBlock* dequeue();
void show( void (* printFn)(ProcessControlBlock* item));


//Implementation
extern ProcessControlBlock* inp_arr[SIZE];
int Rear = - 1;
int Front = - 1;

bool isEmpty() 
{
    return Front == - 1 || Front > Rear;
}

bool isFull()
{
    return Front >= SIZE;
}
 
void enqueue(ProcessControlBlock* insert_item)
{
    if (Rear == SIZE - 1)
        printf("Overflow \n");
        // Rear = Front;
    else
    {
        if (Front == - 1)
      
        Front = 0;
        Rear = Rear + 1;
        inp_arr[Rear] = insert_item;
    }
} 
 
ProcessControlBlock* dequeue()
{
    if (Front == - 1 || Front > Rear)
    {
        printf("Underflow \n");
        return NULL;  // Question: is this line needed?
    }
    else
    {
        ProcessControlBlock* returnValue = inp_arr[Front];
        Front = Front + 1;
        return returnValue;
    }
} 
 
void show( void (* printFn)(ProcessControlBlock* item))
{
    
    if (Front == - 1)
        printf("Empty Queue \n");
    else
    {
        printf("Queue: \n");
        for (int i = Front; i <= Rear; i++)
            printFn(inp_arr[i]);
        printf("\n");
    }
} 
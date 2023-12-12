#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <bits-stdc++.h>
#include <chrono>
using namespace std;

class Node{
    public:
        // Nodes hold three pieces of info, their data, next node, and previous node
        int data;
        struct Node* next;
        struct Node* prev;

        // Constructor
        Node(int nData){
            data = nData;
            next = NULL;
            prev = NULL;
        }
};

class LList{
    public:
        // List only has two pieces of info, head and tail
        struct Node* head = NULL;
        struct Node* tail = NULL;
        
        // Push to front of list
        void push(int val){
            Node* newnode = new Node(val);
            if (!head){
                head = newnode;
                tail = newnode;
            } else{
                newnode->next = head;
                head->prev = newnode;
                head = newnode;
            }
        }

        // Append to end of list
        void append(int val){
            Node* newnode = new Node(val);
            if (!tail){
                head = newnode;
                tail = newnode;
            } else{
                newnode->prev = tail;
                tail->next = newnode;
                tail = newnode;
            }
        }

        // Remove first item of list
        void shift(){
            if (head){
                Node* temp = head;
                head = head->next;
                head->prev = NULL;
                delete temp;
            }
        }

        // Remove last item of list
        void pop(){
            if (tail){
                Node* temp = tail;
                tail = tail->prev;
                tail->next = NULL;
                delete temp;
            }
        }

        // Returns the length of the linked list
        int length(){
            int counter = 0;
            Node* tracker = head;
            while (tracker){
                counter++;
                tracker = tracker->next;
            }
            return counter;
        }

        // Merge Sort linked list
        // Can't have default parameter be variable, so it begins as 0 and if 0 is there it pulls head and runs that
        void mergeSort(Node** headRef = 0){
            if (headRef == 0){
                mergeSort(&head);
            } else{
                Node* head = *headRef;
                Node* left;
                Node* right;
                if ((head == NULL) || (head->next == NULL)) {
                    return;
                }
                // Gets front, middle, and back. Splits them so that the left most and right most can be fed and used recursively
                frontBackSplit(head, &left, &right);
                // Sends left side of the list to be run through this again
                mergeSort(&left);
                // Sends right side of the list to be run through this again
                mergeSort(&right);
                // Combines the two sides
                *headRef = sortedMerge(left, right);
            } 
        }

        // In charge of combining two lists
        Node* sortedMerge(Node* left, Node* right){
            Node* result = NULL;
            // If only one node passed then just return the one node
            if (left == NULL)
                return (right);
            else if (right == NULL)
                return (left);
            // If the left side is greater than right, set left's next to the right and repass what is left of the lists
            if (left->data <= right->data) {
                result = left;
                result->next = sortedMerge(left->next, right);
            }
            // If the right side is greater than left, set right's next to the left and repass what is right of the lists
            else {
                result = right;
                result->next = sortedMerge(left, right->next);
            }
            return (result);
        }
        
        // Splits a linked list in the middle
        void frontBackSplit(Node* source, Node** frontRef, Node** backRef){
            // Uses slow and fast node. Fast moves twice as quickly as slow, so when it gets to the end of the list then slow should be in the middle
            Node* fast;
            Node* slow;
            slow = source;
            fast = source->next;
            while (fast != NULL) {
                fast = fast->next;
                if (fast != NULL) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            // Splits the list in half and sets pointers to the beginning node of the now two lists
            *frontRef = source;
            *backRef = slow->next;
            slow->next = NULL;
        }

        // Sorts list low to high via bubble sort. Instead of worrying about remapping head and tail, it just adds a 0 to each side and sorts the middle numbers then removes the 0s at the end.
        void bubbleSort(){
            int len = length();
            Node* focus; Node* temp;
            push(0);
            append(0);
            for (size_t i = 0; i < len; i++){
                focus = head;
                while (focus->next){
                    if (focus->data > focus->next->data){
                        if (focus != head && focus->next != tail){
                            temp = focus->next;
                            focus->prev->next = temp;
                            temp->prev = focus->prev;
                            focus->next = temp->next;
                            focus->next->prev = focus;
                            temp->next = focus;
                            focus->prev = temp;
                        }
                    }
                    focus = focus->next;
                }
            }
            shift();
            pop();
        }

        // Linear search for the linked list
        int lSearch(int key){
            Node* iterate = head;
            int loc = 0;
            while (iterate){
                if (iterate->data == key){
                    return loc;
                }
                iterate = iterate->next;
                loc++;
            }
            return -1;
        }

        // Gets pointer for whatever index is input
        Node* getPointer(int loc){
            Node* iterate = head;
            for (size_t i = 0; i < loc; i++){
                iterate = iterate->next;
            }
            return iterate;
        }

        // Gets value for whatever index is input
        int index(int loc){
            return getPointer(loc)->data;
        }

        // Adds x random integers in the range of 0-y. Can choose whether to push or append by providing a char other than 'a'. Defaults to append.
        void fillRandom(int x, int y = 1000, char type = 'a'){
            srand(time(NULL));
            if (type == 'a'){
                for(size_t i = 0; i < x; i++){
                    append(rand()%y);
                }
            } else{
                for(size_t i = 0; i < x; i++){
                    push(rand()%y);
                }
            }
        }

        // Add quantity len numbers to array pointed to by arrPtr. If ord is 'a' or 'd' make the order ascend or descend
        void fillRandomOrder(char ord, int x, int y = 1000, char type = 'a'){
            // Seed Random
            srand(time(NULL));
            // Track is used to ensure increasing or decreasing
            int track;
            if (ord == 'a'){
                // If ascend start track low and add up to 5 at a time to it
                track = 0;
                for(size_t i = 0; i < x; i++){
                    track += rand()%5;
                    append(track);
                }
            } else if (ord == 'd'){
                // If descend start track high and remove up to 5 at a time from it
                track = 10000;
                for(size_t i = 0; i < x; i++){
                    track -= rand()%5;
                    append(track);
                }
            }
        }

        // Empty the entirety of the list.
        void clear(){
            Node* cleaner = head;
            while (cleaner){
                Node* temp = cleaner;
                cleaner = cleaner->next;
                delete temp;
            }
            head = NULL;
            tail = NULL;
        }

        // Print all values in list separated by a comma
        void print(){
            Node* printer = head;
            int k = 0;
            while (printer){
                printf("%d, ", printer->data);
                printer = printer->next;
                if (k > 10){
                    return;
                }
            }
            printf("\n");
        }
};

int main(){
    LList llist;
    llist.fillRandom(43120);
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    llist.mergeSort();
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9; 
    printf("%f", time_taken);
}
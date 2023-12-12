#include <cstdio>
#include <stdlib.h>
#include <time.h>

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
    llist.fillRandom(10, 11);
    // llist.append(1);
    // llist.append(3);
    // llist.append(2);
    // llist.append(3);
    llist.print();
    printf("\n\n");
    llist.bubbleSort();
    llist.print();
    printf("\nObject can be located at index %d", llist.lSearch(10));
    printf("\n%d", llist.index(2));
}
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

// Defines node class. Opted not to track parent just because it wasn't really needed for this implementation.
class Node{
    public:
        int val = NULL;
        Node* right = NULL;
        Node* left = NULL;
        Node(int nData){
            val = nData;
        }
};

// Defines heap class. In this instance it is a minheap
class Heap{
    public:
        Node* root = NULL;

        // This fills the tree with elements of an array in order. Is provided array pointer and array length
        void fillTree(int* arrPtr, int arrLen){
            // First sets the root to the first queue element
            root = new Node(arrPtr[0]);
            // Utilizes a queue function as a way to track where it is in adding nodes
            queue<Node*> nodeQueue;
            nodeQueue.push(root);
            // Runs for every element of the fed array
            for (size_t i = 1; i < arrLen; i++){
                // Grabs the node to focus on from the fron of the queue
                Node* node = nodeQueue.front();
                // Creates a new node with the next value from the array
                Node* newnode = new Node(arrPtr[i]);
                // If node does not have a left side set the left side equal to the new node
                if (!node->left){
                    node->left = newnode;
                // If node does have a left side set the right side to the new node
                } else{
                    node->right = newnode;
                    // If a left and right side exist, then the node should no longer be in the queue and it should pop so nothing is overwritten
                    nodeQueue.pop();
                }
                // Add the new node to the queue to maintain in order tracking
                nodeQueue.push(newnode);
            }
            // Sort the heap now that everything is added
            sortMin(root);
        }

        // Will recursively end up calling a sort of every single element
        void sortMin(Node* node){
            if (!node){
                return;
            }
            sortMin(node->right);
            sortMin(node->left);
            sorterMin(node);
        }

        // Actually does the sorting
        void sorterMin(Node* node){
            // First it gets a pointer to the smallest of three nodes, node, left, and right
            Node* smallest = node;
            if (node->left && node->left->val < smallest->val){
                smallest = node->left;
            }
            if (node->right && node->right->val < smallest->val){
                smallest = node->right;
            }
            if (smallest != node){
                // Swaps values between node and smallest node, unless smallest node is itself
                int holder = node->val;
                node->val = smallest->val;
                smallest->val = holder;
                // Resorts the smallest node determined by this
                sorterMin(smallest);
            }
        }

        // Will get the kth smallest element
        int kthSmallest(int count = 1){
            for (size_t i = 0; i < count-1; i++){
                popper(root);
            }
            return root->val;
        }

        // Actually removes each node
        void popper(Node* node){
            // If there is a left node do this. This is longer than the right node one because it accounts for left and right existing
            if (node->left){
                // Get the smallest value and swap things around
                Node* smallest = node->left;
                if (node->right && node->right->val < smallest->val){
                    smallest = node->right;
                }
                int holder = node->val;
                node->val = smallest->val;
                smallest->val = holder;
                // If smallest is not a leaf node call it again to continue moving the old root node down through everything
                if (smallest->right || smallest->left){
                    popper(smallest);
                // If smallest is a leaf node
                } else{
                    // Set the pointer to smallest equal to NULL
                    if (node->left == smallest){
                        node->left = NULL;
                    } else{
                        node->right = NULL;
                    }
                    // Delete smallest
                    delete(smallest);
                }
            // If there is a right node and no left node
            } else if (node->right){
                // Swap values
                int holder = node->val;
                node->val = node->right->val;
                node->right->val = holder;
                // If the right node isn't the leaf call again with leaf
                if (node->right->right || node->right->left){
                    popper(node->right);
                // Else set pointer to leaf node equal to node and delete the node
                } else{
                    node->right = NULL;
                    delete(node->right);
                }
            }
        }

        // By going through the left side figure out height of tree. Just used for my own troubleshooting
        void getHeight(){
            Node* node = root;
            int obj = 0;
            while (node->left){
                node = node->left;
                obj++;
            }
            printf("%d", obj);
        }
};

// Make a random list at arrPtr with len number of elements
int makeRandom(int *arrPtr, int len){
    srand(time(NULL));
    for(size_t i = 0; i < len; i++){
        arrPtr[i] = rand()%1000;
    }
    return 0;
}

int main(){
    // Make a random list of length x and fill it with random numbers
    int arr[] = {7, 4, 6, 3, 9, 1};
    int *arrPtr = arr;
    int arrLen = sizeof(arr)/sizeof(int);
    // makeRandom(arrPtr, arrLen);
    // Make a heap element and fill with the array
    Heap minheap;
    minheap.fillTree(arrPtr, arrLen);
    // Get the kth smallest value
    printf("%d", minheap.kthSmallest(1));
}
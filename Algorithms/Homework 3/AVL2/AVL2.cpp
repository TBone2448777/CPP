#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <bits-stdc++.h>
#include <chrono>
using namespace std;

// Define a node class
class Node{
    public:
        string* val = NULL;
        Node* parent = NULL;
        Node* left = NULL;
        Node* right = NULL;
        int height = 0;

        Node(string* data){
            val = data;
        }

        // Figure out the balance of a node. Basically used to tell if one side over one node taller than the other
        int get_balance(){
            int left_height = -1;
            if (left){
                left_height = left->height;
            }
            int right_height = -1;
            if (right){
                right_height = right->height;
            }
            return left_height - right_height;
        }

        // Updates height of the node
        void update_height(){
            int left_height = -1;
            if (left){
                left_height = left->height;
            }
            int right_height = -1;
            if (right){
                right_height = right->height;
            }
            height = std::max(left_height, right_height) + 1;
        }

        // Sets child of the node
        void set_child(bool which_child, Node* child){
            if (which_child){
                right = child;
            } else {
                left = child;
            }
            if (child){
                child->parent = this;
            }
            update_height();
        }

        // Swaps the old child of node with new child
        void replace_child(Node* currChild, Node* newChild){
            if (left == currChild){
                set_child(0, newChild);
            } else if (right == currChild){
                set_child(1, newChild);
            }
        }
};

// Defines AVLTree
class AVLTree{
    public:
        Node* root = NULL;

        // Swaps values around to match a left rotation
        void rotate_left(Node* node){
            Node* right_left_child = node->right->left;
            if (node->parent){
                node->parent->replace_child(node, node->right);
            } else{
                root = node->right;
                root->parent = NULL;
            }
            node->right->set_child(0, node);
            node->set_child(1, right_left_child);
        }

        // Swaps values around to match a right rotation
        void rotate_right(Node* node){
            Node* left_right_child = node->left->right;
            if (node->parent){
                node->parent->replace_child(node, node->left);
            } else {
                root = node->left;
                root->parent = NULL;
            }
            node->left->set_child(1, node);
            node->set_child(0, left_right_child);
        }

        // Called to rebalance tree when any structural changes occur
        void rebalance(Node* node){
            node->update_height();
            if (node->get_balance() == -2){
                if (node->right->get_balance() == 1){
                    rotate_right(node->right);
                }
                rotate_left(node);
            } else if (node->get_balance() == 2){
                if (node->left->get_balance() == -1){
                    rotate_left(node->left);
                }
                rotate_right(node);
            }
            if (node->parent){
                rebalance(node->parent);
            }
        }

        // Traverses through the BST and finds a place to put the new node
        void append(string val){
            Node* node = new Node(&val);
            if (!root){
                root = node;
            } else{
                Node* current_node = root;
                while (current_node){
                    if (node->val < current_node->val){
                        if (current_node->left){
                            current_node = current_node->left;
                        } else{
                            current_node->left = node;
                            node->parent = current_node;
                            current_node = NULL;
                        }
                    } else{
                        if (current_node->right){
                            current_node = current_node->right;
                        } else{
                            current_node->right = node;
                            node->parent = current_node;
                            current_node = NULL;
                        }
                    }
                }
                node = node->parent;
                while (node){
                    rebalance(node);
                    node = node->parent;
                }
            }
        }

        // Prints height of root node. Used for troubleshooting
        void printTopHeight(){
            printf("%d", root->height);
        }

        // Fills with a bunch of psuedo words. Just three random characters
        void fillRandom(int count){
            srand(time(NULL));
            string alphabet[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
            for (size_t i = 0; i < count; i++){
                append(alphabet[rand()%26]+alphabet[rand()%26]+alphabet[rand()%26]);
            }
        }
};

int main(){
    // Defines AVL tree
    AVLTree tree;
    // Begins to start clock
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    // Fills tree which sorts and balances as it does so
    tree.fillRandom(10000000);
    // Ends timer
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9; 
    // Prints time taken in milliseconds
    printf("%f milliseconds", time_taken * 1000);
}
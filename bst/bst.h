#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct node {
    int value;
    struct node *left, *right;
} Node;

Node * insert_node(Node *tree, int value);
Node * delete_node(Node *tree, int value);

bool search(Node *tree, int value);
int greater(Node *tree);
int smaller(Node *tree);
int height(Node *tree);
int sum(Node *tree);
int count_primes(Node *tree);
int successor(Node *tree, int value);
void path(Node *tree, int value);

// The order that is printed is used to create the same tree
// Ex: save the tree as a list in the file to recreate the tree later
void pre_order(Node *tree);
// It is used to print the values in ascending order
void in_order(Node *tree);
// It is used to create a tree with operations in a language compiler
void post_order(Node *tree);
// It is used to print the values in descending order
void reverse_order(Node *tree);

#endif

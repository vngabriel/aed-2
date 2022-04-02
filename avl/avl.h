#ifndef AVL_H
#define AVL_H

#include <stdbool.h>

typedef int abstract_data;

typedef struct node_avl {
    abstract_data data;
    struct node_avl *left, *right;
    int balance_factor;
} Node;

Node * insert_node(Node *tree, abstract_data data, bool *grew);
Node * delete_node(Node *tree, abstract_data data, bool *decreased);

Node * rotate(Node *tree);
Node * single_left_rotation(Node *tree);
Node * single_right_rotation(Node *tree);
Node * double_left_rotation(Node *tree);
Node * double_right_rotation(Node *tree);

int greater(Node *tree);

void print_node(Node *tree);
void print_tree(Node *tree);

#endif

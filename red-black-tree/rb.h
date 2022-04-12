#ifndef RB_H
#define RB_H

#include <stdbool.h>

enum color { RED, BLACK, DOUBLE_BLACK };

typedef int abstract_data;

typedef struct node_rb {
	abstract_data data;
	enum color color;
	struct node_rb *left, *right, *father;
} Node;

void init(Node **root);
void insert_node(abstract_data data, Node **root);
void delete_node(abstract_data data, Node **root);

abstract_data greater(Node *root);
int height(Node *tree);
int max(int n1, int n2);

void print_node(Node *node);
void print_tree(Node *tree);

void fix_insert(Node **root, Node *node);
void fix_delete(Node **root, Node *double_black_node);

void single_right_rotation(Node **root, Node *pivot);
void single_left_rotation(Node **root, Node *pivot);
void double_right_rotation(Node **root, Node *pivot);
void double_left_rotation(Node **root, Node *pivot);

enum color color(Node *node);
bool is_root(Node *node);
bool is_left_son(Node *node);
Node * brother(Node *node);
Node * uncle(Node *node);
void remove_double_black(Node **root, Node *node);

#endif

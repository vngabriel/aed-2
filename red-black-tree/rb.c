#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

Node * null_node;

void init(Node **root) {
	*root = NULL;

	null_node = (Node *) malloc(sizeof(Node));
	null_node->color = DOUBLE_BLACK;
	null_node->data = 0;
    null_node->left = NULL;
    null_node->right = NULL;
}

void insert_node(abstract_data data, Node **root) {
	Node *position, *father, *new_node;
	position = *root;
	father = NULL;

	 while (position != NULL) {
			father = position;
			if (data >= position->data) {
                position = position->right;
            } else {
                position = position->left;
            }
	}

	new_node = (Node *) malloc(sizeof(Node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->father = father;
	new_node->color = RED;

	if (is_root(new_node)) {
        *root = new_node;
    } else {
		if (data >= father->data) {
            father->right = new_node;
        }
		else {
            father->left = new_node;
        }
	}

	fix_insert(root, new_node);
}

void fix_insert(Node **root, Node *node) {
	while (color(node) == RED && color(node->father) == RED) {
        if (color(uncle(node)) == RED) {
            uncle(node)->color = BLACK;
            node->father->color = BLACK;
            node->father->father->color = RED;
			
            node = node->father->father;
            continue;
        } 
        if (is_left_son(node) && is_left_son(node->father)) {
            single_right_rotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        if (!is_left_son(node) && !is_left_son(node->father)) {
            single_left_rotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;

            continue;
        }
        if (!is_left_son(node) && is_left_son(node->father)) {
            double_right_rotation(root, node->father->father);
            node->color = BLACK;
            node->right->color = RED;

            continue;
        }
        if (is_left_son(node) && !is_left_son(node->father)) {
            double_left_rotation(root, node->father->father);
            node->color = BLACK;
            node->left->color = RED;

            continue;
        }
	}
	(*root)->color = BLACK;
}

void single_right_rotation(Node **root, Node *pivot){
    Node *u, *t1;
    u = pivot->left;
    t1 = u->right;

    bool pivot_is_left_son = is_left_son(pivot);
    
    pivot->left = t1;
    if (t1 != NULL) {
        t1->father = pivot;
    }
    u->right = pivot;
    u->father = pivot->father;
    pivot->father = u;
    
    if (is_root(u)) {
        *root = u;
    } else {
        if (pivot_is_left_son) {
            u->father->left = u;
        } else {
            u->father->right = u;
        }
    }
}

void single_left_rotation(Node **root, Node *pivot) {
    Node *u, *t2;
    u = pivot->right;
    t2 = u->left;

    bool pivot_is_left_son = is_left_son(pivot);

    pivot->right = t2;
    if (t2 != NULL) {
        t2->father = pivot;
    }

    u->left = pivot;
    u->father = pivot->father;
    pivot->father = u;

    if (is_root(u)) {
        *root = u;
    } else {
        if (pivot_is_left_son) {
            u->father->left = u;
        } else {
            u->father->right = u;
        }
    }
}

void double_right_rotation(Node **root, Node *pivot) {
    Node *u = pivot->left;

    single_left_rotation(root, u);
    single_right_rotation(root, pivot);
}

void double_left_rotation(Node **root, Node *pivot) {
    Node *u = pivot->right;

    single_right_rotation(root, u);
    single_left_rotation(root, pivot);
}

void delete_node(abstract_data data, Node **root) {

}

void fix_delete(Node **root, Node *node) {

}

enum color color(Node *node) {
	enum color c;

	if (node == NULL) {
        c = BLACK;
    } else {
        c = node->color;
    }

	return c;
}

bool is_root(Node *node) {
	return (node->father == NULL);
}

bool is_left_son(Node *node) {
	return (node->father != NULL && node == node->father->left);
}

Node * uncle(Node *node) {
	return brother(node->father);
}

Node * brother(Node *node) {
	if (is_left_son(node)) {
        return node->father->right;
    } else {
        return node->father->left;
    }
}

abstract_data greater(Node *root) {
	if (root == NULL) {
        return -1;
    } 
    
    if (root->right == NULL) {
		return root->data;
    } else {
	    return greater(root->right);
    }
}

void print_tree(Node *tree) {
	printf("(");
	if(tree != NULL) {
		print_node(tree);
		print_tree(tree->left);
		print_tree(tree->right);
	}
	printf(")");
}

void print_node(Node *node) {
	switch(node->color){
		case BLACK:
			printf("\x1b[30m[%d]\x1b[0m", node->data);
			break;
		case RED:
			printf("\x1b[31m[%d]\x1b[0m", node->data);
			break;
		case DOUBLE_BLACK:
			printf("\x1b[32m[%d]\x1b[0m", node->data);
			break;
	}
}
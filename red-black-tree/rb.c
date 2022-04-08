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
        // case 1
        if (color(uncle(node)) == RED) {
            uncle(node)->color = BLACK;
            node->father->color = BLACK;
            node->father->father->color = RED;
			
            node = node->father->father;
            continue;
        }
        // case 2a
        if (is_left_son(node) && is_left_son(node->father)) {
            single_right_rotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;
            
            continue;
        }
        // case 2b
        if (!is_left_son(node) && !is_left_son(node->father)) {
            single_left_rotation(root, node->father->father);
            node->father->color = BLACK;
            brother(node)->color = RED;

            continue;
        }
        // case 3a
        if (!is_left_son(node) && is_left_son(node->father)) {
            double_right_rotation(root, node->father->father);
            node->color = BLACK;
            node->right->color = RED;

            continue;
        }
        // case 3b
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
    Node *removable_node;
	removable_node = *root;

	while (removable_node != NULL) {
		if (data == removable_node->data) {
            if (removable_node->left != NULL && removable_node->right != NULL) {
    			removable_node->data = greater(removable_node->left);
	    		delete_node(removable_node->data, &(removable_node->left));

                break;
            }

			if (removable_node->left == NULL && removable_node->right != NULL) {
                Node *right_node = removable_node->right;
                removable_node->data = right_node->data;
                removable_node->right = NULL;

                free(right_node);

				break;
			}

			if (removable_node->left != NULL && removable_node->right == NULL) {
				Node *left_node = removable_node->left;
                removable_node->data = left_node->data;
                removable_node->left = NULL;

                free(left_node);

                break;
			}

			if (removable_node->left == NULL && removable_node->right == NULL) {				
				if (is_root(removable_node)) {
					*root = NULL;
                    free(removable_node);

					break;
				}

				if (removable_node->color == RED) {
					if (is_left_son(removable_node)) {
					    removable_node->father->left = NULL;
                    } else {
						removable_node->father->right = NULL;
                    }
                    free(removable_node);

					break;

				} else {
                    null_node->father = removable_node->father;
                    if (is_left_son(removable_node)) {
                        removable_node->father->left = null_node;
                    } else {
                        removable_node->father->right = null_node;
                    }
                    free(removable_node);
                    fix_delete(root, null_node);

                    break;
				}
			}
		} else {
            if (data >= removable_node->data) {
                removable_node = removable_node->right;
            } else {
                removable_node = removable_node->left;
            }
        }	
	}
}

void fix_delete(Node **root, Node *double_black_node) {
    // case 1
	if(is_root(double_black_node)) {
        remove_double_black(root, double_black_node);

		return;
	}

    // case 2
	if(color(double_black_node->father) == BLACK && color(brother(double_black_node)) == RED && 
    color(brother(double_black_node)->right) == BLACK && color(brother(double_black_node)->left) == BLACK) {

        if (is_left_son(double_black_node)) {
            single_left_rotation(root, double_black_node->father);
        } else {
            single_right_rotation(root, double_black_node->father);	
        }
        double_black_node->father->father->color = BLACK;
        double_black_node->father->color = RED;
        
        fix_delete(root, double_black_node);

        return;
	}

    // case 3
    if (color(double_black_node->father) == BLACK && color(brother(double_black_node)) == BLACK && 
    color(brother(double_black_node)->right) == BLACK && color(brother(double_black_node)->left) == BLACK) {

        Node *father = double_black_node->father;

        brother(double_black_node)->color = RED;
        father->color = DOUBLE_BLACK;

        remove_double_black(root, double_black_node);
        fix_delete(root, father);

        return;
    }	

    // case 4
	if (color(double_black_node->father) == RED && color(brother(double_black_node)) == BLACK && 
    color(brother(double_black_node)->right) == BLACK && color(brother(double_black_node)->left) == BLACK) {	

        double_black_node->father->color = BLACK;
        brother(double_black_node)->color = RED;
        remove_double_black(root, double_black_node);

		return;
	}

    // case 5a
	if (color(brother(double_black_node)) == BLACK && color(brother(double_black_node)->right) == BLACK &&
    color(brother(double_black_node)->left) == RED && !is_left_son(brother(double_black_node))) {	

        single_right_rotation(root, brother(double_black_node));
        brother(double_black_node)->color = BLACK;
        brother(double_black_node)->right->color = RED;

        fix_delete(root, double_black_node);

		return;
	}

    // case 5b
	if (color(brother(double_black_node)) == BLACK && color(brother(double_black_node)->right) == RED &&
    color(brother(double_black_node)->left) == BLACK && is_left_son(brother(double_black_node))) {	
		
        single_left_rotation(root, brother(double_black_node));
        brother(double_black_node)->color = BLACK;
        brother(double_black_node)->left->color = RED;

        fix_delete(root, double_black_node);
        
        return;
	}

	// case 6a
	if (color(brother(double_black_node)) == BLACK && color(brother(double_black_node)->right) == RED &&
    !is_left_son(brother(double_black_node))) {

        single_left_rotation(root, double_black_node->father);
        enum color aux_color = double_black_node->father->father->color;
        double_black_node->father->father->color = double_black_node->father->color;
        double_black_node->father->color = aux_color;
        uncle(double_black_node)->color = BLACK;

        remove_double_black(root, double_black_node);

		return;
	}

	// case 6b
	if (color(brother(double_black_node)) == BLACK && color(brother(double_black_node)->left) == RED &&
    is_left_son(brother(double_black_node))) {

        single_right_rotation(root, double_black_node->father);
        enum color aux_color = double_black_node->father->father->color;
        double_black_node->father->father->color = double_black_node->father->color;
        double_black_node->father->color = aux_color;
        uncle(double_black_node)->color = BLACK;

        remove_double_black(root, double_black_node);

		return;
	}
}

void remove_double_black(Node **root, Node *node) {
    if (node == null_node) {
        if (is_root(node)) {
            *root = NULL;
        } else {
            if (is_left_son(node)) {
                node->father->left = NULL;
            } else {
                node->father->right = NULL;
            }
        }
    } else {
        node->color = BLACK;
    }
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
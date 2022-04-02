#include "bst.h"
#include "utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Node * insert_node(Node *tree, int value)  {
    if (tree == NULL) {
        Node *node = (Node *) malloc(sizeof(Node));
        node->value = value;
        node->left = NULL;
        node->right = NULL;

        return node;
    } else {
        if (value >= tree->value) {
            tree->right = insert_node(tree->right, value);
        } else {
            tree->left = insert_node(tree->left, value);
        }
        return tree;
    }
}

Node * delete_node(Node *tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    if (value == tree->value) {
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        } else if (tree->left != NULL && tree->right == NULL) {
            Node *left = tree->left;
            free(tree);
            return left;
        } else if (tree->left == NULL && tree->right != NULL) {
            Node *right = tree->right;
            free(tree);
            return right;
        } else if (tree->left != NULL && tree->right != NULL) {
            int max_value = greater(tree->left);
            tree->value = max_value;
            tree->left = delete_node(tree->left, max_value);
            return tree;
        }
    } else {
        if (value >= tree->value) {
            tree->right = delete_node(tree->right, value);
        } else {
            tree->left = delete_node(tree->left, value);
        }
        return tree;
    }
}

bool search(Node *tree, int value) {
    if (tree != NULL) {
        if (value == tree->value) {
            return true;
        } else if (value >= tree->value) {
            search(tree->right, value);
        } else {
            search(tree->left, value);
        }
    } else {
        return false;
    }
}

int greater(Node *tree) {
    if (tree != NULL) {
        if (tree->right == NULL) {
            return tree->value;
        } else {
            greater(tree->right);
        }
    } else {
        return -1;
    }
}

int smaller(Node *tree) {
    if (tree != NULL) {
        if (tree->left == NULL) {
            return tree->value;
        } else {
            smaller(tree->left);
        }
    } else {
        return -1;
    }
}

int height(Node *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        return 1 + max(height(tree->left), height(tree->right));
    }
}

int sum(Node *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        return tree->value + sum(tree->left) + sum(tree->right);
    }
}

int count_primes(Node *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        if (is_prime(tree->value)) {
            return 1 + count_primes(tree->left) + count_primes(tree->right);
        } else {
            return count_primes(tree->left) + count_primes(tree->right);
        }
    }
}

int successor(Node *tree, int value) {
    if (tree != NULL) {
        Node *node = tree;
        Node *succ = NULL;

        while (node != NULL) {
            if (node->value == value) {
                break;
            } else if (value >= node->value) {
                node = node->right;
            } else {
                succ = node;
                node = node->left;
            }
        }

        if (node != NULL) {
            if (node->right != NULL) {
                smaller(node->right);
            } else if (succ != NULL) {
                return succ->value;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void path(Node *tree, int value) {
    if (search(tree, value)) {
        if (value == tree->value) {
            printf("[%d]", tree->value);
        } else if (value >= tree->value) {
            printf("[%d]", tree->value);
            path(tree->right, value);
        } else {
            printf("[%d]", tree->value);
            path(tree->left, value);
        }
    }
}

void pre_order(Node *tree) {
    if (tree != NULL) {
        printf("[%d]", tree->value);
        pre_order(tree->left);
        pre_order(tree->right);
    }
}

void in_order(Node *tree) {
    if (tree != NULL) {
        in_order(tree->left);
        printf("[%d]", tree->value);
        in_order(tree->right);
    }
}

void post_order(Node *tree) {
    if (tree != NULL) {
        post_order(tree->left);
        post_order(tree->right);
        printf("[%d]", tree->value);
    }
}

void reverse_order(Node *tree) {
    if (tree != NULL) {
        reverse_order(tree->right);
        printf("[%d]", tree->value);
        reverse_order(tree->left);
    }
}

#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    Node *tree = NULL;

    int option;
    int value;

    while (true) {
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                scanf("%d", &value);
                bool *grew = (bool *) malloc(sizeof(bool));
                *grew = false;
                tree = insert_node(tree, value, grew);
                break;
            case 2:
                scanf("%d", &value);
                bool *decreased = (bool *) malloc(sizeof(bool));
                *decreased = false;
                tree = delete_node(tree, value, decreased);
                break;
            case 3:
                print_tree(tree);
                printf("\n");
                break;
            case 10:
                printf("%d\n", height(tree));
                break;
            case 99:
                exit(0);
                break;
        }
    }

    return 0;
}

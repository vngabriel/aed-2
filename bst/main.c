#include "bst.h"
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
                tree = insert_node(tree, value);
                break;
            case 2:
                pre_order(tree);
                printf("\n");
                break;
            case 3:
                in_order(tree);
                printf("\n");
                break;
            case 4:
                post_order(tree);
                printf("\n");
                break;
            case 5:
                reverse_order(tree);
                printf("\n");
                break;
            case 6:
                printf("%d\n", count_primes(tree));
                break;
            case 7:
                scanf("%d", &value);
                printf("%d\n", successor(tree, value));
                break;
            case 8:
                scanf("%d", &value);
                path(tree, value);
                printf("\n");
                break;
            case 9:
                scanf("%d", &value);
                tree = delete_node(tree, value);
                break;
            case 99:
                exit(0);
                break;
        }
    }

    return 0;
}

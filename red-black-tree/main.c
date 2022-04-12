#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rb.h"

int main(int argc, char * argv[]) {
	Node *tree;
	int option;
	init(&tree);

	while (true) {
		scanf("%d", &option);

		switch (option) {
            abstract_data data;
            case 1:
                scanf("%d", &data);
                insert_node(data, &tree);
                break;
            case 2:
                scanf("%d", &data);
                delete_node(data, &tree);
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
		}
	}
}
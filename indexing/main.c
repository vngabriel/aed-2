#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "indexing.h"

int main(int argc, char * argv[]) {
    Table table;
    Book *book;
	int option, key;

	if (!init_table(&table)) {
        printf("Error starting data file!");
        exit(0);
    }

	while (true) {
		scanf("%d", &option);

		switch (option) {
            int valor;
            case 1:
                add_book(&table, read_data());
                break;
            case 2:
                scanf("%d", &key);
                book = search_book(&table, key);
                if (book != NULL) {
                    printf("Code: %d\n", book->code);
                    printf("Title: %s\n", book->title);
                    printf("Author: %s\n", book->author);
                    printf("Year: %d\n", book->year);
                } else {
                    printf("Book not find!\n");
                }
                break;

            case 3:
                pre_order(table.indexes);
                printf("\n");
                break;
                
            case 99:
                finish(&table);
                exit(0);
		}
	}

    return 0;
}
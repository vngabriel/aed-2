#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "indexing.h"

bool init_table(Table *table) {
    init(&table->indexes);	
	table->data_file = fopen(DATA_PATH, "a+");
	load_file(INDEXES_PATH, &table->indexes);
	if (table->data_file != NULL) {
		return true;
    } else {
		return false;
    }
}

void finish(Table *table) {
    fclose(table->data_file);
	save_file(INDEXES_PATH, table->indexes);
}

void add_book(Table *table, Book *book) {
    if(table->data_file != NULL) {
        abstract_data *new_index = (abstract_data *) malloc(sizeof(abstract_data));
        new_index->key = book->code;

        fseek(table->data_file, 0L, SEEK_END);
        new_index->index = ftell(table->data_file);
        
        fprintf(table->data_file, "CODE=%d\n", book->code);
        fprintf(table->data_file, "TITLE=%s\n", book->title);
        fprintf(table->data_file, "AUTHOR=%s\n", book->author);
        fprintf(table->data_file, "YEAR=%d\n", book->year);
        fprintf(table->data_file, "#\n");

        insert_node(new_index, &table->indexes);
	}
}

Book * search_book(Table *table, int key) {
    if (table->data_file != NULL) {
        Node *temp;
        temp = table->indexes;

        while (temp != NULL) {
            if (temp->data->key == key) {
                Book *book = (Book *) malloc(sizeof(Book));
                char *buffer = (char *) malloc(356 * sizeof(char)); // the size of the buffer is bigger because the line in the file have the property string

                fseek(table->data_file, temp->data->index, SEEK_SET);
                fgets(buffer, 355, table->data_file);

                if (strcmp(buffer, "#\n") != 0) {
                    book->code = atoi(get_value(buffer));

                    fgets(buffer, 355, table->data_file);
                    book->title = strdup(get_value(buffer));

                    fgets(buffer, 355, table->data_file);
                    book->author = strdup(get_value(buffer));

                    fgets(buffer, 355, table->data_file);
                    book->year = atoi(get_value(buffer));
                }

                free(buffer);
                return book;
            } else {
                if (key >= temp->data->key) {
                    temp = temp->right;
                } else {
                    temp = temp->left;                
                }
            }
        }
    }

    return NULL;
}

Book * read_data() {
    Book *new_book = (Book *) malloc(sizeof(Book));
    char *buffer = (char *) malloc(256 * sizeof(char));

	printf("Code: ");
	scanf("%d", &new_book->code);
    getchar();

	printf("Title: ");
	fgets(buffer, 255,  stdin);
	remove_enter_character(buffer);
    new_book->title = strdup(buffer);

	printf("Author: ");
    fgets(buffer, 255,  stdin);
    remove_enter_character(buffer);
    new_book->author = strdup(buffer);

	printf("Year: ");
	scanf("%d", &new_book->year);
    getchar();

    free(buffer);

	return new_book;
}

void remove_enter_character(char *string) {
    string[strlen(string) -1] = '\0';
}   

void save_file(char *name, Node *tree) {
    FILE *file;
	file = fopen(name, "wb");
	if (file != NULL) {
		save_tree(tree, file);
		fclose(file);
	}
}

void save_tree(Node *root, FILE *file) {
    if (root != NULL) {
        fwrite(root->data, sizeof(abstract_data), 1, file);
		save_tree(root->left, file);
		save_tree(root->right, file);
	}
}

void load_file(char *name, Node **tree) {
    FILE *file = fopen(name, "rb");
	abstract_data *temp;
	if (file != NULL) {
		temp = (abstract_data *) malloc(sizeof(abstract_data));
		while(fread(temp, sizeof(abstract_data), 1, file)) {
			
			insert_node(temp, tree);			
			temp = (abstract_data *) malloc(sizeof(abstract_data));
		}
		fclose(file);
	}
}

char * get_value(char *string) {
    int i = 0, j, k;
    char *value = (char *) malloc(256 * sizeof(char));

    // finding the equals sign
    while (string[i] != '=' && string[i] != '\0') {
        i++;
    }

    // i + 1 is the position of the equal sign
    // goes until strlen(string) - 1 because the last character is the \n
    for (j = i + 1, k = 0; j < strlen(string) - 1; j++, k++) {
        value[k] = string[j];
    }

    return value;
}

// --- red black tree code ---
void init(Node **root) {
	*root = NULL;
}

void insert_node(abstract_data *data, Node **root) {
	Node *position, *father, *new_node;
	position = *root;
	father = NULL;

    while (position != NULL) {
        father = position;
        if (data->key >= position->data->key) {
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
		if (data->key >= father->data->key) {
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

void pre_order(Node *tree) {
    if (tree != NULL) {
        printf("[%d]", tree->data->key);
        pre_order(tree->left);
        pre_order(tree->right);
    }
}

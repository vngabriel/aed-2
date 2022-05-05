#ifndef INDEXING_H
#define INDEXING_H

#include <stdbool.h>
#include <stdio.h>

#define DATA_PATH "storage/data.txt"
#define INDEXES_PATH "storage/indexes.dat"

enum color { RED, BLACK, DOUBLE_BLACK };

typedef struct book {
	int code;
	char *title;
	char *author;
	int year;
} Book;

typedef struct index {
	int key; // key refers to the book code
	int index;
} Index;

typedef Index abstract_data;

typedef struct node_rb {
	abstract_data *data;
	enum color color;
	struct node_rb *left, *right, *father;
} Node;

typedef struct table {
	FILE *data_file;
	Node *indexes;
} Table;

bool init_table(Table *table);
void finish(Table *table);
void add_book(Table *table, Book *book);
Book * search_book(Table *table, int key);

Book * read_data();
void remove_enter_character(char *string);
void save_file(char *name, Node * tree);
void save_tree(Node *root, FILE *file);
void load_file(char *name, Node **tree);
char * get_value(char *string);

void init(Node **root);
void insert_node(abstract_data *data, Node **root);
void fix_insert(Node **root, Node *node);

void single_right_rotation(Node **root, Node *pivot);
void single_left_rotation(Node **root, Node *pivot);
void double_right_rotation(Node **root, Node *pivot);
void double_left_rotation(Node **root, Node *pivot);

enum color color(Node *node);
bool is_root(Node *node);
bool is_left_son(Node *node);
Node * brother(Node *node);
Node * uncle(Node *node);
void pre_order(Node *tree);

#endif

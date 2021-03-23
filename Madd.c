#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct binary_tree binary_tree;
typedef struct element element;
typedef struct hash_table hash_table;

#define SIZE_ASCII 256

struct binary_tree{
  int item;
  binary_tree *left;
  binary_tree *right;
};

binary_tree* create_empty_binary_tree()
{
  return NULL;
}

binary_tree* create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
  binary_tree *new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
  new_binary_tree->item = item;
  new_binary_tree->left = left;
  new_binary_tree->right = right;
  return new_binary_tree;
}

binary_tree* add(binary_tree *bt, int item)
{
  if(bt == NULL)
  {
    bt = create_binary_tree(item, NULL, NULL);
  }
  else if(bt->item > item)
  {
    bt->left = add(bt->left, item);
  }
  else
  {
    bt->right = add(bt->right, item);
  }
  return bt;
}

int is_leaf(binary_tree *bt){

    return ((bt->left == NULL)&&(bt->right == NULL));

}

struct element{
    char letter[SIZE_ASCII];
};

struct hash_table{
    element *table[SIZE_ASCII];
};

hash_table *create_hash_table(){
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for(i = 0; i < SIZE_ASCII; i++){
        new_hash_table->table[i] = (element*) malloc(sizeof(element));
    }
    return new_hash_table;
}

void mapeamento(hash_table *ht, binary_tree *bt, char *letter_string, int index, char item) { 
	if(index == -1){
		
		letter_string[index] = 64;
	    if(bt!=NULL)
	    {
	        letter_string[index + 1] = '\0';
	        //printf("[%s][%c]\n", letter_string, bt->item);
	        strcpy(ht->table[(int) bt->item]->letter, letter_string);
	    }
	}
	if(index > -1){
		
		letter_string[index] = item;
	    if(bt!=NULL)
	    {
	        letter_string[index + 1] = '\0';
	        //printf("[%s][%c]\n", letter_string, bt->item);
	        strcpy(ht->table[(int) bt->item]->letter, letter_string);
	    }
	}

	if(bt->left != NULL){
	    mapeamento(ht, bt->left, letter_string, index + 1, '-');
	}

	if(bt->right != NULL){
	    mapeamento(ht, bt->right, letter_string, index + 1, '|');
	}

}

void print_message(binary_tree *bt, char *aux, int index){

	if(aux[index] == '-'){
		print_message(bt->left, aux, index+1);
	}
	else if(aux[index] == '|'){
		print_message(bt->right, aux, index+1);
	}
	else if(aux[index] == '@'){
		printf("M");
	}
	else{
		printf("%c", bt->item);
	}

}

void print_binary_tree(binary_tree *bt)
{
  if(bt != NULL)
  {
    print_binary_tree(bt->left);
    printf(" %c", bt->item);
    print_binary_tree(bt->right);
  }
}

int main() {
	char ger[30] = {'M','G','T','C','K','Q','W','A','E','I','L','O','R','U','Y',' ','B','D','F','H','J','N','P','S','V','X','Z'};
	binary_tree *bt = create_empty_binary_tree();
	hash_table *ht = create_hash_table();
	int i, j = 0;
	char input;
	char aux[30];
	for(i = 0; i < 27; i++){
		bt = add(bt, ger[i]);
	}
	//print_binary_tree(bt);
	char letter_string[SIZE_ASCII];
	mapeamento(ht, bt, letter_string, -1, '-');
	while(scanf("%c", &input) != EOF){
		if(input != '*'){
			aux[j] = input;
			j++;
		}
		else{
			//printf("%s\n", aux);
			print_message(bt, aux, 0);
			j = 0;
			for(i = 0; i < 30; i++){
				aux[i] = '\0';
			}
		}
	}
	return 0;
}
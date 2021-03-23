#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct binary_tree binary_tree;
typedef struct element element;
typedef struct hash_table hash_table;

int size, preorder[100], inorder[100], postorder[100], k = 0, l = 0, m = 0;

struct element{
    int numbers[2];
};

struct hash_table{
    element *table[100];
};

struct binary_tree{
  int item;
  binary_tree *left;
  binary_tree *right;
};

hash_table* create_hash_table()
{
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for (i = 0; i < size; i++) {
    new_hash_table->table[i] = (element*) malloc(sizeof(element));
    }
    return new_hash_table;
}

int is_empty(binary_tree *bt){
  return (bt == NULL);
}

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

binary_tree* add(binary_tree *bt, hash_table *ht, int i)
{
  //printf("%d ", i);

  if(is_empty(bt))
  {
    bt = create_binary_tree(i, NULL, NULL);
  }

  if(i == -1){
    return;
  }

  bt->left = add(bt->left, ht, (int) ht->table[i]->numbers[0]);

  bt->right = add(bt->right, ht, (int) ht->table[i]->numbers[1]);

  return bt;
}

void print_binary_tree_pre_order(binary_tree *bt)
{
  if(!is_empty(bt))
  {
     if(bt->item!=-1){
        preorder[k] = bt->item;
        //printf("[%d][%d]", bt->item, k);
        k++;
    }
    print_binary_tree_pre_order(bt->left);
    print_binary_tree_pre_order(bt->right);
  }
}

void print_binary_tree_in_order(binary_tree *bt)
{
  if(!is_empty(bt))
  {
    print_binary_tree_in_order(bt->left);
    if(bt->item!=-1){
        inorder[l] = bt->item;
        l++;
    }
    print_binary_tree_in_order(bt->right);
  }
}

void print_binary_tree_post_order(binary_tree *bt)
{
  if(!is_empty(bt))
  {
    print_binary_tree_post_order(bt->left);
    print_binary_tree_post_order(bt->right);
    if(bt->item!=-1){
        postorder[m] = bt->item;
        m++;
    }
  }
}

int main(){
  binary_tree *bt = create_empty_binary_tree();
  int item1, item2, root, i, j, tree[100];
  scanf("%d", &size);
  hash_table *ht = create_hash_table();
  printf("\n");
  for(i = 0; i < size; i++){
      scanf("%d", &item1);
      scanf("%d", &item2);
      ht->table[i]->numbers[0] = item1;
      ht->table[i]->numbers[1] = item2;
      //printf("[%d][%d]", ht->table[i]->numbers[0], ht->table[i]->numbers[1]);
  }
  scanf("%d", &root);
  //printf("%d", root);
  bt = add(bt, ht, root);
  print_binary_tree_pre_order(bt);
  print_binary_tree_in_order(bt);
  print_binary_tree_post_order(bt);
  printf("Pre Order:\n");
  for(i = 0; i<size; i++){
      for(j = 0; j < size; j++){
        if(preorder[j] == i){
           if(j == 0){
            printf("Node %d: previous = -1 next = %d\n", i, preorder[j+1]);
           }
           else if(j == size-1){
            printf("Node %d: previous = %d next = -1\n", i, preorder[j-1]);
           }
           else{
            printf("Node %d: previous = %d next = %d\n", i, preorder[j-1], preorder[j+1]);
           }
        }
      }
  }
  printf("In Order\n");
  for(i = 0; i<size; i++){
      for(j = 0; j < size; j++){
        if(inorder[j] == i){
           if(j == 0){
            printf("Node %d: previous = -1 next = %d\n", i, inorder[j+1]);
           }
           else if(j == size-1){
            printf("Node %d: previous = %d next = -1\n", i, inorder[j-1]);
           }
           else{
            printf("Node %d: previous = %d next = %d\n", i, inorder[j-1], inorder[j+1]);
           }
        }
      }
  }
  printf("Post Order\n");
  for(i = 0; i<size; i++){
      for(j = 0; j < size; j++){
        if(postorder[j] == i){
           if(j == 0){
            printf("Node %d: previous = -1 next = %d\n", i, postorder[j+1]);
           }
           else if(j == size-1){
            printf("Node %d: previous = %d next = -1\n", i, postorder[j-1]);
           }
           else{
            printf("Node %d: previous = %d next = %d\n", i, postorder[j-1], postorder[j+1]);
           }
        }
      }
  }
  printf("\n");
  return 0;
}
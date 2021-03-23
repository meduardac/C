#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int value;
	struct node *next;
}node;

typedef struct hash_table_
{
	node* table[100];
}hash_table;

hash_table *create_hash_table(int q)
{
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));
    int i;
    for(i=0;i<q;i++)
    {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;

}

node *create_node(int key,int value)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->value = value;
	new_node->key = key;
	new_node->next = NULL;
	return new_node;
}

node* add(node *head,int key,int value)
{
	if (head!=NULL)
	{
		if (head->key == key)
		{
			return head;
		}
		head->next = add(head->next,key,value);
		return head;
	}
	else
	{
		node* new_node = (node*) malloc(sizeof(node));
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;
		return new_node;
	}
}

void put(hash_table *ht, int key, int value)
{
	int h = key % value;
	ht->table[h] = add(ht->table[h],key,value);
}


void print(hash_table *ht,int q)
{
	int i;
	for (i = 0; i < q; ++i)
	{
	    printf("%d -> ",i);
		node *temp = ht->table[i];
	    while(temp != NULL)
	    {
	    	printf("%d -> ",temp->key);
	    	//printf("\n");
	    	temp = temp->next;
	    }
	    	printf("\\\n");
	}
}


int main()
{
	int n,d,q;
	scanf("%d",&n);
	int i,j;
	for (j = 0; j < n; ++j)
	{
	    scanf("%d",&d);
	    scanf("%d",&q);
	    int a[q];
		hash_table *ht = create_hash_table(q);
		for (i = 0; i < q; ++i)
		{
			scanf("%d",&a[i]);
			put(ht,a[i],d);
		}
	    print(ht,d);
	    printf("\n");
	}

	return 0;
}

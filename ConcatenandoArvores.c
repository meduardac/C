#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//int d = -1;
typedef struct binary_tree
{
    int item;
    //int depth;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

binary_tree *create_empty_binary_tree()
{
    return NULL;
}

binary_tree *create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
    if (item == -1)
    {
        return NULL;
    }
    //d++;
    binary_tree *new_bt = (binary_tree *)malloc(sizeof(binary_tree));
    new_bt->item = item;
    //new_bt->depth = d;
    new_bt->left = left;
    new_bt->right = right;
    //d--;
    return new_bt;
}

int cast(char *array, int size, int sinal)
{
    int j, power = 1, sum = 0;
    for (j = size - 1; j >= 0; --j)
    {
        sum += ((array[j] % 48) * power);
        power *= 10;
    }

    return (sinal) ? sum : sum * -1;
}

int i = 1;
binary_tree* add_string_to_binary_tree(binary_tree *bt, char *tree)
{
	if(tree[i] == '(' )
	{
		i++;
		bt->left = add_string_to_binary_tree(bt->left, tree);

		if (tree[i] == '(')
		{
			i++;
			bt->right = add_string_to_binary_tree(bt->right, tree);
		}
		
	}else if(tree[i] != '\n' && tree[i] != ')' )
	{
	    int j = 0, sinal = 1;
	    char n[8];

        while (tree[i] != '(' && tree[i] != ')')
		{
			if (tree[i] == '-') {
				sinal = 0;
				i++;
			} else {
				n[j] = tree[i];
				j++;
				i++;
			}	
		}

		int item = cast (n, j, sinal);
		bt = create_binary_tree (item, NULL, NULL);

		if(tree[i] == '(')
		{
			i++;
			bt->left = add_string_to_binary_tree(bt->left, tree);

			if(tree[i] == '(')
			{
				i++;
				bt->right = add_string_to_binary_tree(bt->right, tree);
			}
		}
	}
	
	i++;
	return bt;
}

void search_insert(binary_tree *bt, int item, binary_tree *btaux)
{
    if (bt == NULL)
    {
        return;
    }
    else
    {
        if (bt->item == item)
        {
            bt->left = btaux->left;
            bt->right = btaux->right;
        }
        search_insert(bt->left, item, btaux);
        search_insert(bt->right, item, btaux);
    }
}

int is_empty(binary_tree *bt)
{
    return (bt == NULL);
}

void print_pre_order(binary_tree *bt)
{

    if (is_empty(bt))
    {
        printf("()");
    }

    if (!is_empty(bt))
    {
        printf("(%d", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
        printf(")");
    }
}

int main()
{
    int j;
    char s[10000], aux[10000];
    binary_tree *bt = create_empty_binary_tree();
    binary_tree *btaux;
    while (scanf("%s", s) != EOF)
    {
        if(strcmp(s, "()") == 0)
        {
            break;
        }
        btaux = add_string_to_binary_tree(btaux, s);
        i = 1;

        if (bt == NULL)
        {
            bt = btaux;
        }
        else
        {
            if (btaux != NULL)
            {
                search_insert(bt, btaux->item, btaux);
            }
            
            
        }
        
    }
    print_pre_order(bt);
    printf("\n");

    return 0;
}
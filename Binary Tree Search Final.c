#include <stdio.h>

int executor(int (*f) (int*,int,int,int,int), int array[], int tam, int escolha, int begin, int end)
{
	return f(array,tam,escolha,begin,end);
}

int tree_recursive(int array[], int tam , int escolha, int begin , int end)
{
	int middle;

	while(begin <= end)
	{
		middle = (begin+end)/2;
		if (array[middle] < escolha)
		{
			return tree_recursive(array,tam,escolha,(middle+1),end);
		}
		else if (array[middle] > escolha)
		{
			return tree_recursive(array,tam,escolha,begin,(middle-1));
		}
		else
		{
			return array[middle];
			break;
		}
	}
	return 0;
}

void executor2(void (*g)(int*, int, int),int* array, int tam, int escolha)
{
	g(array,tam,escolha);
}

void tree(int* array, int tam, int escolha)
{
	int begin,end,middle;
	begin = 0;
	end = tam - 1;
	while (begin <= end)
	{
		middle = (begin + end)/2;
		if (array[middle] < escolha)
		{
			begin = middle + 1;
		}
		else if (array[middle] > escolha)
		{
			end = middle - 1;
		}
		else if (array[middle] == escolha)
		{
			printf("%d\n",array[middle]);
			break;
		}
	}
	return ;
}

int main()
{
	//int (*f)(int*,int,int,int,int);
	int tam = 10;
	int escolha = 48;
	int array[10]={3,8,13,19,24,33,48,76,132,187};
	printf("%d\n",executor(tree_recursive,array,tam,escolha,0,tam-1));
	printf("\n");
	executor2(tree,array,tam,escolha);
}

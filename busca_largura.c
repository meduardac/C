#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int prev[MAX];
int matrix[MAX][MAX] = {0};

typedef struct node
{
	int item;
	struct node *next;
}node;

typedef struct queue
{
	node *front;
	node *rear;
}queue;

typedef struct adj_list
{
	int item;
	struct adj_list *next;
}adj_list;

typedef struct graph
{
	int matrix[MAX][MAX];
	adj_list *vertices[MAX];
	int visited[MAX];
	//int prev[MAX];
}graph;

queue *create_queue()
{
	queue *new_queue = (queue*) malloc(sizeof(queue));
	new_queue->front = new_queue->rear = NULL;
	return new_queue;
}

void enqueue(queue *queue,int item)
{
	node* new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = NULL;
	if (queue->front == NULL && queue->rear == NULL)
	{
		queue->front = queue->rear = new_node;
	}
	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
}

int dequeue(queue *queue)
{
	if (queue->front == NULL)
	{
		return -1;
	}
	node *temp = queue->front;
	queue->front = queue->front->next;

	if (queue->front == NULL)
	{
		queue->rear = NULL;
	}

	return temp->item;
}

int is_empty(queue *queue)
{
	if (queue->front == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void print_queue(queue *queue)
{
	node *temp = queue->front;
	while(temp != NULL)
	{
		printf("%d\n",temp->item );
		temp = temp->next;
	}
}

graph *create_graph(int d)
{
	graph *new_graph = (graph*) malloc(sizeof(graph));
	int i;
	for (i = 0; i < d; ++i)
	{
		new_graph->vertices[i] = NULL;
		new_graph->visited[i] = 0;
		//new_graph->prev[i] = -1;
	}
	return new_graph;
}

adj_list *create_adj_list(int item)
{
	adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
	new_adj_list->item = item;
	new_adj_list->next = NULL;
	//printf("%d\n",new_adj_list->item);
	return new_adj_list;
}

void swap(adj_list *h1, adj_list *h2)
{
	int temp = h1->item;
	h1->item = h2->item;
	h2->item = temp;
}

void SelectionSort(adj_list *head)
{
	if (head == NULL)
	{
		return ;
	}
	adj_list *start = head;
	adj_list *temp;
	adj_list *min;
	while(start->next)
	{
		min = start;
		temp = start->next;
		while(temp)
		{
			if (min->item > temp->item)
			{
				min = temp;
			}
			temp = temp->next;
		}
		swap(start,min);
		start = start->next;
	}
}

void add_edge(graph *graph,int vertex1,int vertex2,int d)
{
	matrix[vertex1][vertex2] = 1;
	adj_list *vertex = create_adj_list(vertex2);
	vertex->next = graph->vertices[vertex1];
	graph->vertices[vertex1] = vertex;

}

void print(graph *graph,int d)
{
	int i;
	for (i = 0; i < d; ++i)
	{
		//printf("%d\n",graph->prev[i]);
		SelectionSort(graph->vertices[i]);
		adj_list *temp = graph->vertices[i];
		printf("Adjacency List of vertex%d\n",i );
		while(temp!= NULL)
		{
			if (temp->item != -1)
			{
				printf("-> %d",temp->item );
			}
			temp = temp->next;
		}
		printf("\n");
	}
}

void print_matrix(int d)
{
	int i,j;
	for ( i = 0; i < d; ++i)
	{
		for (j = 0; j < d; ++j)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}

void print_path(graph *graph,int w)
{
	if (prev[w] != -1)
	{
		print_path(graph,prev[w]);
	}
	if (prev[w]!= -1)
	{
		printf(" %d =>",prev[w]);
	}
}

int count_path(graph *graph,int w,int destiny)
{
	if(prev[w] != -1)
	{
		return 1 + count_path(graph,prev[w],destiny);
	}
	return 0; 
}

void bfs(graph *graph,int source,int destiny,int v,int k)
{
	int i;
	for (i = 0; i < v; ++i)
	{
		graph->visited[i] = 0;
		prev[i] = -1;
		SelectionSort(graph->vertices[i]);
	}
	adj_list *temp = graph->vertices[source];
	printf("Caso de Teste #%d - BFS(%d)\n",k,source);
	printf("\n");
	queue *fila = create_queue();
	int dequeued;
	printf("Iniciando busca em largura a partir de %d\n",source);
	graph->visited[source] = 1;
	enqueue(fila,source);

		while(!is_empty(fila))
		{
			dequeued = dequeue(fila);
			temp = graph->vertices[dequeued];
			while(temp!=NULL)
			{
				//printf("aqui\n");
				if (!graph->visited[temp->item])
				{
					printf("Iniciando busca em largura a partir de %d\n",temp->item);
					graph->visited[temp->item] = 1;
					prev[temp->item] = dequeued;
					enqueue(fila,temp->item);
					//printf("%d\n",graph->prev[temp->item]);
				}
				temp = temp->next;
			}
		}
}

void bfs2(graph *graph,int source,int destiny,int v)
{
	int i;
	for (i = 0; i < v; ++i)
	{
		graph->visited[i] = 0;
		prev[i] = -1;
	}
	//SelectionSort(graph->vertices[source]);
	adj_list *temp = graph->vertices[source];
	//printf("Caso de Teste #1 - BFS(%d)\n",source);
	queue *fila = create_queue();
	int dequeued;
	//printf("Iniciando busca em largura a partir de %d\n",source);
	graph->visited[source] = 1;
	enqueue(fila,source);

		while(!is_empty(fila))
		{
			dequeued = dequeue(fila);
			temp = graph->vertices[dequeued];
			if (dequeued == destiny)
			{
				break;
			}
			while(temp!=NULL)
			{
				//printf("aqui\n");
				if (!graph->visited[temp->item])
				{
					//printf("Iniciando busca em largura a partir de %d\n",temp->item);
					graph->visited[temp->item] = 1;
					prev[temp->item] = dequeued;
					enqueue(fila,temp->item);
					//printf("%d\n",graph->prev[temp->item]);
				}
				temp = temp->next;
			}
		}
}


void print_formatted(graph *graph ,int o, int d, int v)
{
	printf("\n");
	int i;
	for ( i = 0; i < v; ++i)
	{
		bfs2(graph,o,i,v);
		if((count_path(graph,i,d) == 0 && i!= o) && (prev[i] == -1))
		{
			printf("%d | - | -\n",i);
		}
		else if (count_path(graph,i,d) == 0 && i!= o)
		{
			printf("%d | - | %d\n",i,prev[i]);
		}
		else if (prev[i] == -1)
		{
			printf("%d | %d | -\n",i,count_path(graph,i,d));
		}
		else
		{
			printf("%d | %d | %d\n",i,count_path(graph,i,d),prev[i]);
		}
	}
	printf("\n");
	bfs2(graph,o,d,v);
	if (prev[d] != -1 || o == d)
	{
		printf("Caminho entre %d e %d:",o,d);
		print_path(graph,d);
		printf(" %d\n",d);
	}
	else
	{
		printf("Sem caminho entre %d e %d\n",o,d);
	}
	printf("\n");
	printf("--------\n");
}

int main()
{
	int v,a,t,i,o,d;
	int x1,x2;
	scanf("%d %d %d",&v,&a,&t);
	graph *graph = create_graph(v);

	for (i = 0; i < a; ++i)
	{
		scanf("%d %d",&x1,&x2);
		add_edge(graph,x1,x2,v);
	}
	//print(graph,v);
	printf("--------\n");
	printf("\n");
	for (i = 0; i < t; ++i)
	{
		scanf("%d %d",&o,&d);
		bfs(graph,o,d,v,i+1);
		print_formatted(graph,o,d,v);
		printf("\n");
	}
	/*scanf("%d %d",&o,&d);
	bfs(graph,7,4,v,i);
	print_formatted(graph,7,4,v);*/
	//bfs2(graph,o,6);
	return 0;

}

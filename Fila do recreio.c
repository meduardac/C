	#include <stdio.h>
	#include <stdlib.h>

	int cont = 0;

	typedef struct node_ {
		int item;
		int priority;
		struct node_ *next;
	}node;

	typedef struct priority_queue_{
		node *head;
	}priority_queue;

	priority_queue *create_priority_queue();

	void enqueue(priority_queue *pq,int i,int p);

	node *dequeue(priority_queue *pq);

	int maximum(priority_queue *pq);

	int is_empty(priority_queue *pq);

	void print_priority_queue(priority_queue *pq);

	void search(priority_queue *pq);

	int main()
	{
		int n,a,i,j;
		scanf("%d",&n);
		for (j = 0; j < n; ++j)
		{
		    priority_queue* fila = create_priority_queue();
			scanf("%d",&a);
			int p[a];
			for (i = 0; i < a; ++i)
			{
				scanf("%d",&p[i]);
				enqueue(fila,i,p[i]);
			}
			search(fila,p);
			//print_priority_queue(fila);
			printf("%d",maximum(pq));
			//printf("%d\n",cont);
			cont = 0;
		}

		return 0;
	}

	priority_queue *create_priority_queue()
	{
		priority_queue* new_queue = (priority_queue*) malloc(sizeof(priority_queue));
		new_queue->head = NULL;
		return new_queue;
	}

	void enqueue(priority_queue *pq,int i,int p)
	{
		node *new_node = (node*) malloc(sizeof(node));
		new_node->item = i;
		new_node->priority = p;
		if ((is_empty(pq)) ||(p > pq->head->priority))
		{
			if (is_empty(pq)) cont+=0;
			else
			{
				new_node->next = pq->head;
				pq->head = new_node;
				cont+=2;
			}
		}
		else
		{
			node *temp = pq->head;
			while((temp->next != NULL) && (temp->next->priority > p))
			{
				temp = temp->next;
			}
			if (temp->next == NULL)
			{
				cont+=0;
				new_node->next = temp->next;
				temp->next = new_node;
			}
			else
			{
				new_node->next = temp->next;
				temp->next = new_node;
				cont+=2;
			}
		}
	}

	node *dequeue(priority_queue *pq)
	{
		if (is_empty(pq))
		{
			return NULL;
		}
		else
		{
			node *temp = pq->head;
			pq->head = pq->head->next;
			temp->next = NULL;
			return temp;
		}
	}

	int maximum(priority_queue *pq)
	{
		if (is_empty(pq))
		{
			return -1;
		}
		else
		{
			return pq->head->item;
		}
	}

	int is_empty(priority_queue* pq)
	{
	    if(pq->head == NULL)
	    {
	    	return 1;
	    }
	    else
	    {
	    	return 0;
	    }
	}

	void print_priority_queue(priority_queue *pq)
	{
		node *temp = pq->head;
		while(temp != NULL)
		{
			printf("%d\n",temp->priority);
			temp = temp->next;
		}
	}

	void search(priority_queue *pq, int *array)
	{
		int i = 0;
		node *temp = pq->head;
		while(temp != NULL)
		{
		    if (temp->priority == array[i])
	        {
	            cont++;
	        }
				temp = temp->next;
				i++;
		}
	}


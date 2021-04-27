#include <stdio.h>
#include <stdlib.h>
struct Node{
	struct Node *next;
	int val;
};

struct Queue{
	struct Node *first;
	struct Node *last;
};

struct Node* createNode(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->next = NULL;
	node->val = value;
	return node;
}

struct Queue* createQueue()
{
	struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->first = NULL;
	queue->last = NULL;
	return queue;
}

void printNode(struct Node *node)
{
	printf("val = %d\n", node->val);
}

void add(struct Queue *queue, struct Node *node)
{
	if(!queue->first)
	{
		queue->first = node;
		queue->last = node;
	}
	else
	{
		struct Node *tmpNode = queue->last;
		tmpNode->next = node;
		queue->last = node;
	}
}

void pop(struct Queue *queue)
{
	if(!queue->first)
	{
		printf("Brak elementow w kolejce\n");
	}
	else
	{
		printNode(queue->first);
		struct Node* node = queue->first;
		queue->first = node->next;
		free(node);
	}
}


int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	struct Queue *queue = createQueue();
	
	for(int i = 0; i < n; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		struct Node *node = createNode(tmp);
		add(queue, node);
		printf("Dodaje element %d do kolejki\n", tmp);
		
	}
	printf("\nwszystkie elementy zostaly dodane\n\n");
	for(int i = 0; i <= n; i++)
	{
		printf("proba usuniecia z kolejki, ");
		pop(queue);
	}
	return 0;
}










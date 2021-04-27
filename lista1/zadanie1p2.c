#include <stdio.h>
#include <stdlib.h>
struct Node{
	struct Node *before;
	int val;
};

struct Queue{
	struct Node *first;
	struct Node *last;
};

struct Node* createNode(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->before = NULL;
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
		node->before = tmpNode;
		queue->last = node;
	}
}

void pop(struct Queue *queue)
{
	if(!queue->last)
	{
		printf("Brak elementow na stosie\n");
	}
	else
	{
		printNode(queue->last);
		struct Node* node = queue->last;
		queue->last = node->before;
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
		printf("Dodaje element %d do stosu\n", tmp);
		
	}
	printf("\nwszystkie elementy zostaly dodane\n\n");
	for(int i = 0; i <= n; i++)
	{
		printf("proba usuniecia ze stosu, ");
		pop(queue);
	}
	return 0;
}










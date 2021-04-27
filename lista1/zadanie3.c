#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Node{
	struct Node *next, *prev;
	int val;
};

struct List{
	struct Node *first;
};

struct Node* createNode(int value)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->next = NULL;
	node->prev = NULL;
	node->val = value;
	return node;
}

struct List* createList()
{
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list->first = NULL;
	return list;
}

void printNode(struct Node *node)
{
	printf("val = %d\n", node->val);
}

void addToFirst(struct List *list, struct Node *node)
{
	if(!list->first)
	{
		list->first = node;
		list->first->next = node;
		list->first->prev = node;
	}
	else
	{
		struct Node *tmpNode = list->first->next;
		node->next = tmpNode;
		tmpNode->prev = node;
		node->prev = list->first;
		list->first->next = node;
	}
}

void printList(struct List *list)
{
	printf("\n----current-list-content----\n");
	if(!list)
	{
		printf("Lista jest pusta :(\n");
	}
	else
	{
		struct Node *curNode = list->first;
		while(curNode->next != list->first)
		{
			printNode(curNode);
			curNode = curNode->next;
				
		}
		printNode(curNode);
	}
	printf("----------------------------\n\n");
}

int getElement(struct List *list, int index)
{
	int count = 0;
	if(index<0)
	{
		return -1;
	}
	if(!list->first)
	{
		printf("Brak elementow w liscie\n");
	}
	else if(index == 0)
	{
		return 0;
	}
	else
	{
		struct Node *node = list->first;
		for(int i=1; i < index; i++)
		{
			if(node->next == list->first)
			{
				printf("w liscie nie ma pozycji o indexie %d", index);
				return -1;
			}
			node = node->next;
			count++;
		}
		return count;
	}
}

void popIndex(struct List *list, int index)
{
	if(!list->first)
	{
		printf("Brak elementow w liscie\n");
	}
	else
	{	
		struct Node *node = list->first;
		struct Node *prevNode = NULL;
		for(int i = 0; i < index; i++)
		{
			if(node->next == list->first)
			{
				printf("w liscie nie ma pozycji o indexie %d", index);
				return;
			}
			prevNode = node;
			node = node->next;
		}
		printf("usuwam element z listy o indexie %d, ", index);
		prevNode->next = node->next;
		node->next->prev = prevNode;
		free(node);
	}
}

// do listy1 doklejamy liste2
void merge(struct List *list1, struct List *list2)
{

	if(!list1->first || !list2->first)
	{
		printf("jedna z podanych list jest pusta \n");
	}
	else
	{
		struct Node *node1 = list1->first->next;
		struct Node *node2 = list2->first->prev;
		list1->first->next = list2->first;
		list2->first->prev = list1->first;
		node1->prev = node2;
		node2->next = node1;
		free(list2);	
	}

}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	struct List *list1 = createList();
	struct List *list2 = createList();
	struct List *list3 = createList();
	for(int i = 0; i < n; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		struct Node *node1 = createNode(tmp);
		//printf("Dodaje element %d do listy 1\n", tmp);
		addToFirst(list1, node1);
	}
	
	int index1, index2, index3;
	scanf("%d%d%d", &index1, &index2, &index3);
	int ans1, ans2, ans3;
	ans1 = getElement(list1, index1);
	ans2 = getElement(list1, index2);
	ans3 = getElement(list1, index3);
	printf("\nliczba iteracji potrzeba do dostania sie do indexu %d wynosi: %d\n\n", index1 ,ans1);
	printf("liczba iteracji potrzeba do dostania sie do indexu %d wynosi: %d\n\n", index2 ,ans2);
	printf("liczba iteracji potrzeba do dostania sie do indexu %d wynosi: %d\n\n", index3 ,ans3);
	
	srand(time(NULL));
	int avg = 0;
	for(int i = 0; i < 100; i++)
	{
		int p = rand() % (1000);
		avg += getElement(list1, p);
	}
	avg/=100;
	printf("\nsredni czas dostepu do losowego elementu: %d\n", avg);
	
	for(int i = 0; i < 5; i++)
	{
		struct Node *node1 = createNode(i);
		struct Node *node2 = createNode(100 - i);
		addToFirst(list2, node1);
		addToFirst(list3, node2);
	}
	printf("\nlista 2\n");
	printList(list2);
	printf("\nLista 3\n");
	printList(list3);
	printf("Lista 2 merge Lista 3\n");
	merge(list2, list3);
	printList(list2);
	popIndex(list2, 1);
	printList(list2);
	
	return 0;
}










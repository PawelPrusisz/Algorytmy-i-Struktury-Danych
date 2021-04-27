#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Node{
	struct Node *next;
	int val;
};

struct List{
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

struct List* createList()
{
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void printNode(struct Node *node)
{
	printf("val = %d\n", node->val);
}

void addToLast(struct List *list, struct Node *node)
{
	if(!list->first)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		struct Node *tmpNode = list->last;
		tmpNode->next = node;
		list->last = node;
	}
}

void addToFirst(struct List *list, struct Node *node)
{
	if(!list->first)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		struct Node *tmpNode = list->first;
		list->first = node;
		list->first->next = tmpNode;
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
		while(curNode)
		{
			printNode(curNode);
			curNode = curNode->next;
		}
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
	else
	{
		struct Node *node = list->first;
		for(int i=0; i < index; i++)
		{
			if(!node->next)
			{
				//printf("w liscie nie ma pozycji o indexie %d", index);
				return -1;
			}
			node = node->next;
			count++;
		}
		//printf("znaleziono element o indexie %d, ", index);
		//printNode(node);
		return count;
	}
}

void popFirst(struct List *list)
{
	if(!list->first)
	{
		printf("Brak elementow w liscie\n");
	}
	else
	{
		printf("usuwam element z listy, ");
		printNode(list->first);
		struct Node* node = list->first;
		list->first = node->next;
		free(node);
	}
}

void popIndex(struct List *list, int index)
{
	if(!list->first)
	{
		printf("Brak elementow w liscie\n");
	}
	else if(index == 0)
	{
		popFirst(list);
		return;
	}
	else
	{	
		struct Node *node = list->first;
		struct Node *prevNode = NULL;
		for(int i = 0; i < index; i++)
		{
			if(!node->next)
			{
				printf("w liscie nie ma pozycji o indexie %d", index);
				return;
			}
			prevNode = node;
			node = node->next;
		}
		printf("usuwam element z listy o indexie %d, ", index);
		prevNode->next = node->next;
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
		list1->last->next = list2->first;
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
		//struct Node *node2 = createNode(100 - tmp);
		//printf("Dodaje element %d na poczatek listy 1\n", tmp);
		addToFirst(list1, node1);
		//printf("Dodaje element %d na koniec listy 2\n", 100-tmp);
		//addToLast(list2, node2);
	}
	//printf("podaj indeksy 3 elementow do zbadania\n\n");
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
	
	for(int i = 0; i < 10; i++)
	{
		struct Node *node1 = createNode(i);
		struct Node *node2 = createNode(100-i);
		addToFirst(list2, node1);
		addToFirst(list3, node2);
	}
	printf("\nlista 1\n");
	printList(list2);
	printf("lista 2\n");
	printList(list3);
	
	printf("lista 1 merge lista 2\n");
	merge(list2,list3);
	printList(list2);
	/*
	for(int i = 0; i < 10; i++)
	{
		struct Node *node1 = createNode(-i);
		printf("Dodaje element %d na koniec listy 2\n", -i);
		addToLast(list2, node1);
	}
	*/
	/*
	printf("\nlista1\n");
	printList(list1);
	
	printf("lista2\n");
	printList(list2);
	
	printf("lista1 merge lista2\n");
	merge(list1,list2);
	printList(list1);
	
	printf("pop index\n");
	popIndex(list1, 6);
	printList(list1);
	
	printf("pop first\n");
	popFirst(list1);
	printList(list1);
	*/
	return 0;
}










#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// returns random from [a, b]
int rnd(int a, int b)
{
	return a + rand()%(b-a+1);
}
int main()
{
	srand(time(NULL));
	int a = -10000;
	int b = 100000;
	int n;
	scanf("%d", &n);
	printf("%d\n", n);
	for(int i = n; i>0;i--)
	{
		printf("%d ", rnd(a,b));
	}
	printf("\n");
}

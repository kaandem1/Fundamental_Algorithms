#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 10001


/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: DISJOINT SET FUNCTIONS	
 * Implemented FUNCTIONS
 * FIND AND UNION HAVE A COMPLEXITY OF O(LOG N) BUT MAKE SET IS  O(1)
 *
 *
 */


typedef struct node {
	int rank;
	int val;
	struct node* parent;
}node_t;

node_t a[SIZE] = { 0 };

void make_set(int x)
{
	a[x].parent = &a[x];
	a[x].val = x;
	a[x].rank = 0;
}

void link(int x, int y)
{
	if (a[x].rank > a[y].rank)
	{
		a[y].parent = &a[x];
	}
	else
	{
		a[x].parent = &a[y];
		if (a[x].rank == a[y].rank)
		{
			a[y].rank = +1;
		}
	}
}

node_t* find_set(int x)
{
	if (a[x].parent != &a[x])
	{
		a[x].parent = find_set(a[x].parent->val);
	}
	return a[x].parent;
}

void Union(int x, int y)
{
	node_t* px = find_set(x);
	node_t* py = find_set(y);
	link(px->val, py->val);
}


void demo()
{
	for (int i = 0; i <= 10; i++)
	{
		make_set(i);
	}
	for (int i = 1; i <= 5; i++){
		Union(i, 2*i);
		for (int i = 0; i <= 10; i++)
			printf("%d: { paret: %d, rank: %d }, ", i, a[i].parent->val, a[i].rank);
		printf("\n");

	}
	for (int i = 0; i < 5; i++)
	{
		printf("Value: %d\nRepresentative of the set: %d\n", i, find_set(i)->val);
	}
}




int main()
{
	demo();

}
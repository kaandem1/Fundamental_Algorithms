/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: Demo for the insert and search operations using the required data structure
 *
 * 
 * Finally, regarding the question of space, we work with constant space with both algorithms without additional no more than some variables.
 *
 *
 */


#include <string.h>
#include <stdio.h>
#define SIZE 10007
#define C1 7347 //positive aux constants
#define C2 3697

typedef struct { int id; char name[30]; } Entry;

Entry* hash[SIZE] = { 0 }; // array of pointers initialized with null

int h2(int id) //random hash function 
{
	id = (id * 265) * 17;
	id = id + 97548556;
	id = id / 13; 
	return id;
}


int h(int id, int i) // hash function for quadratic probing 
{
	return (h2(id) + C1 * i + C2 * i * i) % SIZE;
}

int search(Entry* hash[], Entry* e)//search function to find element in the table
{
	int i = 0;
	int j = h(e->id, i);

	while (hash[j] != NULL && i < SIZE) //while in the table
	{
		if (hash[j]->id == e->id) //if the func finds the required id return the index in the table
		{
			return j;
		}
		i++; //else go to the next index
		j = h(e->id, i);
	}

	return -1;
}

int insert(Entry* hash[], Entry* e)
{
	int i = 0;
	int j;
	do
	{
		j = h(e->id, i); 
		if (hash[j] == NULL)//if the func finds an empty space at the j'th place in the hash table
		{
			hash[j] = e; //insert the entry there
			return j;
		}
		else i++;//else go to the next index
	} while (i < SIZE);

	return -1;
}

void demo()
{
	Entry e[] =
	{
		{ 222, "apple" }, {1555,"pear"}, {1243,"watermelon"}, {99,"kaan"} //entries that will be put into the hashtable
	};

	int s = sizeof(e) / sizeof(e[0]); 
	for (int i = 0; i < s; i++)
	{
		insert(hash, &e[i]); // inserting into the hashtable the addresses of entries
	}

	printf("HashTable:\n");
	for (int i = 0; i < SIZE; i++)
	{
		if(hash[i] != NULL)
		{
			printf("index: %d, id: %d, name: %s\n", i, hash[i]->id, hash[i]->name);
		}
	}

	Entry e2 ={ 222, "apple" }; //entry we are looking for

	int j = search(hash, &e2); 
	
	printf("Entry { id: %d, name: %s } was ", e2.id, e2.name);
	if (j != -1)
		printf("found an index = %d", j);
	else
		printf("not Found.");

}



int main()
{

	demo();
}


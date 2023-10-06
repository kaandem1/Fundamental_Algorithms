#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHILD_SIZE 50


/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: Multi-way Trees. Transformations between different representations
 * Implemented R1 , R2 and T1.
 * T1 is linear becase the funcion is called once for each node, and in the for loop if it encounters a node previously created node it skips the function call
 * Finally, regarding the question of space, we work with constant space with both algorithms without additional no more than some variables.
 *
 *
 */





typedef struct mwnode  //defining node
{
    int key;
    mwnode* a[CHILD_SIZE];
    int children;
} mwnode_t;

mwnode_t* create_node(int key) // a function to create nodes
{
    mwnode_t* new_node = (mwnode_t*)calloc(1, sizeof(mwnode_t)); //reserve a chunk of memory the size of mwnode_t for the new node

    if (!new_node) {
        return NULL;
    }

    new_node->key = key;
    return new_node;
}

void create_t1node(int arr[], mwnode_t* a[], int i)
{
    a[i] = create_node(i+1);//array indexes start from 0 instead of 1
    if (arr[i] == -1) //if node is the root do nothing
        return;

    if (a[arr[i]-1] == NULL)
        create_t1node(arr, a, arr[i]-1); //if the node has no parent, create one

    mwnode_t* parent = a[arr[i] - 1];

    parent->a[parent->children] = a[i]; //add to the ith node, to its parent's children array
    parent->children++; //number of children increase
}

mwnode_t* t1(int arr[], int n) 
{
    mwnode_t* a[100];
        
    int root;

    for (int i = 0; i < n; i++)
    {
        a[i] = NULL; // initialize the children array by making all null
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == -1)
            root = i;

        if (a[i] == NULL) //if the ith position is null
        {
            create_t1node(arr, a, i); // create the node
        }
    }

    return a[root];
}


void pp_one(int arr[], int n, int p, int level) //n^2 becas for each node, we loop again to search such that its parent == p
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == p)
        {
            for (int j = 0; j < level; j++)
            {
                printf("   ");
            }
            printf("%d\n", i + 1);
            pp_one(arr, n, i + 1, level + 1);
        }

    }
}

void pp_two(mwnode_t* root, int level)
{
    for (int j = 0; j < level; j++)
    {
        printf("   ");
    }
    printf("%d\n", root->key);
    level++;
    for (int i = 0; i < root->children; i++)
        pp_two(root->a[i], level);
}

int main()
{
    int a[] = { 2, 7, 5, 2, 7, 7,-1, 5, 2 }, n = sizeof(a) / sizeof(a[0]);
    pp_one(a, n, -1, 0);
    mwnode_t* r2 = t1(a, n);
    pp_two(r2, 0);
    return 0;
}

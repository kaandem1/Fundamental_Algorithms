#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZ 5
//#define MIN_SIZ 1
//#include "Profiler.h"

/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: required to implement correctly and efficiently an O(nlogk) method for merging k
                            sorted sequences, where n is the total number of elements
 *
 * Implemented everything except the average case with the profiler.
 * My implementation creates nodes and adds them in a linked list using the create_list function and does this k times in a for loop.
 * It then put the smalles values from k linked lists and puts them in a min heap and takes out the root as long as nodes exist and puts them in the sorted output linked list.
 * The complexity we get is O(nlogk): Building the heap with bottom up takes O(n), heapifying (Ologk) with n nodes would be O(nlogk) would give O(n)+O(nlogk) complexity
 * Since O(nlogk) is bigger, that's the complexity we work with. Or by factoring n, we get n(logk+1) =nlogk.
 */
 //Profiler profiler("Average Case");

 //const char* comp_ = "Comparisons", * assign_ = "Assignments", * tot_ = "Total";

typedef struct node  //defining node
{
    int key;
    struct node* next;

} node_t;

typedef struct pair  //defining a pair of index and key to use in heap
{
    int index;
    int key;

} pair_t;

void DOOM_THE_LIST(node_t* node) //a function to clean up the memory we reserve for the nodes
{
    if (node == NULL)
        return;
    DOOM_THE_LIST(node->next);
    free(node);
}

unsigned long int rand_num(unsigned long int mi, unsigned long int ma) //  a random number generator for the keys in nodes
{
    unsigned long int i = rand() % (ma - mi) + mi;
    return i;
}

void min_heapify(pair_t a[], int n, int i)  // at every insertion, min heapify checks the parent with children, take one that is smallest and swap if necessary
{


    int l = 2 * i + 1;  // indices of children in the array
    int r = 2 * i + 2;
    int smallest;
    if (l < n && a[l].key < a[i].key)  // if left child smaller , and we do a comparison with a[i].key because we are only concerned with the key out of the pair
    {
        //comp_l.count();
        smallest = l;
    }
    else {
        if (l < n) {
            //comp_l.count();
        }
        smallest = i;
    }

    if (r < n && a[r].key < a[smallest].key)  // if right child smaller, and we do a comparison with a[i].key because we are only concerned with the key out of the pair
    {
        // comp_h.count();
        smallest = r;
    }
    if (r < n) {
        // comp_h.count();
    }

    if (smallest != i) {
        // assign_h.count(3);
        pair_t temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        min_heapify(a, n, smallest);  // recursive call to see if the node needs to go down further.
    }
}

void btm_up(pair_t a[], int n)  // n=heap size
{
    // since we don't do any comparisons or assignments involving the array AND we call the max_heapify function, we need to count them in the max_heapify function
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        min_heapify(a, n, i);
}

node_t* create_node(int key) // a function to create nodes 
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t)); //reserve a chunk of memory the size of node_t for the new node

    if (!new_node) {
        return NULL;
    }

    new_node->key = key; //give the new node a key and make it the random number we generated before
    new_node->next = NULL; //newly created node has no other node after it so declare node next as null
    return new_node;
}

node_t* list_create(int n)  // a function to create a linked list of nodes
{
    node_t* head = create_node(rand_num(1, 100)); // the new node, which is the first and the head of the list, gets a key which is randomly generated between 1 and 100
    node_t* current = head; // define the current node as head since its the only one
    for (int i = 1; i < n; i++) {
        current->next = create_node(rand_num(1, 100) + current->key); // in  a loop, add as many nodes as n is, give them a random key and add the previous one to the key so list is generated sorted
        current = current->next;// go to the next node
    }

    return head;
}

void demo(int k, int n) // k linked lists of n elements
{
    k = MAX_SIZ; //vs doesnt let me use uninitialised k, so give k = 5 with max size
    node_t* a[MAX_SIZ];

    int list_size = n / k; // each list has at most n/k elements
    int mod = n % k; //check if n divisible by k


    for (int i = 0; i < k; i++) {//generate k linked lists
        a[i] = list_create(list_size+(mod>0)); //
        mod--;
        for (node_t* j = a[i]; j; j = j->next)
            printf("%d ", j->key);//print out the lists, keys of the nodes
        printf("\n");
    }

    pair_t heap[MAX_SIZ]; // define a heap of pairs
    node_t* b[MAX_SIZ]; // the array that keeps the indexes of the linked lists
    //keep track of indexes to know from where to add the next value or if that list is empty, shrink the heap
    node_t* out_head; //head of the output linked list
    node_t* out_current; //current node of the output linked list

    int heap_size = k; //a heap of k elements
    for (int i = 0; i < k; i++) {
        heap[i] = { i, a[i]->key };
        b[i] = a[i]->next;
    }
    btm_up(heap, MAX_SIZ);

    out_head = create_node(heap[0].key); //first node of the output is the minimum element of the heap, the root
    out_current = out_head; // no other elements so current = head
    while (heap_size > 1) {//while heap not empty
        if (b[heap[0].index]) { //while index not null
            heap[0].key = b[heap[0].index]->key;
            b[heap[0].index] = b[heap[0].index]->next;
        }
        else {
            heap[0] = heap[heap_size - 1];//decrease the size of the heap if one of the lists has no more elements
            heap_size--;
        }
        min_heapify(heap, heap_size, 0); //min heaoify as long as heap not empty
        out_current->next = create_node(heap[0].key);
        out_current = out_current->next; //create and add new nodes with keys from the heap
    }

    for (node_t* i = out_head; i; i = i->next) {
        printf("%d ", i->key); //printing the output array
    }

    DOOM_THE_LIST(out_head); //clean up the memory
    for (int i = 0; i < k; i++)
        DOOM_THE_LIST(a[i]);
}






int main() {
    srand(time(NULL)); // give a seed with srand to the rand funct
    //profile();
    demo(MAX_SIZ, 100);
    return 0;
}

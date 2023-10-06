#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#define MAX_SIZ 10001

/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: Compare and Analyse Direct sorting methods
 *
 * For average case: Top Down performs significantly worse than bottom up because the total number of comparisons and assignments is almost double that of bottom up.
 * In the worst case: Top down has a complexity of O(nlogn) meanwhile bottom up has a complexity of O(n). Top down still performs worse than bottom up
 * For bottom up, we start from leaves and go up. We already have half of the nodes and we keep adding the other half and swap if necessary. We keep adding one by one and keep going up until the root. the complexity is O(n).
 * However in the case of top down; we start from the root, we go the depth of the tree for each node (which is o log n) and u do this n times n nb of nodes. = O(nlogn).
 * It is important to note that even though the lines on the graphs may look similar, depending on the way we implement the algorithms the number of assignments/comparisons may vary.
 * Finally, regarding the question of space, we work with constant space with both algorithms without additional no more than some variables.
 *
 *
 */

Profiler profiler("Average Case");

const char* btm_comp = "Bottom Up Comparisons", * btm_assign = "Bottom Up Assignments", * btm_tot = "Bottom Up Total";
const char* top_comp = "Top Down Comparisons", * top_assign = "Top Down Assignments", * top_tot = "Top Down Total";



void max_heapify(int a[], int n, int i) //at every insertion, max heapify checks the parent with children, take one that is largest and swap if necessary
{
    Operation comp_btm = profiler.createOperation(btm_comp, n);
    Operation assign_btm = profiler.createOperation(btm_assign, n);
    int l = 2 * i + 1; //indices of children in the array
    int r = 2 * i + 2;
    int temp, largest;
    if (l < n && a[l]> a[i]) //if left child bigger
    {
        comp_btm.count();
        largest = l;
    }
    else
        largest = i;
    
    if (r < n && a[r]> a[largest]) //if right child bigger
    {
        comp_btm.count();
        largest = r;
    }

    if (largest != i)
    {
        assign_btm.count(3);
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, n, largest); //recursive call to see if the node needs to go down further.
    }
}

void btm_up(int a[], int n)//n=heap size
{
    //since we don't do any comparisons or assignments involving the array AND we call the max_heapify function, we need to count them in the max_heapify function
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        max_heapify(a, n, i);
}

void top_down(int a[], int n)
{
    Operation comp_top = profiler.createOperation(top_comp, n);// create operation for the comparisons of top down heap building
    Operation assign_top = profiler.createOperation(top_assign, n); // for assignments
    for (int i = 1; i < n; i++)
    {
        int parent = (i - 1) / 2;
        int j = i;
        while (j != 0 && a[j] > a[parent])
        {
            comp_top.count();
            assign_top.count(3);
            int temp;
            temp = a[j];
            a[j] = a[parent];
            a[parent] = temp; // swapped child with parent while child >

            //updating indices
            j = parent;
            parent = (j - 1) / 2;


        }
        if (j!=0)   //when its not entering while, count operation even though the second condition wasn't true. (instead of having 2 ifs).
        { 
            comp_top.count();

        }

    }

}

void heapsort(int a[], int n)
{
    int i, j;
    int temp;
    btm_up(a, n); // we build the heap using the bottom up algorithm
    for (i = n - 1; i >= 1; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        max_heapify(a, i, 0);
    }
}






void demo()
{
    int i;
    int a[] = { 2, 9, 7, 6, 5, 8, 10, 3, 6, 9 }, n = sizeof(a) / sizeof(a[0]);
    printf("Unsorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    int b[MAX_SIZ];
    for (i = 0; i < n; i++)
        b[i] = a[i];
    printf("\nBottom up demo: ");
    btm_up(a, n);

    for (i = 0; i <= n - 1; i++)
        printf("%d ", a[i]);
    printf("\n");

    int c[MAX_SIZ];
    for (int i = 0; i < n; i++)
        c[i] = b[i];
    printf("\nTop down demo: ");
    top_down(b, n);

    for (i = 0; i <= n - 1; i++)
        printf("%d ", b[i]);
    printf("\n");

    printf("\nSorted Array: ");
    heapsort(c, n);
    for (int i = 0; i < n; i++)

        printf("%d ", c[i]);
}

void profile()
{
    const int MAX_SIZE = 10001, INC = 100, ITERATIONS = 5;

    int a1[MAX_SIZE];//bottom up
    int a2[MAX_SIZE];//top down

    //average case
    for (int i = 0; i < ITERATIONS; i++) //we will have arrays of length 100 to 10000 with random numbers (after each sort size=size+100) sorted with b sort , have the whole process 5 times.
        for (int n = 100; n < MAX_SIZE; n += INC)
        {
            printf("%d\n", n);
            FillRandomArray(a1, n, 0, 1000000);//values in array are picked randomly in a set of a million numbers
            CopyArray(a2, a1, n);
            btm_up(a1, n);
            top_down(a2, n);
        }
    profiler.divideValues(btm_comp, ITERATIONS);
    profiler.divideValues(btm_assign, ITERATIONS);//we divide the number of assingments and comparisons by the number of iterations to get the average value
    profiler.addSeries(btm_tot, btm_comp, btm_assign); //btm_tot gets the value of the sum of assignments and comparisons

    profiler.divideValues(top_comp, ITERATIONS);
    profiler.divideValues(top_assign, ITERATIONS);//we divide the number of assingments and comparisons by the number of iterations to get the average value
    profiler.addSeries(top_tot, top_comp, top_assign);//top_tot gets the value of the sum of assignments and comparisons

    profiler.createGroup("Average Comp", btm_comp, top_comp); //merging lines in the same chart
    profiler.createGroup("Average Ass", btm_assign, top_assign);
    profiler.createGroup("Average Total", btm_tot, top_tot);

    profiler.reset("Worst Case");

    for (int n = 100; n < MAX_SIZE; n += INC)
    {
        printf("%d\n", n);
        FillRandomArray(a1, n, 0, 1000000, false, ASCENDING);
        CopyArray(a2, a1, n);//generating a2 out of a1
        btm_up(a1, n);
        top_down(a2, n);
    }
    profiler.addSeries(btm_tot, btm_comp, btm_assign);
    profiler.addSeries(top_tot, top_comp, top_assign);

    profiler.createGroup("Worst Comp", btm_comp, top_comp); //merging lines in the same chart
    profiler.createGroup("Worst Ass", btm_assign, top_assign);
    profiler.createGroup("Worst Total", btm_tot, top_tot);

    profiler.showReport();
}






int main()
{
    //profile();
    demo();
    return 0;
}
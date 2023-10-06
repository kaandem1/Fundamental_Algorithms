#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZ 10001
#include "Profiler.h"

/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: Compare and Analyse Quicksort and Heapsort
 *
 * Quicksort depends on the implementation. But generally O(n^logn) in best and average, and O(n^2) in worst.
 * For Heapsort, it's complexity is O (n log n) all around .
 * We can't compare Quickort and Heapsort in best and worst cases because their cases are not the same.
 * It is important to note that even though the lines on the graphs may look similar, depending on the way we implement the algorithms the number of assignments/comparisons may vary.
 * Finally, regarding the question of space, we work with constant space with both algorithms without additional no more than some variables.
 *
 *
 */

Profiler profiler("Average Case");

const char* q_comp = "Quicksort Comparisons", * q_assign = "Quicksort Assignments", * q_tot = "Quicksort Total";
const char* h_comp = "Heapsort Comparisons", * h_assign = "Heapsort Assignments", * h_tot = "Heapsort Total";

int partition(int a[], int m, int e, Operation comp_q, Operation assign_q)
{
    int j;
    int temp1;
    assign_q.count(1);
    int k = a[e];
    int i = m - 1;
    for (j = m; j <= e - 1; j++)
    {
        if (a[j] <= k)
        {
            comp_q.count();
            i++;
            assign_q.count(3);
            temp1 = a[i];
            a[i] = a[j];
            a[j] = temp1;
        }

    }
    if (i + 1 != e)
    {
        assign_q.count(3);
        temp1 = a[i + 1];
        a[i + 1] = a[e];
        a[e] = temp1;
    }

    return i + 1;
}

int rand_part(int a[], int m, int e, Operation comp_q, Operation assign_q)
{
    srand(time(NULL)); //simplest random gen
    int i = rand() % (e - m) + m; //give a seed with srand to the rand funct. and the rand function generates random number between m and e 
    int temp;
    assign_q.count(3);
    temp = a[i];
    a[i] = a[e];
    a[e] = temp; //swapping random number with the last number
    return partition(a, m, e, comp_q, assign_q); //returning partition with the random element as last
}

int best_part(int a[], int m, int e, Operation comp_q, Operation assign_q)
{
    int j;
    int temp1;
    assign_q.count(3);
    int k = a[(m + e) / 2];
    a[(m + e) / 2] = a[e];
    a[e] = k;
    
    int i = m - 1;
    for (j = m; j <= e - 1; j++)
    {
        if (a[j] <= k)
        {
            comp_q.count();
            i++;
            assign_q.count(3);
            temp1 = a[i];
            a[i] = a[j];
            a[j] = temp1;
        }

    }
    if (i + 1 != e)
    {
        assign_q.count(3);
        temp1 = a[i + 1];
        a[i + 1] = a[e];
        a[e] = temp1;
    }
    return i + 1;
}



void av_quicksort(int a[], int m, int e, Operation comp_q, Operation assign_q)//average case for quicksort using average partitioning to have a random pivot in the array
{
    int q;
    if (m < e)
    {
        q = rand_part(a, m, e, comp_q, assign_q);
        av_quicksort(a, m, q - 1, comp_q, assign_q);
        av_quicksort(a, q + 1, e, comp_q, assign_q);//was q+1

    }
}

void best_quicksort(int a[], int m, int e, Operation comp_q, Operation assign_q) //sorted ascending and pick middle as pivot
{
    int q;
    if (m < e)
    {
        q = best_part(a, m, e, comp_q, assign_q);
        best_quicksort(a, m, q -1 , comp_q, assign_q);
        best_quicksort(a, q+1, e, comp_q, assign_q);//was q+1

    }
}

void worst_quicksort(int a[], int m, int e, Operation comp_q, Operation assign_q) //worst case descending but always pick smallest element
{
    int q;
    if (m < e)
    {
        q = partition(a, m, e, comp_q, assign_q);
        worst_quicksort(a, m, q - 1, comp_q, assign_q);
        worst_quicksort(a, q + 1, e, comp_q, assign_q);//was q+1

    }
}

void max_heapify(int a[], int n, int i, Operation comp_h, Operation assign_h) //at every insertion, max heapify checks the parent with children, take one that is largest and swap if necessary
{
    int l = 2 * i + 1; //indices of children in the array
    int r = 2 * i + 2;
    int temp, largest;
    if (l < n && a[l]> a[i]) //if left child bigger
    {
        comp_h.count();
        largest = l;
    }
    else
    {
        if (l < n)
        {
            comp_h.count();
        }
        largest = i;
    }

    if (r < n && a[r]> a[largest]) //if right child bigger
    {
        comp_h.count();
        largest = r;
    }
    if (r < n)
    {
        comp_h.count();
    }

    if (largest != i)
    {
        assign_h.count(3);
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, n, largest, comp_h, assign_h); //recursive call to see if the node needs to go down further.
    }
}



void btm_up(int a[], int n, Operation comp_h, Operation assign_h)//n=heap size
{
    //since we don't do any comparisons or assignments involving the array AND we call the max_heapify function, we need to count them in the max_heapify function
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        max_heapify(a, n, i, comp_h, assign_h);
}


void heapsort(int a[], int n, Operation comp_h, Operation assign_h)
{
    int i, j;
    int temp;
    btm_up(a, n, comp_h, assign_h); // we build the heap using the bottom up algorithm
    for (i = n - 1; i >= 1; i--)
    {
        assign_h.count(3);
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        max_heapify(a, i, 0, comp_h, assign_h);
    }
}



void demo()
{

    int i;
    int a[] = { 2, 9, 7, 6, 5, 8, 10, 3, 6, 9 }, n = sizeof(a) / sizeof(a[0]);
    Operation comp_h = profiler.createOperation(h_comp, n);
    Operation assign_h = profiler.createOperation(h_assign, n);
    Operation comp_q = profiler.createOperation(q_comp, n);
    Operation assign_q = profiler.createOperation(q_assign, n);
    printf("Unsorted Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    int b[MAX_SIZ];
    for (i = 0; i < n; i++)
        b[i] = a[i];

    printf("\nWorst Case Quicksort demo: ");
    worst_quicksort(a, 0, n - 1, comp_q, assign_q);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    printf("\n Best Case Quicksort demo: ");
    best_quicksort(a, 0, n - 1, comp_q, assign_q);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    printf("\nAverage Case Quicksort demo: ");
    av_quicksort(a, 0, n - 1, comp_q, assign_q);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    printf("\nHeapsort Demo: ");
    heapsort(b, n, comp_h, assign_h);
    for (int i = 0; i < n; i++)

        printf("%d ", b[i]);
}

void profile()
{
    const int MAX_SIZE = 10001, INC = 100, ITERATIONS = 5;

    int a1[MAX_SIZE];//array for quicksort
    int a2[MAX_SIZE];//array for heapsort

    //average case for quicksort and heapsort
    for (int i = 0; i < ITERATIONS; i++) //we will have arrays of length 100 to 10000 with random numbers (after each sort size=size+100) sorted with b sort , have the whole process 5 times.
        for (int n = 100; n < MAX_SIZE; n += INC)
        {
            Operation comp_h = profiler.createOperation(h_comp, n);
            Operation assign_h = profiler.createOperation(h_assign, n);
            Operation comp_q = profiler.createOperation(q_comp, n);
            Operation assign_q = profiler.createOperation(q_assign, n);
            printf("%d\n", n);
            FillRandomArray(a1, n, 0, 1000000);//values in array are picked randomly in a set of a million numbers
            CopyArray(a2, a1, n);
            av_quicksort(a1, 0, n - 1, comp_q, assign_q);
            heapsort(a2, n, comp_h, assign_h);
        }
    profiler.divideValues(q_comp, ITERATIONS);
    profiler.divideValues(q_assign, ITERATIONS);//we divide the number of assingments and comparisons by the number of iterations to get the average value
    profiler.addSeries(q_tot, q_comp, q_assign); //b_tot gets the value of the sum of assignments and comparisons

    profiler.divideValues(h_comp, ITERATIONS);
    profiler.divideValues(h_assign, ITERATIONS);//we divide the number of assingments and comparisons by the number of iterations to get the average value
    profiler.addSeries(h_tot, h_comp, h_assign);

    profiler.createGroup("Average Comp", q_comp, h_comp); //merging lines in the same graph
    profiler.createGroup("Average Ass", q_assign, h_assign);
    profiler.createGroup("Average Total", q_tot, h_tot);

    profiler.reset("Best Case");
    //best case for quicksort
    for (int n = 100; n < MAX_SIZE; n += INC) //same process but we won't repeat it 5 times and in this case the random values in arr are already sorted ascendingly
    {
        Operation comp_q = profiler.createOperation(q_comp, n);
        Operation assign_q = profiler.createOperation(q_assign, n);
        printf("%d\n", n);
        FillRandomArray(a1, n, 0, 1000000, false, ASCENDING);
        best_quicksort(a1, 0, n - 1, comp_q, assign_q);
    }
    profiler.addSeries(q_tot, q_comp, q_assign);

    profiler.reset("Worst Case");
    //worst case for quicksort
    for (int n = 100; n < MAX_SIZE; n += INC)
    {
        Operation comp_q = profiler.createOperation(q_comp, n);
        Operation assign_q = profiler.createOperation(q_assign, n);

        printf("%d\n", n);
        FillRandomArray(a1, n, 0, 1000000, false, DESCENDING);
        worst_quicksort(a1, 0, n - 1, comp_q, assign_q);
    }
    profiler.addSeries(q_tot, q_comp, q_assign);

    profiler.showReport();



}


int main()
{
    profile();
    //demo();
    return 0;
}
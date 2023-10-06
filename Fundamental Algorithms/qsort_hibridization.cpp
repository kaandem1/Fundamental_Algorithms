
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10001
#define S_SIZE 100
//#include "Profiler.h"
/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: ITERATIVE VS RECURSIVE TRAVERSALS
 * Implemented traversals
 * ALL TRAVERSALS HAVE A COMPLEXITY OF O(N) BECAUSE WE GO ONCE THROUGH EACH NODE
 * Finally, regarding the question of space, we work with ADDITIONAL SPACE O(HEIGHT) WHERE HEIGHT IS BETWEEN LOG N AND N.
 *
 *
 */

struct node_t
{
    int size;
    int height;
    int val;
    node_t* left, * right;
};



node_t* preStack[S_SIZE];
int preTop = -1;

node_t* postStack[S_SIZE];
int postTop = -1;

node_t* inStack[S_SIZE];
int inTop = -1;



int preisempty()
{

    if (preTop == -1)
        return 1;
    else
        return 0;
}

int postisempty()
{

    if (postTop == -1)
        return 1;
    else
        return 0;
}

int inisempty()
{

    if (inTop == -1)
        return 1;
    else
        return 0;
}

int preisfull()
{
    if (preTop == S_SIZE)
        return 1;
    else
        return 0;
}

int postisfull()
{
    if (postTop == S_SIZE)
        return 1;
    else
        return 0;
}

int inisfull()
{
    if (inTop == S_SIZE)
        return 1;
    else
        return 0;
}


void prepush(node_t* root)
{

    if (!preisfull()) {
        preTop = preTop + 1;
        preStack[preTop] = root;
    }
    else {
        printf("Could not insert data\n");
    }
}

node_t* prepop()
{

    if (!preisempty()) {
        node_t* ret =preStack[preTop];
        preTop = preTop - 1;
        return ret;
    }
    else {
        printf("Could not retrieve data\n");
    }
}

void postpush(node_t* root)
{

    if (!postisfull())
    {
        postTop = postTop + 1;
        postStack[postTop] = root;
    }
    else
    {
        printf("Could not insert data\n");
    }
}

node_t* prepeek() {
    return preStack[preTop];
}

node_t* postpeek() {
    return postStack[postTop];
}

node_t* inpeek() {
    return inStack[inTop];
}

node_t* postpop()
{
    if (!postisempty())
    {
        node_t* ret = postStack[postTop];
        postTop = postTop - 1;
        return ret;
    }
    else
    {
        printf("Could not retrieve data\n");
    }
}

void inpush(node_t* root)
{

    if (!inisfull())
    {
        inTop = inTop + 1;
        inStack[inTop] = root;
    }
    else
    {
        printf("Could not insert data\n");
    }
}


node_t* inpop()
{
    if (!inisempty())
    {

        node_t* ret = inStack[inTop];
        inTop = inTop - 1;
        return ret;
    }
    else
    {
        printf("Could not retrieve data\n");
    }
}




node_t* createnode(int nval)
{
    node_t* t = (node_t*)calloc(1, sizeof(node_t));
    if (t == NULL)
        return NULL;

    t->val = nval;
    t->left = NULL;
    t->right = NULL;
    t->height = 1;
    return t;
}

node_t* build_tree(int a[], int left, int right) //build a balanced tree
{
    if (left > right)
        return NULL;
    int mid = (left + right) / 2;
    node_t* node = createnode(a[mid]);
    node->left = build_tree(a, left, mid - 1);
    node->right = build_tree(a, mid + 1, right);
    node->size = 1;
    if (node->left != NULL)
        node->size += node->left->size;
    if (node->right != NULL)
        node->size += node->right->size;
    return node;
}

void preorder(node_t* root)
{
    if (root == NULL)
        return;
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void itPre(node_t* root)
{
    if (root == NULL)
        return;
    prepush(root);
    node_t* current;
    while (!preisempty()) //while we still have nodes to visit
    {
        current = prepop(); // current node top of stack
        printf("%d ", current->val); // print top of stack

        if (current->right != NULL)// push right node to visit later
            prepush(current->right);
  
        if (current->left!= NULL)//then go on left
            prepush(current->left);
    }
}

void inorder(node_t* root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void itIn(node_t* root) {
    node_t* current = root;

    while (current != NULL || !inisempty())  
    {
        while (current != NULL)
        {//go on the left side of the current node
            inpush(current); //push current on stack
            current = current->left;//continue going left
        }
        
        current = inpop(); // reach the end of the left branch
        printf("%d ", current->val);
        current = current->right;//go on the right side
    }
}

void postorder(node_t* root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

void itPost(node_t* root)
{
    if (root == NULL)
        return;
    postpush(root);
    node_t* prev = NULL,*current;
    while (!postisempty())
    {
        current = postpeek();

        if (prev == NULL || prev->left == current || prev->right == current) 
        { // havent reached a leaf
            if (current->left != NULL) // go to the left if possible
                postpush(current->left);
            else if (current->right != NULL) // right if possible
                postpush(current->right);
            else 
            {
                postpop(); //
                printf("%d ", current->val);
            }
        }
        else if (current->left == prev) 
        { // reached a leaf on left of prev
            if (current->right != NULL) // go to the right
                postpush(current->right);
            else 
            {
                postpop();
                printf("%d ", current->val);
            }
        }
        else if (current->right == prev) 
        { // reached a leaf on right of prev
            postpop();
            printf("%d ", current->val);
        }

        prev = current;
    }
}

void pp(node_t* root, int level)
{
    if (root == NULL)
        return;

    for (int j = 0; j < level; j++)
    {
        printf("   ");
    }
    printf("%d\n", root->val);
    level++;

    pp(root->left,level);
    pp(root->right, level);
}

void demo_traversals()
{
    int a[] = { 1,2,3,4,5,6,7,8,9,10,11 }, n = sizeof(a) / sizeof(a[0]); //easier to follow for ascending array
    node_t* root = build_tree(a, 0, n-1);
    pp(root,0);
    printf("Preorder recursive: ");
    preorder(root);
    printf("\nPreorder iterative: ");
    itPre(root);
    printf("\nInorder recursive: ");
    inorder(root);
    printf("\nInorder iterative: ");
    itIn(root);
    printf("\nPostorder recursive: ");
    postorder(root);
    printf("\nPostorder iterative: ");
    itPost(root);
    printf("\n");
}

int main()
{
    demo_traversals();
    return 0;
}

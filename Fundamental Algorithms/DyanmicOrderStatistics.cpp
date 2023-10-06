#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: Dynamic Order Statistics
 * Implemented build, select and delete
 * build tree has a complexity of O(n), however select and delete have a complexity of O(log n)
 * Finally, regarding the question of space, we work with constant space with both algorithms without additional no more than some variables.
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

node_t* createnode(int nval)
{
    node_t* t = (node_t*)calloc(1,sizeof(node_t));
    if (t == NULL)
        return NULL;

    t->val = nval;
    return t;
}

node_t* build_tree(int left, int right) //build a balanced tree
{
    if (left > right)
        return NULL;
    int mid = (left + right) / 2;
    node_t* node = createnode(mid);
    node->left = build_tree(left, mid - 1);
    node->right = build_tree(mid + 1, right); 
    node->size = 1;
    if (node->left!=NULL)
        node->size += node->left->size;
    if (node->right != NULL)
        node->size += node->right->size;
    return node;
}


node_t* os_select(node_t* root, int i) //returns the ith smallest node in the tree
{
    if (root == NULL)
        return NULL;

    if (i <= 0 || root->size < i)
        return NULL;

    int left_size = 0; //if root left is null, left size remains 0
    if (root->left != NULL)
        left_size = root->left->size;
        
    int rank = left_size + 1;
    if (i == rank)
        return root;
    if (i < rank)
        return os_select(root->left, i);
    else
        return os_select(root->right, i - rank);
}

node_t* minimum_r(node_t* node) //return min node from sub tree we are on
{
    if (node == NULL)
        return NULL;
    if (node->left != NULL)
        return minimum_r(node->left);
    else return node;
}
node_t* rotate_right(node_t* node) //function for right rotate for an avl tree
{
    if (node == NULL)
        return NULL;
    if (node->left == NULL)
        return node;

    node_t* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    int hl, hr,sl,sr;
    sl = 0, sr = 0;
    hl = 0, hr = 0;

    if (node->left != NULL)
    {
        hl = node->left->height;
        sl = node->left->size;
    }
    if (node->right != NULL)
    {
        hr = node->right->height;
        sr = node->right->size;
    }
    if (hl > hr)
    {
        node->height = hl + 1;
    }
    else
        node->height = hr + 1;

    node->size = 1 + sl + sr;

    hl = 0, hr = 0;
    sl = 0, sr = 0;

    if (temp->left != NULL)
    {
        hl = temp->left->height;
        sl = temp->left->size;
    }
    if (temp->right != NULL)
    {
        hr = temp->right->height;
        sr = temp->right->size;
    }
    if (hl > hr)
    {
        temp->height = hl + 1;
    }
    else
        temp->height = hr + 1;
    temp->size = 1 + sl + sr;
    return temp;
}

node_t* rotate_left(node_t* node) // function to rotate left for an avl tree
{
    if (node == NULL)
        return NULL;
    if (node->right == NULL)
        return node;

    node_t* temp = node->right;
    node->right = temp->left;
    temp->left = node;


    int hl, hr, sl, sr;
    sl = 0, sr = 0;
    hl = 0, hr = 0;

    if (node->left != NULL)
    {
        hl = node->left->height;
        sl = node->left->size;
    }
    if (node->right != NULL)
    {
        hr = node->right->height;
        sr = node->right->size;
    }
    if (hl > hr)
    {
        node->height = hl + 1;
    }
    else
        node->height = hr + 1;

    node->size = 1 + sl + sr;

    hl = 0, hr = 0;
    sl = 0, sr = 0;

    if (temp->left != NULL)
    {
        hl = temp->left->height;
        sl = temp->left->size;
    }
    if (temp->right != NULL)
    {
        hr = temp->right->height;
        sr = temp->right->size;
    }
    if (hl > hr)
    {
        temp->height = hl + 1;
    }
    else
        temp->height = hr + 1;
    temp->size = 1 + sl + sr;
    return temp;
}
node_t* os_delete(node_t* node, int val)//delete the node with the corresponding value in tree
{
    if (node == NULL)
        return NULL;

    node->size--;
   
    if (val < node->val)
        node->left = os_delete(node->left, val);
    else if (val > node->val)
        node->right = os_delete(node->right, val);
    else
    {
        if (node->left != NULL && node->right != NULL)
        {
            node_t* temp = minimum_r(node->right);
            node->val = temp->val;
            node->right = os_delete(node->right, temp->val);
        }
        else
        {
            node_t* temp = node;
            if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            free(temp);
        }

    }
    if (node == NULL)
        return NULL;

    int hl, hr;
    hl = 0, hr = 0;

    if (node->left != NULL)
        hl = node->left->height;
    if (node->right != NULL)
        hr = node->right->height;
    if (hl > hr)
    {
        node->height = hl + 1;
    }
    else
        node->height = hr + 1;
    int x = hl - hr;

    //right right
    if (x < -1 && val > node->right->val)
        return rotate_left(node);
    //left left
    if (x > 1 && val < node->left->val)
        return rotate_right(node);
    //left right
    if (x > 1 && val > node->left->val)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    //right left
    if (x < -1 && val > node->right->val)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

void pp(node_t* root, int level)
{
    if (root == NULL)
        return;
    for (int j = 0; j < level; j++)
    {
        printf("   ");
    }
    printf("%d (%d)\n", root->val, root->size);
    level++;
    pp(root->right, level);
    pp(root->left,level);
    
}





int main()
{
    node_t* root = build_tree(1, 11);
    pp(root, 0);//pretty print after build tree
    root = os_delete(root, 6);//delete demo
    pp(root, 0);
    node_t* select = os_select(root, 3);
    pp(select, 0);
    return 0;
}
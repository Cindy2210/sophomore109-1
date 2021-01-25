
//fail
/*
Week 8 Question 1
Description

Please finish the two function remove and inorder in template.
Please make sure that tree still be a binary search tree after remove .
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Node
{
    int data, level;
    struct Node *left, *right, *parent;
};

void insert(struct Node **root, struct Node *node)
{
    if(*root == NULL)
    {
        *root = node;
        return;
    }

    struct Node *cur = *root;
    while(1)
    {
        if(cur->data > node->data)///go left
        {
            if( cur->left == NULL)
            {
                cur->left = node;
                node->parent = cur;
                break;
            }
            cur = cur->left;
        }
        else//go right
        {
            if(cur->right == NULL)
            {
                cur->right = node;
                node->parent = cur;
            }
            cur = cur->right;

        }
    }
}

/*
Function removal will remove all the node tree content data n.
The return value of function removal is a integer represent how many node are removed.
*/
struct Node *find_max(struct Node *root)
{
    if(root == NULL)
        return NULL;
    while(root->right != NULL)
        root = root->right;

    return root;
}
struct Node *find_min(struct Node *root)
{
    if(root == NULL)
        return NULL;
    while(root->left != NULL)
        root = root->left;

    return root;
}


int cp(int data1, int data2)
{
    if(data1 > data2)
        return 1;
    else if(data1 < data2)
        return -1;
    else
        return 0;

}

void inorder_counts(struct Node *root, int *counts, int targ)
{
    if(root)
    {
        inorder_counts(root->left, counts, targ);
        if(root->data == targ)
            (*counts)++;
        inorder_counts(root->right, counts, targ);
    }
    return;
}

struct Node *search_targ(struct Node *root, int targ)
{
    if(root == NULL)
        return NULL;
    if( cp(root->data, targ) == 0)//root->data > targ
    {
        return root;
    }
    if( cp(root->data, targ) == 1)//root->data > targ
    {
        return search_targ(root->left, targ);
    }
    if( cp(root->data, targ) == -1)//root->data < targ
    {
        return search_targ(root->right, targ);
    }

}

struct Node *delete_node(struct Node *root, int target)
{
    //no child
    if(root->left == NULL && root->right == NULL)
    {
        free(root);
        return;
    }
    //one child
    ///left child
    else if(root->left != NULL && root->right == NULL)
    {
        struct Node *tmp = root->left;
        root->left = NULL;
        return tmp;
    }
    ///right child
    else if(root->left == NULL && root->right != NULL)
    {
        struct Node *tmp = root->right;
        root->right = NULL;
        return tmp;
    }
    ///two child
    else
    {

    }
}/*
struct Node *find_parent( struct Node *root, struct Node *targ)
{

}*/
int removal(struct Node **root, int target)
{
    int couts = 0, tmp = 0;
    struct Node *cur = *root, *parent = *root, *find = *root;
//first, counts how many nodes needed to be removed
    inorder_counts( cur, &couts, target);
    if(couts == 0)
        return couts;
    while(tmp != couts)
    {
        struct Node *tmp = search_targ( cur, target);
        //parent = find_parent(cur, tmp);
        ///find parent
        while()
        {

        }
        delete_node( tmp, target);
        tmp++;
    }
    return couts;
}



void inorder(struct Node *root)
{
    if(root)
    {
        //printf("%d(1)  ", root->data);
        inorder(root->left);
        //printf("%d ", root->data);
        printf("%d(%p)  \n", root->data, root);
        inorder(root->right);
        //printf("%d(3)  ", root->data);
    }
    //printf("NULL\n");
    return;
}


int main()
{
    struct Node *tree = NULL, *node;
    int j, k, l;
    srand(time(NULL));
    for(j = 0; j < 15; j ++)
    {
        node = (struct Node *)malloc(sizeof(struct Node));
        node->data = rand() % 10;
        printf("%d ", node->data);
        node->left = NULL;
        node->right = NULL;
        insert(&tree, node);
    }
    printf("\n");
    inorder(tree);
    printf("\n");
    for(j = 0; j < 10; j ++)
    {
        l = rand() % 10;
        k = removal(&tree, l);
        printf("Remove %d(%d)\n", l, k);
    }
    inorder(tree);
    printf("\n");
}
/*
int main()
{
    struct Node *tree = NULL, *node;
    int j, k, l;
    srand(time(NULL));

    int test[19];
    test[0] = 1;
    test[1] = 4;
    test[2] = 6;
    test[3] = 2;
    test[4] = 2;
    test[5] = 3;
    test[6] = 3;
    test[7] = 8;
    test[8] = 8;
    test[9] = 4;
    test[10] = 2;
    test[11] = 1;
    test[12] = 3;
    test[13] = 0;
    test[14] = 3;
    //test[15] = 10;
    //test[16] = 12;
    // test[17] = 14;
    // test[18] = 15;

    for(j = 0; j < 15; j ++)
    {
        node = (struct Node *)malloc(sizeof(struct Node));
        //node->data = rand() % 10;
        node->data = test[j];
        node->left = NULL;
        node->right = NULL;
        insert(&tree, node);
    }
    inorder(tree);
    printf("\n");

    l = 7;
    k = removal(&tree, l);
    printf("Remove %d(%d)\n", l, k);
    inorder(tree);
    printf("\n");

    l = 6;
    k = removal(&tree, l);
    printf("Remove %d(%d)\n", l, k);
    inorder(tree);
    printf("\n");

    l = 1;
    k = removal(&tree, l);
    printf("Remove %d(%d)\n", l, k);
    inorder(tree);
    printf("\n");
    /*
            l = 9;
            k = removal(&tree, l);
            printf("Remove %d(%d)\n", l, k);


        inorder(tree);
        printf("\n");


}
*/


/*
Week 8 Question 1
Description

Please finish the two function remove and inorder in template.
Please make sure that tree still be a binary search tree after remove .
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int data, height;
    struct Node *left, *right, *parnt;
};

void getHigh(struct Node *root)
{
    if (root)
    {
        int L, R;
        if (root->left)
            L = root->left->height + 1;
        else
            L = 1;

        if (root->right)
            R = root->right->height + 1;
        else
            R = 1;

        if (L > R)
            root->height = L;
        else
            root->height = R;
        getHigh(root->parnt);
    }
    return;
}

void insert(struct Node **root, struct Node *node)
{
    if (!(*root))
    {
        (*root) = node;
        getHigh(node);
        return;
    }

    struct Node *cur = (*root);
    struct Node *head = (*root);
    
    //    printf("!123!\n");
    while (1)
    {
        if (cur->data >= node->data) //go left
        {
            if (cur->left == NULL)
            {
                cur->left = node;
                node->parnt = cur;
                break;
            }
            cur = cur->left;
        }
        else if (cur->data < node->data)
        {
            if (cur->right == NULL)
            {
                cur->right = node;
                node->parnt = cur;
                break;
            }
            cur = cur->right;
        }
    }
    //    printf("return\n\n");
    getHigh(node);
    return;
}

/*
Function removal will remove all the node tree content data n.
The return value of function removal is a integer represent how many node are removed.
*/

struct Node *findMax(struct Node *root)
{
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

struct Node *find_min(struct Node *root)
{
    while (root->left)
        root = root->left;
    return root;
}
struct Node *Find(struct Node *root, int targ)
{
    while (1)
    {
         if (!root)
            return NULL;
        else
        {
            if (root->data == targ)
                return root;
            else if (root->data > targ) //root > elemt
                root = root->left;
            else //root < elemt
                root = root->right;

            if (!root)
                return NULL;
        }
    }
}

void inorder(struct Node *root)
{
    if (root)
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

void inorder_counts(struct Node *root, int *counts, int targ)
{
    if (root)
    {
        inorder_counts(root->left, counts, targ);
        if (root->data == targ)
            (*counts)++;
        inorder_counts(root->right, counts, targ);
    }
    return;
}

void delete_node(struct Node **tree, int targ)
{
    if ((*tree) == NULL)
        return;

    struct Node *head = (*tree);
    struct Node *root = (*tree);

    struct Node *targPtr = Find(root, targ);
   // printf("find:(%p)%d \t H:%d\n", targPtr, targPtr->data, targPtr->height);

    if (targPtr == (*tree))
    {
        if ((!((*tree)->left)) && (!((*tree)->right)))
        {
            free(*tree);
            return;
        }
        else if ((!((*tree)->left)) && ((*tree)->right))
        {
            struct Node *treeR = (*tree)->right;

            (*tree)->right = NULL;
            treeR->parnt = NULL;
            free(*tree);
            (*tree) = treeR;
        }
        else if (((*tree)->left) && (!((*tree)->right)))
        {
            struct Node *treeL = (*tree)->left;

            (*tree)->left = NULL;
            treeL->parnt = NULL;
            free(*tree);
            (*tree) = treeL;
        }
        else // ((*tree)->left)  && ((*tree)->right)
        {
            int L = targPtr->left->height;
            int R = targPtr->right->height;

            if (R >= L)
            {
               // printf("R>=L\n");
                struct Node *minNode = find_min((*tree)->right);
               // printf("minNode:(%p)%d \t H:%d\n", minNode, minNode->data, minNode->height);
               
                struct Node *targLeft = (*tree)->left;
                (*tree)->left = NULL;
                targLeft->parnt = NULL;

                if (minNode->parnt == (*tree))
                {
                    //printf("if (minNode->parnt == (*tree))\n");
                    (*tree)->right = NULL;
                    minNode->parnt = NULL;
                }
                else
                {
                    struct Node *targRight = (*tree)->right;
                    (*tree)->right = NULL;
                    targRight->parnt = NULL;

                    struct Node *minNodeParnt = minNode->parnt;
                    minNode->parnt = NULL;
                    minNodeParnt->left = NULL;

                    struct Node *minNodeRight = minNode->right;
                    minNode->right = NULL;
                    if (minNodeRight)
                    {
                        minNodeRight->parnt = NULL;
                        minNodeRight->parnt = minNodeParnt;
                    }
                    minNodeParnt->left = minNodeRight;

                    targRight->parnt = minNode;
                    minNode->right = targRight;
                }

                targLeft->parnt = minNode;
                minNode->left = targLeft;
                free(*tree);
                (*tree) = minNode;
            }
            else
            {
                //printf("else L<R\n");
                struct Node *maxNode = findMax((*tree)->left);
                struct Node *targRight = (*tree)->right;
                (*tree)->right = NULL;
                targRight->parnt = NULL;

                if (maxNode->parnt == (*tree))
                {
                    (*tree)->left = NULL;
                    maxNode->parnt = NULL;
                }
                else //max->parnt != (*tree)
                {
                    struct Node *targLeft = (*tree)->left;
                    (*tree)->left = NULL;
                    targLeft->parnt = NULL;

                    struct Node *maxNodeParnt = maxNode->parnt;
                    maxNode->parnt = NULL;
                    maxNodeParnt->right = NULL;

                    struct Node *maxNodeLeft = maxNode->left;
                    maxNode->left = NULL;
                    if (maxNodeLeft)
                    {
                        maxNodeLeft->parnt = NULL;
                        maxNodeLeft->parnt = maxNodeParnt;
                    }
                    maxNodeParnt->right = maxNodeLeft;

                    targLeft->parnt = maxNode;
                    maxNode->left = targLeft;
                }

                maxNode->right = targRight;
                targRight->parnt = maxNode;
                free(*tree);
                (*tree) = maxNode;
            }
        }

        getHigh(*tree);
        return;
    }
    else
    {
        if ((!(targPtr->left)) && (!(targPtr->right))) //targPtr has no child
        {
            struct Node *targParnt = targPtr->parnt;

            targPtr->parnt = NULL;
            if (targParnt->left == targPtr)
                targParnt->left = NULL;
            else //(targParnt->right == targ)
                targParnt->right = NULL;

            free(targPtr);
            targPtr = targParnt;
        }
        else if ((!(targPtr->left)) && (targPtr->right)) //targ has right child
        {
            struct Node *minNode = find_min(targPtr->right);
        

            struct Node *targParnt = targPtr->parnt;
            targPtr->parnt = NULL;

            if (minNode->parnt == targPtr)
            {
                targParnt->right = NULL;
                minNode->parnt = NULL;

                minNode->parnt = targParnt;
                if (targParnt->right = targPtr)
                {
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }
            }
            else
            {
                struct Node *targRight = targPtr->right;
                targPtr->right = NULL;
                targRight->parnt = NULL;

                struct Node *minNodeParnt = minNode->parnt;
                minNode->parnt = NULL;
                minNodeParnt->left = NULL;

                struct Node *minNodeRight = minNode->right;
                minNodeRight->parnt = NULL;
                minNode->right = NULL;

                minNodeRight->parnt = minNodeParnt;
                minNodeParnt->left = minNodeRight;

                minNode->parnt = targParnt;
                if (targParnt->right == targPtr)
                {
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }

                targRight->parnt = minNode;
                minNode->right = targRight;
            }
            free(targPtr);
            targPtr = minNode;
        }
        else if ((targPtr->left) && (!(targPtr->right))) //targ has left child
        {
            struct Node *maxNode = findMax(targPtr->left);

            struct Node *targParnt = targPtr->parnt;
            targPtr->parnt = NULL;

            if (maxNode->parnt == targPtr)
            {
                targPtr->left = NULL;
                maxNode->parnt = NULL;
            }
            else
            {
                struct Node *targLeft = targPtr->left;
                targPtr->left = NULL;
                targLeft->parnt = NULL;

                struct Node *maxNodeParnt = maxNode->parnt;
                maxNode->parnt = NULL;
                maxNodeParnt->right = NULL;

                struct Node *maxNodeLeft = maxNode->left;
                maxNodeLeft->parnt = NULL;
                maxNode->left = NULL;

                maxNodeLeft->parnt = maxNodeParnt;
                maxNodeParnt->right = maxNodeLeft;

                targLeft->parnt = maxNode;
                maxNode->left = targLeft;
            }

            maxNode->parnt = targParnt;
            if (targParnt->right == targPtr)
            {
                targParnt->right = NULL;
                targParnt->right = maxNode;
            }
            else
            {
                targParnt->left = NULL;
                targParnt->left = maxNode;
            }
            free(targPtr);
            targPtr = maxNode;
        }
        else if ((targPtr->left) && (targPtr->right)) //targ has both child
        {
            //printf("else if ((targ->left) && (targ->right))\n");
            int L = targPtr->left->height;
            int R = targPtr->right->height;
            if (R >= L) //in right find minNode
            {
                printf("\t\tif( R >= L)\n");
                struct Node *minNode = find_min(targPtr->right);
                printf("miinNode:(%p)%d  H:%d\n", minNode, minNode->data, minNode->height);
                struct Node *targL = targPtr->left;
                targPtr->left = NULL;
                targL->parnt = NULL;

                struct Node *targParnt = targPtr->parnt;
                targPtr->parnt = NULL;

                if (minNode->parnt == targPtr)
                {
                    targPtr->right = NULL;
                    minNode->parnt = NULL;
                }
                else //minNode->parnt != targ
                {

                    struct Node *minParnt = minNode->parnt;
                    minNode->parnt = NULL;
                    minParnt->left = NULL;

                    struct Node *minRight = minNode->right;
                    minNode->right = NULL;
                    if (minRight)
                    {
                        minRight->parnt = NULL;
                        minRight->parnt = minParnt;
                    }
                    minParnt->left = minRight;

                    minNode->right = minParnt;
                    minParnt->parnt = minNode;
                }
                ///minNode connect to targ
                minNode->parnt = targParnt;
                if (targParnt->right == targPtr)
                {
                    //printf("!!\n");
                    targParnt->right = NULL;
                    targParnt->right = minNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = minNode;
                }

                minNode->left = targL;
                targL->parnt = minNode;

                free(targPtr);
                targPtr = minNode;
                //printf("-----------targ--------------------------------%p----------------------------------------------\n", targ);
            }
            else //in left child find maximum node
            {
                struct Node *maxNode = findMax(targPtr->left);
                printf("max:%d(%p) H:%d\n", maxNode->data, maxNode, maxNode->height);
                struct Node *targR = targPtr->right;
                targPtr->right = NULL;
                targR->parnt = NULL;

                struct Node *targL = targPtr->left;
                printf("targL:%d(%p) H:%d\n", targL->data, targL, targL->height);
                
                struct Node *targParnt = targPtr->parnt;
                targPtr->parnt = NULL;

                if (maxNode->parnt == targPtr)
                {
                    targPtr->left = NULL;
                    maxNode->parnt = NULL;
                }
                else //maxNode->parnt != targ
                {
                    struct Node *maxParnt = maxNode->parnt;
                    maxNode->parnt = NULL;
                    maxParnt->right = NULL;

                    struct Node *maxLeft = maxNode->left;
                    maxNode->left = NULL;
                    if (maxLeft)
                    {
                        maxLeft->parnt = NULL;
                        maxLeft->parnt = maxParnt;
                    }
                    maxParnt->right = maxLeft;

                    maxNode->left = targL;
                    targL->parnt = maxNode;
                }
                ///maxNode connect to targ
                maxNode->parnt = targParnt;
                if (targParnt->right == targPtr)
                {
                    targParnt->right = NULL;
                    targParnt->right = maxNode;
                }
                else
                {
                    targParnt->left = NULL;
                    targParnt->left = maxNode;
                }

                maxNode->right = targR;
                targR->parnt = maxNode;
                
                free(targPtr);
                targPtr = maxNode;
            }
        }
        getHigh(targPtr);
        return;
    }
}

int removal(struct Node **root, int target)
{
    int couts = 0;
    struct Node *cur = *root;

    //first, counts how many nodes needed to be removed
    inorder_counts(cur, &couts, target);
    if (couts == 0)
        return couts;

    int tmp = 0;
    while (tmp != couts)
    {
        //printf("tmp:%d\n", tmp);
        /*printf("\n--------------------------------------------------\n");
        inorder(*root);*/
        delete_node(root, target);
        tmp++;
        //printf("tmp:%d\n", tmp);
        printf("\n--------------------------------------------------\n");
        inorder(*root);
        printf("\n==================================================\n");
    }

    return couts;
}
int main()
{
    struct Node *tree = NULL, *node;
    int j, k, l;
    srand(5);
    for (j = 0; j < 15; j++)
    {
        node = (struct Node *)malloc(sizeof(struct Node));
        node->data = rand() % 10;
        printf("%d ", node->data);
        printf("%d\n", j);
        node->left = NULL;
        node->right = NULL;
        node->parnt = NULL;
        node->height = 0;
        insert(&tree, node);
    }
    printf("\n");
    inorder(tree);
    printf("\n");
    for (j = 0; j < 10; j++)
    {
        l = rand() % 10;
        printf("l:%d\t", l);
        k = removal(&tree, l);
        printf("Remove %d(%d)\n", l, k);
    }
    inorder(tree);
    printf("\n");
}

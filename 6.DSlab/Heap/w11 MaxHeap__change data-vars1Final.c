/*
Week 11 Question 1
Description

請完成樣板中的最大堆積

Please finish the maximum heap in template.

如果你能完成所有功能你可以得到60分

If you complete all function then you can get 60 points.

如果你在插入時能保持樹的平衡你可以在得到額外的20分

If you can keep the heap height-balanced while insert, then you can get extract 20 points.

如果你在移除節點時也能保持樹的平衡，你可以在得到額外的20分

If you can keep the heap height-balanced while remove, then you can get extract 20 points.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

///MaxHeap
struct Node
{
    int data;
    struct Node *left, *right, *parent;
};

/*
Function getHeight take one parameter represent a tree root
and return an integer as the height of the tree.
*/

int getHeight(int index)
{
    int high = 0;
    while(index >= 0)
    {
        high++;
        if(index%2 == 0)
            index = (index-2)/2;
        else
            index = (index-1)/2;
    }
    return high;
}

/*
Function insert take parament root represent a maximum heap and insert data
into the maximum heap.
*/
struct Node *malloc_Node(int num)
{
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->data = num;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    return newnode;
}
void inorder(struct Node *root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d(%p)\t", root->data, root);
        inorder(root->right);
    }
    return;
}

void inorder_debug(struct Node *root)
{
    if(root)
    {
        //printf("!!\n");
        //printf("%d ", root->data);
        printf("L: ");
        inorder_debug(root->left);
        if(root->parent != NULL)
            printf("%d(parent)\tcur:%d(%p)\n", root->parent->data, root->data, root);
        else
            printf("\t\tcur:%d(%p)  \n", root->data, root);

        printf("R: ");
        inorder_debug(root->right);
    }
    else
        printf("NULL\n");
    printf("return;\n\n");
    return;
}


void heapUp(struct Node **root, struct Node *now)
{
    if( now->parent != NULL)
    {
        if(now->data <= now->parent->data)
        {
            return;
        }
        int tmp = now->data;
        now->data = now->parent->data;
        now->parent->data = tmp;

        heapUp( root, now->parent);
    }
    return;
}

void insert(struct Node **root, struct Node **stack_arr, int num, int *stack_i)
{
    struct Node *newnode = malloc_Node(num);
    if( (*root) == NULL)
    {
        (*root) = newnode;
        stack_arr[(*stack_i)] = (*root);
        (*stack_i)++;
        return;
    }

    struct Node *cur = (*root);
    
    int parent_i = ((*stack_i) -1)/2;
    struct Node *parnt = stack_arr[parent_i];

    if(parnt->left == NULL)
    {
        parnt->left = newnode;
    }
    else
    {
        parnt->right = newnode;
    }
    
    newnode->parent = parnt;
    stack_arr[(*stack_i)] = newnode;
    (*stack_i)++;

    heapUp( root, newnode);

}

/*
Function remove take parament root represent a maximum heap and remove the root
from heap.
Please keep the heap as a maximum heap while removing the root.
Return the data you removed.
If there is nothing in the heap, return NULL.
*/
void heapDown( struct Node **root, struct Node *cur, int flag)
{
    struct Node *max = cur;
    if(cur->right != NULL)
    {
        if(max->data < cur->right->data)
            max = cur->right;
    }
    if(cur->left != NULL)
    {
        if(max->data < cur->left->data)
            max = cur->left;
        
    }

    if(max == cur->left)
    {
        int tmp = cur->left->data;
        cur->left->data = cur->data;
        cur->data = tmp;

        cur = cur->left;
        flag = 1;
    }
    if(max == cur->right)
    {
        int tmp = cur->right->data;
        cur->right->data = cur->data;
        cur->data = tmp;

        cur = cur->right;
        flag = 1;
    }

    if(flag == 1)
        heapDown( root, cur, 0);
    else
    {
        return;
    }    
}

struct Node *remove_heap(struct Node **root, struct Node **stackArr, int *stack_i)
{
    (*stack_i)--;
    if((*stack_i) < 0)
        return NULL;
    struct Node *last = stackArr[(*stack_i)];

    if((*stack_i) == 0)
    {
        return last;
    }

    struct Node *head = *root;

    int tmp = (*root)->data;
    (*root)->data = last->data;
    last->data = tmp;

    struct Node *parnt = last->parent;

    if(parnt->left == last)
    {
        parnt->left = NULL;
    }
    else
    {
        parnt->right = NULL;
    }
    last->parent = NULL;

    struct Node *cur = (*root);
    heapDown( root, cur, 0);

    return last;
}

int main()
{
    int j;
    struct Node *k;
    struct Node *heap = NULL;
    struct Node *stackHeap[200];
    int stack_i = 0;

    srand(5);


    for(j = 0; j < 31; j ++)
    {
        int num = rand();
        insert(&heap, stackHeap, num, &stack_i);

    }
    printf("\n");

    while(1)
    {
        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            break;
        printf("%d(%d) \n", k->data, getHeight(stack_i));
    }
}

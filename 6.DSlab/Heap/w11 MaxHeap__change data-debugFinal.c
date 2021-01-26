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
/*
int getHeight(struct Node *root)
{
    int index = 0;
    while (root != NULL)
    {
        root = root->left;
        index++;
    }
    return index;
    
}
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
}
/*
void swap_fn(void *eleA, void *eleB, int eleSize)
{
    void *tmp = (char*)malloc(sizeof(char)*eleSize);
    memcpy(tmp, eleA, eleSize);
    memcpy(eleA, eleB, eleSize);
    memcpy(eleB, tmp, eleSize);
    free(tmp);
    return;
}

*/



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
//    printf("parent:%d(%p)\n", parnt->data, parnt );

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

    /*
        for(int i = 0 ; i < *stack_i ; i++)
            printf("(%d)%p ", stack_arr[i]->data, stack_arr[i]);
        printf("\n");
        inorder_debug(head);
        head = *root;
        inorder(head);
        printf("\n heapUp \n");
        */
    heapUp( root, newnode);

    //inorder(head);
    //printf("\n");
    //inorder_debug(head);
    //printf("\n================================================\n");
}

/*
Function remove take parament root represent a maximum heap and remove the root
from heap.
Please keep the heap as a maximum heap while removing the root.
Return the data you removed.
If there is nothing in the heap, return NULL.
*/
void heapDown( struct Node **root, struct Node *cur, int flag)
{/*
    getch();
    if (cur->left == NULL && cur->right == NULL)
    {
        printf("if (cur->left == NULL && cur->right == NULL) AND return\n");
        return;
    }
    */
//    printf("cur->data:%d(%p)\n", cur->data, cur);
    struct Node *max = cur;
    if(cur->right != NULL)
    {
//        printf("cur->right:%d(%p)\n", cur->right->data, cur->right);
        if(max->data < cur->right->data)
            max = cur->right;
//        printf("max->data:%d(%p)\n", max->data, max);
    }
    if(cur->left != NULL)
    {
//        printf("cur->left:%d(%p)\n", cur->left->data, cur->left);
        if(max->data < cur->left->data)
            max = cur->left;
//        printf("max->data:%d(%p)\n", max->data, max);
        
    }

    if(max == cur->left)
    {
//        printf("if(max == cur->left)\n");
//        printf("cur->left:%d(%p)\n", cur->left->data, cur->left);
//        printf("cur->data:%d(%p)\n", cur->data, cur);
        int tmp = cur->left->data;
        cur->left->data = cur->data;
        cur->data = tmp;
//        printf("cur->left:%d(%p)\n", cur->left->data, cur->left);
//        printf("cur->data:%d(%p)\n\n", cur->data, cur);

        cur = cur->left;
//        printf("cur->data:%d(%p)\n", cur->data, cur);
        flag = 1;
    }
    if(max == cur->right)
    {
//        printf("if(max == cur->right)\n");
//        printf("cur->right:%d(%p)\n", cur->right->data, cur->right);
//        printf("cur->data:%d(%p)\n", cur->data, cur);
        int tmp = cur->right->data;
        cur->right->data = cur->data;
        cur->data = tmp;
//        printf("cur->right:%d(%p)\n", cur->right->data, cur->right);
//        printf("cur->data:%d(%p)\n\n", cur->data, cur);

        cur = cur->right;
//        printf("cur->data:%d(%p)\n", cur->data, cur);
        flag = 1;
    }

    if(flag == 1)
        heapDown( root, cur, 0);
    else
    {
//        printf("heapDown out and return\n");
        return;
    }    
}

struct Node *remove_heap(struct Node **root, struct Node **stackArr, int *stack_i)
{
//    printf("In remove\n");
//    printf("stack_i:%d\n\n", (*stack_i));


//    struct Node *print = malloc_Node()
    (*stack_i)--;
    if((*stack_i) < 0)
        return NULL;
    struct Node *last = stackArr[(*stack_i)];
//    printf("stack_i:%d\n\n", (*stack_i));
    if((*stack_i) == 0)
    {
        return last;
    }

//    printf("%d(%p)\n", last->data, last);
    struct Node *head = *root;

//    printf("\n------------------------------------#1-------------------------------------------\n");
    int tmp = (*root)->data;
    (*root)->data = last->data;
    last->data = tmp;

/*
    printf("stack:\n");
    for(int i = 0 ; i <= (*stack_i) ; i++)
    {
        printf("%d(%p)\t", stackArr[i]->data, stackArr[i]);
    }
    printf("\ninorder\n");
    inorder( head);
    printf("\n=============================================================================================\n");
    printf("\n--------------------------------#2--------------------------------\n");
*/
    struct Node *parnt = last->parent;

//    printf("parent:%d(%p)\n", parnt->data,  parnt);

    if(parnt->left == last)
    {
//        printf("parent->left:%d(%p)\n", parnt->left->data, parnt->left);
//        printf("last:%d(%p)\n", last->data, last);
//        printf("parnt->left == last\n");
        parnt->left = NULL;
    }
    else
    {
//        printf("parent->right:%d(%p)\n", parnt->right->data, parnt->right);
//        printf("last:%d(%p)\n", last->data, last);
//        printf("parnt->right== last\n");
        parnt->right = NULL;
    }
    last->parent = NULL;

//    if(last->parent == NULL && last->left == NULL && last->right == NULL)
//        printf("(last)ALL NULL!!\n");
    //printf("%d(%p)\n", last->data, last);
/*

    printf("stack:\n");
    for(int i = 0 ; i <= (*stack_i) ; i++)
    {
        printf("%d(%p)\t", stackArr[i]->data, stackArr[i]);
    }
    printf("\ninorder\n");
    inorder( head);
    printf("\n=============================================================================================\n");
    printf("\n---------------------------------------------#3------------------------------------\n");
*/
    struct Node *cur = (*root);

    heapDown( root, cur, 0);
/*
    while(1)
    {
        int L = -1, R = -1;
        if(cur->left != NULL)
            L = cur->left->data;
        if(cur->right != NULL)
            R = cur->right->data;
        printf("L:%d\tR:%d\n", L, R);

        if( L == -1 && R == -1)
            break;
        //printf("cur:%d(%p)\n", cur->data, cur);
        if(L > R)
        {
           // printf("L>R\n");
            if(L >cur->data)
            {
                int tmp = cur->data;
                cur->data = cur->left->data;
                cur->left->data = tmp;

            }
            cur = cur->left;
        }
        else
        {
            printf("L<=R\n");
            if(R > cur->data)
            {
                int tmp = cur->data;
                cur->data = cur->right->data;
                cur->right->data = tmp;

            }
            cur = cur->right;
        }
        */
/*
        printf("stack:\n");
        for(int i = 0 ; i < *stack_i ; i++)
        {
            printf("%d(%p)\t", stackArr[i]->data, stackArr[i]);
        }
        printf("\ninorder\n");
        inorder( head);
        printf("\n=============================================================================================\n");

    }*/
    //printf("\n=============================================================================================\n");
    /*

    /*

    struct Node *head = (*root);
    printf("stack:\n");
    for(int i = 0 ; i < *stack_i ; i++)
    {
        printf("%d(%p)\t", stackArr[i]->data, stackArr[i]);
    }
    printf("\ninorder\n");
    inorder( head);
    printf("\n=============================================================================================\n");
    */
    return last;
}

int main()
{
    int j;
    struct Node *k;
    struct Node *heap = NULL;
    struct Node *stackHeap[200];
    int stack_i = 0;

    //srand(1);

    /*for(j = 0; j < 10; j ++)
    {
        int num = rand() % 100;
        printf("j(%d):%d \n", j, num);
        insert(&heap, stackHeap, num, &stack_i);

    }
    */


    srand(5);


    for(j = 0; j < 10; j ++)
    {
        int num = rand() % 100;
       // printf("j(%d):%d \n", j, num);
        insert(&heap, stackHeap, num, &stack_i);

    }
    printf("\n");
    //inorder_debug(heap);
/*

    printf("stack:\n");
    for(int i = 0 ; i < stack_i ; i++)
    {
        printf("%d(%p)\t", stackHeap[i]->data, stackHeap[i]);
    }
    printf("\ninorder\n");
    inorder( heap);
    printf("\n=============================================================================================\n");
*/

    while(1)
    {
        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            break;
//        printf("%d \n", k->data);
        //inorder_debug(heap);
        printf("%d(%d) \n", k->data, getHeight(stack_i));
    }


    /*
        printf("\n");
        inorder_debug(heap);
    */
    /*
        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));

        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));

        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));

        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));

        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));

        k = remove_heap(&heap, stackHeap, &stack_i);
        if(k == NULL)
            printf("NULL!!!!!!\n");
        printf("%d(%p) \n", k->data, getHeight(heap));
    */
    /*
        while(1)
        {
            k = remove_heap(&heap, stackHeap, &stack_i);
            if(k == NULL)
                break;
            printf("%d(%p)(%d) \n", k->data, k, getHeight(heap));
        }
    */


}

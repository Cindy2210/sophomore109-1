/*
Week 14 Question 1
Description

請完成樣板中的 Prim's Algorithm 以及Kruskal's Algorithm

如果你只完成 Kruskal's Algorithm 給你 70 分

如果你只完成Prim's Algorithm 給你 80 分

兩個都完成給你 100 分
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vertex
{
    struct Edge *edgeList[100];
    int edgeCount;
    int id;
};

struct Edge
{
    struct Vertex *end[2];
    int w;
};

//請把找到的邊存在 result
void Kruskal(struct Vertex v[10], struct Edge e[100], struct Edge *result[100])
{
}

///MinHeap
struct Node
{
    struct Edge *ans;
    //int counts = 0;//counts how many edge I have
    struct Node *left, *right, *parent;
};

/*
Function getHeight take one parameter represent a tree root
and return an integer as the height of the tree.
*/
int getHeight(int index)
{
    int high = 0;
    while (index >= 0)
    {
        high++;
        if (index % 2 == 0)
            index = (index - 2) / 2;
        else
            index = (index - 1) / 2;
    }
    return high;
}

/*
Function insert take parament root represent a maximum heap and insert data
into the maximum heap.
*/
struct Node *malloc_Node(struct Edge *targ)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->ans = targ;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    return newnode;
}
void inorder(struct Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("end[0]:%d(%p) end[1]:%d(%p)\t w:%d(%p)\n", root->ans->end[0]->id, root->ans->end[0], root->ans->end[1]->id, root->ans->end[1], root->ans->w, &root->ans->w);
        inorder(root->right);
    }
}
void preorder(struct Node *root)
{
    if (root)
    {
        printf("end[0]:%d(%p) end[1]:%d(%p)\t w:%d(%p)\n", root->ans->end[0]->id, root->ans->end[0], root->ans->end[1]->id, root->ans->end[1], root->ans->w, &root->ans->w);
        preorder(root->left);
        preorder(root->right);
    }
}
void I(struct Node *root)
{
    if (root)
    {
        printf("L:\t");
        I(root->left);
        printf("end[0]:%d(%p) end[1]:%d(%p)\t w:%d(%p)\n", root->ans->end[0]->id, root->ans->end[0], root->ans->end[1]->id, root->ans->end[1], root->ans->w, &root->ans->w);
        printf("R:\t");
        I(root->right);
    }
    printf("return\n");
}
void swap(struct Edge *A, struct Edge *B)
{
    struct Edge *tmp = (struct Edge *)malloc(sizeof(struct Edge));
    tmp->end[0] = A->end[0];
    tmp->end[1] = A->end[1];
    tmp->w = A->w;

    A->end[0] = B->end[0];
    A->end[1] = B->end[1];
    A->w = B->w;

    B->end[0] = tmp->end[0];
    B->end[1] = tmp->end[1];
    B->w = tmp->w;
    return;
}

void heapUp(struct Node **root, struct Node *now)
{
    if (now->parent != NULL)
    {
        if (now->ans->w >= now->parent->ans->w)
            return;

        //swap_data(now->data, now->parent->data);
        swap(now->ans, now->parent->ans);
        heapUp(root, now->parent);
    }
    return;
}

void insert(struct Node **root, struct Node **stack_arr, struct Edge *targ, int *stack_i)
{
    printf("insert\n");
    struct Node *newnode = malloc_Node(targ);
    if ((*root) == NULL)
    {
        (*root) = newnode;
        stack_arr[(*stack_i)] = (*root);
        (*stack_i)++;
        return;
    }

    struct Node *cur = (*root);
    struct Node *head = (*root);
    int nowQueue_i = 0, flag_L = 0, flag_R = 0;

    cur = stack_arr[nowQueue_i];

    if (cur->left != NULL)
        flag_L = 1;
    if (cur->right != NULL)
        flag_R = 1;

    while (flag_L == 1 && flag_R == 1) ///flag == 0 means this child is empty
    {
        flag_L = 0;
        flag_R = 0;
        nowQueue_i++;
        cur = stack_arr[nowQueue_i];
        if (cur->left != NULL)
            flag_L = 1;
        if (cur->right != NULL)
            flag_R = 1;
    }

    if (cur->left == NULL)
    {
        cur->left = newnode;
        newnode->parent = cur;
        stack_arr[(*stack_i)] = newnode; //enqueue
        (*stack_i)++;
        cur = cur->left;
    }
    else if (cur->right == NULL)
    {
        cur->right = newnode;
        newnode->parent = cur;
        stack_arr[(*stack_i)] = newnode;
        (*stack_i)++;
        cur = cur->right;
    }
    heapUp(root, cur);
}

/*
Function remove take parament root represent a maximum heap and remove the root
from heap.
Please keep the heap as a maximum heap while removing the root.
Return the data you removed.
If there is nothing in the heap, return NULL.
*/

struct Node *pop(struct Node **root, struct Node **stackArr, int *stack_i)
{
    (*stack_i)--;
    if ((*stack_i) < 0)
    {
        return NULL;
    }

    struct Node *last = stackArr[(*stack_i)];

    if ((*stack_i) == 0)
        return *root;
    swap((*root)->ans, last->ans);
    //heapDown
    struct Node *parnt = last->parent;
    if (parnt->left == last)
        parnt->left = NULL;
    else
        parnt->right = NULL;
    last->parent = NULL;

    struct Node *cur = (*root);
    while (1)
    {
        int L = 9999, R = 9999;
        if (cur->left != NULL)
            L = cur->left->ans->w;
        if (cur->right != NULL)
            R = cur->right->ans->w;

        if (L == 9999 && R == 9999)
            break;

        if (L < R)
        {
            if (L < cur->ans->w)
            {
                swap(cur->ans, cur->left->ans);
            }
            cur = cur->left;
        }
        else
        {
            if (R < cur->ans->w)
            {
                swap(cur->ans, cur->right->ans);
            }
            cur = cur->right;
        }
    }
    return last;
}

void printEdge(struct Edge e[100], int edgeLength)
{
    int j, k;
    //printf("%d\n", edgeLength);
    for (j = 0; j < edgeLength; j++)
    {
        printf("(%p)%d \t(%p)%d\t", e[j].end[0], e[j].end[0]->id, e[j].end[1], e[j].end[1]->id);
        printf("w:%d(%p)\n", e[j].w, &e[j].w);

        //printf("j:%d\n", j);
    }

    //printf("!!!!\n");
    return;
}
//請把找到的邊存在 result
//root 表示起點為 v[root]
void prim(struct Vertex v[10], struct Edge e[100], int edgeLength, struct Edge *result[100], int root)
{
    struct Node *stackHeap[200];
    int stack_i = 0;
    struct Node *heap = NULL;

    printf("v[root].id:%d(root:%d)<%p>\n", v[root].id, root, v[root]);
    //sort edge
    struct Edge sort[100];

    for (int i = 0; i < edgeLength - 1; i++)
    {
        int min = i;
        if (i == 0)
        {
            if (e[0].end[0]->id > e[0].end[1]->id)
            {
                struct Vertex *tmpV = e[0].end[0];
                e[0].end[0] = e[0].end[1];
                e[0].end[1] = tmpV;
            }
        }

        for (int j = i + 1; j < edgeLength; j++)
        {
            if (e[j].w < e[min].w)
                min = j;

            if (e[j].end[0]->id > e[j].end[1]->id)
            {
                struct Vertex *tmpV = e[j].end[0];
                e[j].end[0] = e[j].end[1];
                e[j].end[1] = tmpV;
            }
        }
        swap(&e[i], &e[min]);
    }

    printEdge(e, edgeLength);
    printf("---------------------------------------------------\n\n");
    int resultI = 0;
    int markv[10];

    for (int i = 0; i < 10; i++)
        markv[i] = 0;
    markv[root] = 1;
    while (1)
    {
        printf("v[root].id:%d(root:%d)<%p>\n", v[root].id, root, v[root]);

        for (int i = 0; i < edgeLength; i++)
        {
            if (e[i].end[0] == e[i].end[1])
                continue;

            /*printf("(%p)%d \t(%p)%d\t", e[i].end[0], e[i].end[0]->id, e[i].end[1], e[i].end[1]->id);
            printf("w:%d(%p)\n", e[i].w, e[i]);
*/
            if (e[i].end[0] == &v[root] && markv[e[i].end[1]->id - 1] == 0)
            {
                //enheap
                printf("end[0]== root\n");

                printf("(%p)%d \t(%p)%d\t", e[i].end[0], e[i].end[0]->id, e[i].end[1], e[i].end[1]->id);
                printf("w:%d(%p)\n", e[i].w, e[i]);
                markv[e[i].end[1]->id - 1] = 1;
                insert(&heap, stackHeap, &e[i], &stack_i);
            }
            if (e[i].end[1] == &v[root] && markv[e[i].end[0]->id - 1] == 0)
            {
                //enheap
                printf("end[1]== root\n");
                printf("(%p)%d \t(%p)%d\t", e[i].end[0], e[i].end[0]->id, e[i].end[1], e[i].end[1]->id);
                printf("w:%d(%p)\n", e[i].w, e[i]);
                markv[e[i].end[0]->id - 1] = 1;
                insert(&heap, stackHeap, &e[i], &stack_i);
            }
        }
        printf("==++Heap++==\n");
        /*
        printf("inorder\n");
        inorder(heap);
        printf("preorder\n");
        preorder(heap);
        printf("\nheapover\n");*/
        printf("I\n");
        I(heap);
        printf("\nheapover\n");

        if (stack_i == 0)
            break;
        result[resultI] = pop(&heap, stackHeap, &stack_i)->ans;

        printf("result[resultI](%p)%d \t(%p)%d\t", result[resultI]->end[0], result[resultI]->end[0]->id, result[resultI]->end[1], result[resultI]->end[1]->id);
        printf("w:%d(%p)\n", result[resultI]->w, &result[resultI]->w);

        printf("---------------------result------------------------------------------------\n");
        for (int j = 0; j <= resultI; j++)
        {
            printf("(%p)%d \t(%p)%d\t", result[j]->end[0], result[j]->end[0]->id, result[j]->end[1], result[j]->end[1]->id);
            printf("w:%d(%p)\n", result[j]->w, &result[j]->w);

            //printf("j:%d\n", j);
        }
        printf("---------------------------------------------------------------------------\n");
        if (result[resultI]->end[0]->id == v[root].id)
        {
            root = result[resultI]->end[1]->id - 1;
            printf("result[resultI]->end[0]\n");
            printf("root:%d\n", root);
        }
        else if (result[resultI]->end[1]->id == v[root].id)
        {
            root = result[resultI]->end[0]->id - 1;
            printf("result[resultI]->end[1]\n");
            printf("root:%d\n", root);
        }

        resultI++;

        printf("**\n\n");
    }
    printf("\t\t\t\tOUT!!!\n");
    printEdge(*result, resultI);
    printf("===========================================================\n");
}

void print(struct Vertex v[10])
{
    int j, k;
    for (j = 0; j < 10; j++)
    {
        printf("%d :", v[j].id);
        for (k = 0; k < v[j].edgeCount; k++)
        {
            if (v[j].edgeList[k]->end[0] == &v[j])
                printf("%d ", v[j].edgeList[k]->end[1]->id);
            else
                printf("%d ", v[j].edgeList[k]->end[0]->id);
        }
        printf("\n");
    }
}

int main()
{
    struct Vertex v[10];
    struct Edge e[100];
    struct Edge *result[100];
    int j, k, i, l;

    srand(5);
    //產生點
    for (j = 0; j < 10; j++)
    {
        v[j].id = j + 1;
        v[j].edgeCount = 0;
    }

    //產生邊
    k = rand() % 30 + 1; //邊的數量
    for (j = 0; j < k; j++)
    {
        //先產生兩個端點
        i = rand() % 10;
        l = rand() % 10;
        //邊的重量
        e[j].w = rand() % 100;
        //兩個端點的連結
        e[j].end[0] = &v[i];
        e[j].end[1] = &v[l];
        printf("!! \t");
        //在兩個端點加入邊
        v[i].edgeList[v[i].edgeCount] = &e[j];
        v[i].edgeCount++;
        v[l].edgeList[v[l].edgeCount] = &e[j];
        v[l].edgeCount++;
    }
    printf("\n");
    printEdge(e, k);
    printf("-----------------------main---------------------\n\n");
    //Kruskal(v, e, result);
    for (j = 0; j < 2; j++)
        prim(v, e, k, result, j);
    /*
    struct Node *h = NULL;
    int index = 0;
    struct Node *r[100];


    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    for(j = 0;j < 5;j ++)
    {
        insert(&h, r, &e[j], &index);
        I(h);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }
    
    for(j = 0;j < 5;j ++)
    {
        //insert(&h, r, &e[j], &index);
        pop(&h, r, &index);
        I(h);
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    }*/
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insert(int root[2000], int node)
{
    int index = 0;
    while (index < 2000 && root[index] != -1)

    {
        if (root[index] < node)
            index = index * 2 + 2;
        else
            index = index * 2 + 1;
    }
    root[index] = node;
}

void inorder(int root[2000], int n)
{
    if (root[2 * n + 1] != -1)
        inorder(root, 2 * n + 1);

    printf("%d ", root[n]);
    if (root[2 * n + 2] != -1)
        inorder(root, 2 * n + 2);
}

/*
Function removal will remove all the node tree content data n.
The return value of function removal is a integer represent how many node are removed.
*/
int removal(int root[2000], int n)
{
    int counts = 0, tmp = 0, q[10];
    for (int i = 0; i < 2000; i++)
        if (root[i] == n)
            counts++;

    while (counts != tmp)
    {
        Delete(root, n);
        tmp++;
    }
    return counts;
}
void Delete(int root[2000], int n)
{
    int index;
    for (index = 0; index < 2000; index++)
        if (root[index] == n)
            break;

    if (root[2 * index + 1] != -1 && root[2 * index + 2] != -1)
    {
        printf("two childrend\n");

        int minI = findmin(root, 2 * index + 2);
        root[index] = root[minI];

        while(root[2*minI +2] != -1)
        {
            root[minI] = root[ minI*2 +2];
            root[minI *2 +2] = -1;
            minI = minI*2 +2;
        }
        root[minI] = -1;

    }
    else if (root[2*index +1] != -1 && root[2*index +2] == -1) //left child
    {
        printf("left childs\n");
        root[index] = root[2*index +1];
        connect(root, 2*index +1, -1);
    }
    else if (root[2*index +1] == -1 && root[2*index +2] != -1) // right child
    {
        printf("right childs\n");
        root[index] = root[2*index +2];
        connect(root, 2*index +2, 1);
    }
    else
    {
        printf("no childs\n");
        root[index] = -1;
    }
    return;
}
int findmin(int root[2000], int index)
{
    while (1)
    {
        if (root[2*index +1] != -1)
            index = index*2 +1;
        else
        {
            return index;
        }
    }
}
void connect(int root[2000], int index, int state)
{
    int parnt, child;
    if (state == -1) //only Left child
    {
        parnt = index;
        child = 2*index +1;
    }
    else if (state == 1) //only Right child
    {
        parnt = index;
        child = 2*index +2;
    }

    int flag = 0, leafnums = 2;
    while (1)
    {
        flag = 0;
        for (int i = 0; i < leafnums; i++)
        {
            if (root[child +i] != -1)
            {
                root[parnt +i] = root[child +i];
                root[child +i] = -1;
                flag = 1;
            }
        }

        if (flag == 1)
        {
            leafnums = 2*leafnums;
            if (state == -1) //L
            {
                parnt = 2*index +1;
                child = 2*parnt +1;
            }
            else if (state == 1) //R
            {
                parnt = child;
                child = 2*child +2;
            }
        }
        else
            break;
    }
}

int main()
{
    int tree[2000];
    int j, k, l, node;
    srand(time(NULL));

    for (j = 0; j < 2000; j++)
        tree[j] = -1;

    for (j = 0; j < 10; j++)
    {
        node = rand() % 10;
        insert(tree, node);
    }
    inorder(tree, 0);
    printf("\n");

    for (j = 0; j < 5; j++)
    {
        l = rand() % 10;
        //printf("delete:%d\n",l);
        k = removal(tree, l);
        printf("Remove %d(%d)\n", l, k);
    }
    inorder(tree, 0);
    printf("\n");
}
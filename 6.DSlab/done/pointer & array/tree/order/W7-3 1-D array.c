#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
Week 7 Question 3
Description
Please finish four function in the template, inorder, preorder, postorder and levelorder.
*/
int insert(int root[2000], int node)
{
    int index = 0;
    while(index < 2000 && root[index] != -1)
    {
        if(root[index] < node)
            index = index * 2 + 2;
        else
            index = index * 2 + 1;
    }
    root[index] = node;
}

void inorder(int root[2000], int index)
{
    if(root[index] != -1 && index <  2000)
    {
        inorder(root, index*2+1);
        printf("%d ", root[index]);
        inorder(root, index*2+2);
    }
}

void preorder(int root[2000], int index)
{
    if(root[index] != -1 && index < 2000)
    {
        printf("%d ", root[index]);
        preorder(root, index*2+1);
        preorder(root, index*2+2);
    }
}

void postorder(int root[2000], int index)
{
    if(root[index] != -1 && index < 2000)
    {
        postorder(root, index*2+1);
        postorder(root, index*2+2);
        printf("%d ", root[index]);
    }
}

void inorder_counts(int root[2000], int index, int *loop_end)
{
    if(root[index] != -1)
    {
        inorder_counts(root, index*2+1, loop_end);
        (*loop_end)++;
        inorder_counts(root, index*2+2, loop_end);
    }
}
/*
void levelorder(int root[2000])
{
    int loop_end = 0;
    inorder_counts(root, 0, &loop_end);
    int *Queue[9999];
    //printf("%d \n", loop_end);

    for(int i = 0 ; i < loop_end ; i++)
        Queue[i] = NULL;

    int root_i = 0, Qi = 0, Qi_targ = 0;

    while( Qi < loop_end)
    {
        if(Qi  == 0)
        {
            Queue[Qi] = &(root[root_i]);
            Qi++;
            continue;
        }

        for(int j = 0 ; j < loop_end ; j++)
        {
            if(Queue[Qi_targ] == Queue[j])
            {
                root_i = j;
                break;
            }
        }
        if(root[root_i*2+1] != -1)
        {
            Queue[Qi] = &(root[root_i*2+1]);
            Qi++;
        }

        if(root[root_i*2+2] != -1)
        {
            Queue[Qi] = &(root[root_i*2+2]);
            Qi++;
        }

        Qi_targ++;
    }

    for( int j = 0 ; j < loop_end ; j++)
        printf("%d (%p)\n", *Queue[j], Queue[j]);

}
*/
void levelorder(int root[2000])
{
    for(int i = 0 ; i < 2000 ; i++)
    {
        if(root[i] != -1)
            printf("%d ", root[i]);
    }
}

int main()
{
    int tree[2000];
    int j, k, node;
    srand(time(NULL));

    for(j = 0; j < 2000; j ++)
        tree[j] = -1;

    for(j = 0; j < 10; j ++)
    {
        node = rand() % 100;
        printf("node:%d \n", node);
        insert(tree, node);
    }
    for( j = 0 ; j < 99 ; j++)
    {
        if(tree[j] != -1)
        printf("%d(j = %d) \t", tree[j], j);
    }

    printf("\n\n");
/*
    printf("inorder:\n");
    inorder(tree, 0);
    printf("\n");


    printf("preorder:\n");
    preorder(tree, 0);
    printf("\n");


    printf("postorder:\n");
    postorder(tree, 0);
    printf("\n");
*/

    printf("levelorder:\n");
    levelorder(tree);
    printf("\n");

}


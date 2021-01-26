//Clear vers

/*
Week 7 Question 2
Description
Please finish four function in the template, inorder, preorder, postorder and levelorder.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int insert(int root[20][4], int node)
{
    int f = 0, index = 0;
    while(root[index][0] != -1)
        index ++;
    if(index >= 20)
        return -1;
    if(index == 0)
    {
        root[0][0] = 1;
        root[0][1] = node;
        return 1;
    }
    else
    {
        root[index][0] = 1;
        root[index][1] = node;
        while(1)
        {
            if(root[f][1] < node)
            {
                if(root[f][3] == -1)
                {
                    root[f][3] = index;
                    return 1;
                }
                else
                {
                    f = root[f][3];
                }
            }
            else
            {
                if(root[f][2] == -1)
                {
                    root[f][2] = index;
                    return 1;
                }
                else
                {
                    f = root[f][2];
                }
            }
        }
    }
}

void inorder(int root[20][4], int index)
{
    if(root[index][2] != -1)
        inorder(root, (root[index][2]) );
    printf("%d ", root[index][1]);
    if(root[index][3] != -1)
        inorder(root, (root[index][3]) );
}

void preorder(int root[20][4], int index)
{
    printf("%d ", root[index][1]);
    if(root[index][2] != -1)
        preorder(root, (root[index][2]) );
    if(root[index][3] != -1)
        preorder(root, (root[index][3]) );
}

void postorder(int root[20][4], int index)
{
    if(root[index][2] != -1)
        postorder(root, (root[index][2]) );
    if(root[index][3] != -1)
        postorder(root, (root[index][3]) );
    printf("%d ", root[index][1]);

}
void levelorder(int root[20][4])
{
    int loop_end = 0, *Queue[20], left_i, right_i;
    while(root[loop_end][0] == 1)
        loop_end++;
    for(int i = 0 ; i < loop_end ; i++)
        Queue[i] = NULL;

    int root_i = 0, Qi = 0, Qi_targ = 0;
    while(Qi < loop_end)
    {
        if(Qi == 0)
        {
            Queue[Qi] = &(root[root_i][1]);
            Qi++;
            continue;
        }
/*
        for(int j = 0 ; j < loop_end ; j++)
        {
            if(Queue[Qi_targ] == &(root[j][1]))
            {
                root_i = j;
                break;
            }
        }
*/
        if(Queue[Qi_targ][1] != -1)//left child not NULL
        {
            left_i = Queue[Qi_targ][1];
            Queue[Qi] = &(root[left_i][1]);
            Qi++;
        }

        if(Queue[Qi_targ][2] != -1)//right child not NULL
        {
            right_i = Queue[Qi_targ][2];
            Queue[Qi] = &(root[right_i][1]);
            Qi++;
        }
        Qi_targ++;
    }
    for( int j = 0 ; j < loop_end ; j++)
        printf("%d (%p)\n", *Queue[j], Queue[j]);

}
int main()
{
    int tree[20][4];
    int j, k, node;
    srand(time(NULL));

    for(j = 0; j < 20; j ++)
        for(k = 0; k < 4; k ++)
            tree[j][k] = -1;

    for(j = 0; j < 10; j ++)
    {
        node = rand() % 100;
        insert(tree, node);
    }
    printf("j             value     left_i    right_i\n");
    for(j = 0; j < 25; j ++)
    {
        printf("%d  ", j);
        printf("%p   ", &(tree[j][1]));
        for(k = 1; k < 4; k ++)
        {
            printf("%d          ", tree[j][k]);
        }
        printf("\n");
    }
    printf("===========================================\n\n");


    printf("inorder:\n");
    inorder(tree, 0);
    printf("\n");
    printf("===========================================\n\n");


    printf("preorder:\n");
    preorder(tree, 0);
    printf("\n");
    printf("===========================================\n\n");


    printf("postorder:\n");
    postorder(tree, 0);
    printf("\n");
    printf("===========================================\n\n");

    printf("levelorder:\n");
    levelorder(tree);
    printf("\n");
    printf("===========================================\n\n");

}

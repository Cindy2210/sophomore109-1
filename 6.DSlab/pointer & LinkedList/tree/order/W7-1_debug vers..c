//Debug vers
/*
Week 7 Question 1
Description
Please finish four function in the template, inorder, preorder, postorder and levelorder.
*/
#include<stdlib.h>
#include<time.h>

struct Node
{
    int data, level;
    struct Node *left, *right;
};
void insert(struct Node **root, struct Node *node)
{
    if(*root == NULL)
        *root = node;
    else if(node->data > (*root)->data)
    {
        insert(&((*root)->right), node);
        node->level++;
    }
    else if(node->data <= (*root)->data)
    {
        insert(&((*root)->left), node);
        node->level++;
    }
    else
        node->level--;

}

void inorder(struct Node *root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d\t", root->data);
        printf("level:%d\n", root->level);
        inorder(root->right);
    }
}

void preorder(struct Node *root)
{
    if(root)
    {
        printf("%d\t", root->data);
        printf("level:%d\n", root->level);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root)
{
    if(root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d\t", root->data);
        printf("level:%d\n", root->level);
    }
}
void inorder_count(struct Node *root, int *counts)
{
    if(root)
    {
        //printf("in!!\n");
        inorder_count(root->left, counts);
        (*counts)++;
        inorder_count(root->right, counts);
    }
}

void levelorder(struct Node *root)
{
    if(root == NULL)
        printf("the tree is NULL!!\n");
    int *Queue[99999];
    for(int k = 0 ; k < 99999 ; k ++)
        Queue[k] = -1;
    struct Node *cur = NULL;
    int loop_end = 0;
    inorder_count(root, &loop_end);
    //printf("loop_end = %d --OK--\n\n", loop_end);


    ///queue initial
    int Qi = 0;
    Queue[Qi] = root;
    Qi++;
    if(root->left != NULL)
    {
        Queue[Qi] = root->left;
        Qi++;
    }

    if(root->right != NULL)
    {
        Queue[Qi] = root->right;
        Qi++;
    }
    int targ_i = 1;

    while(1)
    {
        if( Qi >= loop_end)
            break;

        cur = root;
        while(cur != Queue[targ_i])
        {

            if((*Queue[targ_i])> cur->data )
                cur = cur->right;
            else if( (*Queue[targ_i])<= cur->data)
                cur = cur->left;

        }


        //printf("cur = inorder_find(root, target_number);\n");
        //cur = inorder_find(root, target_number);
        //printf("inorder_find out!!!!!!!!!!!!\n");
        /*if(cur != NULL)
            printf("cur:%d(%p)(after)\n\n", cur->data, cur);

        printf("myQueue(BF):\n");
        for( int j = 0 ; j < Qi ; j++)
            printf("data:%d\t(%p) ", (*Queue[j]), Queue[j]);
        printf("\n");
        */
        if(cur)
        {
            if(cur->left)
            {
                //printf("myqueue[%d] = cur->left->data; =%d \n", Qi, cur->left->data);
                Queue[Qi] = cur->left;
                Qi++;
            }
            if(cur->right)
            {
                //printf("myqueue[%d] = cur->right->data; =%d \n", Qi, cur->right->data);
                Queue[Qi] = cur->right;
                Qi++;
            }
        }/*
        printf("after  myqueue(i = %d)\n", Qi);
        for( int j = 0 ; j < Qi ; j++)
            printf("%d(%p) ", *Queue[j], Queue[j]);
        printf("\n");
*/

        targ_i++;
        /*printf("target_i++; = %d\n", targ_i);
        printf("\n=========================================\n");
        */
    }
    printf("after  myqueue(i = %d)\n", Qi);
    for( int j = 0 ; j < Qi ; j++)
        printf("%d(%p) ", *Queue[j], Queue[j]);
    printf("\n");

}

int main()
{
    struct Node *tree = NULL, *node;
    int j;
    srand(time(NULL));
    for(j = 0; j < 10; j ++)
    {
        node = (struct Node *)malloc(sizeof(struct Node));
        node->data = rand()%10;
        printf("node->data:%d(%p)\n", node->data, node);
        node->left = NULL;
        node->right = NULL;
        node->level = 1;
        insert(&tree, node);
    }
    printf("\n");
    /*
    printf("inorder:\n");
    inorder(tree);
    printf("\n");


    printf("preorder:\n");
    preorder(tree);
    printf("\n");

    printf("postorder:\n");
    postorder(tree);
    printf("\n");
    */
    printf("levelorder:\n");
    levelorder(tree);
    printf("\n");

}

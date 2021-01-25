/*
Week 8 Question 2
Description
Please finish the two function remove and inorder in template.
Please make sure that tree still be a binary search tree after remove .
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insert(int root[20][4], int node)
{
    int f = 0, index = 0;
    while (root[index][0] != -1)
        index++;
    if (index >= 20)
        return -1;
    if (index == 0)
    {
        root[0][0] = 1;
        root[0][1] = node;
        return 1;
    }
    else
    {
        root[index][0] = 1;
        root[index][1] = node;
        while (1)
        {
            if (root[f][1] < node)
            {
                if (root[f][3] == -1)
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
                if (root[f][2] == -1)
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

int findmin(int root[20][4], int n)
{
    int place = n;
    while (root[place][2] != -1)
    {
        place = root[place][2];
    }
    return place;
}

void inorder(int root[20][4], int n)
{
    if (root[n][2] != -1)
        inorder(root, root[n][2]);

    printf("%d ", root[n][1]);

    if (root[n][3] != -1)
        inorder(root, root[n][3]);
}

/*
Function removal will remove all the node tree content data n.
The return value of function removal is a integer represent how many node are removed.
*/
int removal(int root[20][4], int n)
{
    int count = 0, nums = 0;
    for (int i = 0; 10 > i; i++)
    {
        if (root[i][1] == n)
            nums++;
    }
    while (nums > 0)
    {
        Delete(root, n);
        count++;
        nums--;
    }
    return count;
}

void Delete(int root[20][4], int n)
{
    int i = 0, j = 0, k = 0, delete_place = 0, parent = 0, LR = 0;
    for (i = 0; 10 > i; i++)
    {
        if (root[i][1] == n) //delete place
        {
            delete_place = i;
            if (delete_place != 0) //delete not root
            {
                for (j = 0; 10 > j; j++)
                {
                    if (root[j][2] == delete_place) //delete is one num left
                    {
                        parent = j; //m = delete parent
                        LR = 2;     //l = 2 is one num left
                        break;
                    }
                    else if (root[j][3] == delete_place) //delete is one num right
                    {
                        parent = j; // m =delete parent
                        LR = 3;     // LR = 3 is one num right
                        break;
                    }
                }
            }
            else
                LR = 0; // LR = 0,not anyone child; is root
            break;
        }
    }

    if (root[delete_place][2] != -1 && root[delete_place][3] != -1) //delete have two child
    {
        if (LR == 2 || LR == 3) //delete have parent,then is parent left
        {
            j = root[delete_place][3];                //delete right
            k = findmin(root, root[delete_place][3]); //delete right minnum(replace)
            if (j != k)                               //minnum not delete child
            {
                for (i = 0; 10 > i; i++)
                {
                    if (root[i][2] == k) //because k is min,so k is leftest,then have one num is minnum parent;k=minnum parent
                    {
                        root[i][2] = root[k][3]; //minnum parent left(minnum is leftest) = minnum right whatever -1 or data,then minparent left is minnum right
                        break;
                    }
                }
                root[parent][LR] = k;               //m is delete parent,because "l"=2,so m[2] = k(minnum) ,l=3, m[3] = minnum
                root[k][2] = root[delete_place][2]; //delete was replaced by minnum,so minnum have connect delete left and right
                root[k][3] = root[delete_place][3];
                for (i = 0; 4 > i; i++)
                    root[delete_place][i] = -1; //initial delete
            }
            else //minnum is delete child
            {
                root[parent][2] = k;                //delete parent left = minnum
                root[k][2] = root[delete_place][2]; //because right no child,but delete left maybe have,so connect delete left;
                for (i = 0; 4 > i; i++)
                    root[delete_place][i] = -1; //initial delete
            }
        }

        else if (LR == 0) //if delete is root
        {
            j = root[delete_place][3];          //delete right
            k = findmin(root, root[parent][3]); //minnum
            if (j != k)                         //minnum not delete child
            {
                for (i = 0; 10 > i; i++)
                {
                    if (root[i][2] == k) //find minnum parent
                    {
                        root[i][2] = root[k][3]; //minnum parent left = minnum right
                        break;
                    }
                }
                root[delete_place][1] = root[k][1]; //delete = minum

                for (i = 0; 4 > i; i++)
                {
                    root[k][i] = -1; //initial delete
                }
            }
            else
            {
                root[delete_place][1] = root[k][1]; //delete data = minnum data
                root[delete_place][3] = root[k][3]; //delete right = minnum
                for (i = 0; 4 > i; i++)
                {
                    root[k][i] = -1; //initial minnum
                }
            }
        }
    }

    else if (root[delete_place][2] == -1 && root[delete_place][3] != -1) //only right child
    {
        if (LR == 2 || LR == 3)
        {
            root[parent][LR] = root[delete_place][3]; //delete parent left or right= delete right
            for (i = 0; 4 > i; i++)
                root[delete_place][i] = -1; //initial delte
        }

        else if (LR == 0) //delete is root
        {
            k = root[delete_place][3]; //delete right
            for (i = 0; 4 > i; i++)
            {
                root[delete_place][i] = root[k][i]; //delete = delete right
                root[k][i] = -1;                    //initial delete right,because delete is robber
            }
        }
    }

    else if (root[delete_place][2] != -1 && root[delete_place][3] == -1) // only left child
    {
        if (LR == 2 || LR == 3)
        {
            root[parent][LR] = root[delete_place][2]; //delete's parent left or right = delete left
            for (i = 0; 4 > i; i++)
                root[delete_place][i] = -1; //init delete
        }

        else if (LR == 0)
        {
            k = root[delete_place][2]; //k = delete left
            for (i = 0; 4 > i; i++)
            {
                root[delete_place][i] = root[k][i]; //delete = delete left
                root[k][i] = -1;                    //init delete left
            }
        }
    }

    else //no childs
    {
        if (LR == 2 || LR == 3) //init
        {
            root[parent][LR] = -1;
            for (i = 0; 4 > i; i++)
                root[delete_place][i] = -1;
        }

        else if (LR == 0) //no child and is root
        {
            for (i = 0; 4 > i; i++)
                root[delete_place][i] = -1;
        }
    }
}

int main()
{
    int tree[20][4];
    int j, k, l, node;
    srand(time(NULL));

    for (j = 0; j < 20; j++)
        for (k = 0; k < 4; k++)
            tree[j][k] = -1;

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
        k = removal(tree, l);
        printf("Remove %d(%d)\n", l, k);
    }
    inorder(tree, 0);
    printf("\n");
}
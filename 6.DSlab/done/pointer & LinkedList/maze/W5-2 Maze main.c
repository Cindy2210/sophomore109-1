/*Week 5 Question 2
Maze
Description
Please finish the class and member function in template.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define WALL 10

struct Grid
{
    struct Grid *dir[4];
    int state;
};
typedef struct Grid Grid;

/*
function initMaze
Allocate a 2-D link list with s * s sizes as the map of maze.
Inside the maze enery gird with state 0 represent empty space and 1 represent wall.
The gird in left top is start point and right bottom is finish point.
Randomly generate 20% wall in the maze.
Make sure start point and finish point are 0

*/
Grid *mallocFn(int data)
{
    Grid *tmp = malloc(sizeof(Grid));
    tmp->state = data;
    tmp->dir[UP] = NULL;
    tmp->dir[DOWN] = NULL;
    tmp->dir[RIGHT] = NULL;
    tmp->dir[LEFT] = NULL;
    return tmp;
}
void initMaze(Grid **m, int s)
{
    int sizeWALL = s + 2;
    //����̤W������
    (*m) = mallocFn(WALL);
    Grid *topHead = (*m);
    Grid *topTail = topHead;
    Grid *lastHead = topHead;
    //Grid *head = topHead;
    for (int i = 0; i < sizeWALL - 1; i++)
    {
        Grid *newGrid_R = mallocFn(WALL);
        topTail->dir[RIGHT] = newGrid_R;
        newGrid_R->dir[LEFT] = topTail;
        topTail = topTail->dir[RIGHT];

        //�A��̥��䪺��= malloc(sizeof(Grid));

        Grid *newGrid_D = mallocFn(WALL);

        lastHead->dir[DOWN] = newGrid_D;
        newGrid_D->dir[UP] = lastHead;
        lastHead = lastHead->dir[DOWN];
    }
    (*m)->dir[RIGHT] = topHead->dir[RIGHT];
    (*m)->dir[DOWN] = topHead->dir[DOWN];
    /*
        int counts = 0;
        Grid *tmp = topHead;
        while(tmp != NULL)
        {
            counts++;
            tmp = tmp->dir[RIGHT];
        }
        printf("%d\n", counts);
    */
    ///��������0
    Grid *cur_d = topHead;
    Grid *cur_r = topHead;
    Grid *next_r = topHead->dir[DOWN];
    for (int i = 0; i < sizeWALL - 1; i++)
    {
        cur_r = cur_d;
        next_r = cur_d->dir[DOWN];
        for (int j = 0; j < sizeWALL - 1; j++)
        {

            Grid *newGrid_R = mallocFn(0);
            newGrid_R->dir[UP] = cur_r->dir[RIGHT];
            cur_r->dir[RIGHT]->dir[DOWN] = newGrid_R;
            newGrid_R->dir[LEFT] = next_r;
            next_r->dir[RIGHT] = newGrid_R;

            cur_r = cur_r->dir[RIGHT];
            next_r = next_r->dir[RIGHT];
        }

        cur_d = cur_d->dir[DOWN];
    }

    //�̤U��M�̥k��]��WALL
    struct Grid *lastTail = lastHead;
    struct Grid *downPtr = topTail;
    while (lastTail != NULL)
    {
        lastTail->state = 10;
        downPtr->state = 10;
        lastTail = lastTail->dir[RIGHT];
        downPtr = downPtr->dir[DOWN];
    }
    ///�[�J20%�����
    int wall = s * s * (0.2);
    srand(time(NULL));
    //    srand(5);

    Grid *start = topHead->dir[RIGHT]->dir[DOWN];
    for (int i = 0; i < wall; i++)
    {
        Grid *change = start;
        int row = rand() % s;
        int col = rand() % s;
        for (int j = 0; j < row; j++)
            change = change->dir[RIGHT];
        for (int k = 0; k < col; k++)
            change = change->dir[DOWN];
        if (change->state != 10)
            change->state = 10;
        else
            i--;
    }
}

/*
function findPath
This function will find a path between start point and finish point.
Return a list content the path information inside.
If there is no path between two point then the list will be empty.

*/
struct List
{
    struct Grid *data[SIZE * SIZE];
    int top;
};
typedef struct List List;
/*
Insert an element from top
*/
void addElement(List *l, Grid *g)
{
    if (l->top == SIZE * SIZE)
    {
        printf("add fail!!\n");
        return;
    }
    l->data[l->top] = g;
    l->top++;
}

/*
remove an element from top and return a pointer point to the element.
If list is empty, return NULL.
*/
Grid *removeElement(List *l)
{
    if (l == NULL)
        return NULL;
    Grid *tmp = malloc(sizeof(Grid));
    l->top--;
    tmp = l->data[l->top];
    return tmp;
}

List *findPath(Grid *m)
{
    ///initialize path
    List *path = malloc(sizeof(List));
    path->top = 0;

    Grid *start = m->dir[RIGHT]->dir[DOWN];
    //printf("%d(%p)\n", start->state, start);
    Grid *end = m;
    for (int i = 0; i < SIZE; i++) ///go right
        end = end->dir[RIGHT];
    for (int i = 0; i < SIZE; i++) ///go down
        end = end->dir[DOWN];
    //printf("%d(%p)\n", end->state, end);

    int first = 0, success = 0;

    while (1)
    {
        //getch();
        if (first && path->top == 0 && start->dir[RIGHT]->state != 0 && start->dir[DOWN]->state != 0 && start->dir[LEFT]->state != 0 && start->dir[UP]->state != 0)
            break;

        if (start == end)
        {
            success = 1;
            break;
        }

        int flag = 0;
        if (start->dir[RIGHT]->state == 0 && flag == 0)
        {
            start->state = RIGHT + 1;
            addElement(path, start);
            start = start->dir[RIGHT];
            flag = 1;
        }
        if (start->dir[DOWN]->state == 0 && flag == 0)
        {
            start->state = DOWN + 1;
            addElement(path, start);
            start = start->dir[DOWN];
            flag = 1;
        }
        if (start->dir[LEFT]->state == 0 && flag == 0)
        {
            start->state = LEFT + 1;
            addElement(path, start);
            start = start->dir[LEFT];
            flag = 1;
        }
        if (start->dir[UP]->state == 0 && flag == 0)
        {
            start->state = UP + 1;
            addElement(path, start);
            start = start->dir[UP];
            flag = 1;
        }

        if (flag == 0)
        {
            start->state = 9;
            Grid *backRoad = removeElement(path);
            //printf("(row:%d)(col:%d)\n", tmp->row, tmp->col);
            start = backRoad;
        }
        if (!first)
            first++;

        printf("\n------------------------------------------------------\n");
        for (int i = 0; i < path->top; i++)
            printf("i:%d %d (%p)\n", i, path->data[i]->state, path->data[i]);

        printf("\n------------------------------------------------------\n");
        printMaze(m);
        /*
        Grid *j = m, *k;
        while(j != NULL)
        {
            k = j;
            while(k != NULL)
            {
                //  printf("%d(%p) ", k->state, k);
                printf("%d\t", k->state);
                k = k->dir[RIGHT];
            }
            printf("\n");
            j = j->dir[DOWN];
        }*/
        printf("\n------------------------------------------------------\n");
    }
    if (success)
    {
        printf("success\n\n");
        return path;
    }
    else
    {
        printf("Fail~!\n");
        return NULL;
    }
}

void printPath(List *l)
{
    if (l == NULL)
        return;
    int j;
    for (j = 1; j < l->top; j++)
    {
        if (l->data[j] == l->data[j - 1]->dir[UP])
        {
            printf("UP\n");
        }
        else if (l->data[j] == l->data[j - 1]->dir[DOWN])
        {
            printf("DOWN\n");
        }
        else if (l->data[j] == l->data[j - 1]->dir[LEFT])
        {
            printf("LEFT\n");
        }
        else if (l->data[j] == l->data[j - 1]->dir[RIGHT])
        {
            printf("RIGHT\n");
        }
    }
}

void printMaze(Grid *m)
{
    Grid *j = m, *k;
    while (j != NULL)
    {
        k = j;
        while (k != NULL)
        {
            //printf("%d(%p) ", k->state, k);
            switch (k->state)
            {
            case 0:
                printf(" ");
                break;
            case 9:
                printf("/");
                break;
            case 1:
                printf("^");
                break;
            case 2:
                printf("v");
                break;
            case 3:
                printf("<");
                break;
            case 4:
                printf(">");
                break;
            default:
                printf("*");
                break;
            }
            k = k->dir[RIGHT];
        }
        printf("\n");
        j = j->dir[DOWN];
    }
}

int main()
{
    Grid *maze = NULL;
    initMaze(&maze, SIZE);
    printMaze(maze);
    printPath(findPath(maze));
    return 0;
}

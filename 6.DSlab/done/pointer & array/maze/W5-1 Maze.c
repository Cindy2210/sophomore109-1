/*
Week 5 Question 1
Maze
Description
Please finish the class and member function in template.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define WALL 10

#define RT 5
#define DN 6
#define LT 7
#define UP 8

#define SIZE 10

struct Node
{
    int row, col;
};
typedef struct Node Node;
/*
function initMaze
Alocate a 2-D array with s * s sizes as the map of maze.
Inside the maze where 0 represent empty space and 1 represent wall.
[0][0] is start point and [s - 1][s - 1] is finish point.
Randomly generate 20% wall in the maze.
Make sure [0][0] and [s - 1][s - 1] are 0

*/
void initMaze(int ***m, int s)
{
    int i;
    *m = (int **)malloc(sizeof(int *) * (s + 2));
    int *tmp = malloc(sizeof(int) * (s + 2) * (s + 2));

    for (i = 0; i < (s + 2) * (s + 2); i++)
        tmp[i] = 0;
    for (i = 0; i < (s + 2); i++)
    {
        tmp[i] = WALL;                               ///TopWall
        tmp[i * (SIZE + 2)] = WALL;                  ///LeftWall
        tmp[i * (SIZE + 2) + (SIZE + 2 - 1)] = WALL; ///RightWALL
        tmp[(SIZE + 2 - 1) * (SIZE + 2) + i] = WALL; ///DownWALL
    }

    int wall = s * s * (0.3);
    //printf("wall:%d\n", wall);
    //    srand(10);
    srand(time(NULL));
    //int times = 0;
    for (i = 0; i < wall; i++)
    {
        //times++;
        int row = rand() % (s + 2);
        int col = rand() % (s + 2);
        //printf("R:%d C:%d\n", row, col);
        if ((row == 1 && col == 1) || (row == s && col == s))
            wall++;
        else if (tmp[(s + 2) * row + col] == WALL)
            i--; //== wall++
        else
            tmp[(s + 2) * row + col] = WALL;
    }
    // printf("times:%d\n", times);

    for (i = 0; i < (s + 2); i++)
        (*m)[i] = &tmp[(s + 2) * i];
}

void printMaze(int *m[SIZE])
{
    int j, k;
    for (j = 0; j < SIZE + 2; j++)
    {
        for (k = 0; k < SIZE + 2; k++)
        {
            if (m[j][k] == 0)
                printf(" ");
            else if (m[j][k] == 10)
                printf("*");
            else if (m[j][k] == 5)
                printf(">");
            else if (m[j][k] == 6)
                printf("v");
            else if (m[j][k] == 7)
                printf("<");
            else if (m[j][k] == 8)
                printf("^");
            else if (m[j][k] == 9)
                printf(" ");
        }
        printf("\n");
    }
}

struct List
{
    Node data[SIZE * SIZE];
    int top;
};
typedef struct List List;
/*
Insert an element from top
*/

void addElement(List *l, int r, int c)
{
    //[r*SIZE + c]
    l->data[l->top].row = r;
    //printf("l->data[l->top].row = r;\n");
    l->data[l->top].col = c;
    //printf("l->data[l->top].col = c;\n");
    l->top++;
    //printf("l->top++;\n");
    //(*flag) = 0;
}

/*
remove an element from top and return a pointer point to the element.
If list is empty, return NULL.*/
Node *removeElement(List *l)
{
    if (l == NULL)
        return NULL;
    Node *tmp = malloc(sizeof(Node));
    *tmp = l->data[l->top - 1];
    //printf("tmp =  l->data[l->top];\n");
    //printf("(row:%d)(col:%d)\n", tmp->row, tmp->col);
    l->top--;
    //printf("l->top--\n");
    //printf("return l->data[tmp_i];\n");
    return tmp;
    /*
        if( *control == RT)
            *control = DN;
        else if( *control == DN)
            *control = LT;
        else if( *control == LT)
            *control = UP;
        else if( *control == UP)
            *control = LT;*/
}
/*          function findPath
This function will find a path between start point and finish point.
Return a queue content the path information inside.
If there is no path between two point then the queue will be empty.
*/
List *findPath(int **m, int s)
{
    List *path = malloc(sizeof(List));

    //int row = 1;
    //int col = 1;
    //printf("%d \n", (*m)[row*SIZE+col]);///10

    ///initialize
    path->top = 0;
    //printf("%d\n", path->top);
    int row = 1;
    int col = 1;
    int first = 0;
    int success = 0;

    while (1)
    {

        getch();
        /*        printf("\n======================================================\n");
        printf("ROW:%d\tCOL:%d\n", row, col);
        printf("top:%d\tR:%d C:%d\n", path->top, path->data[path->top-1].row, path->data[path->top-1].col);
//        printf("%d ", m[row][col]);
        printf("now:%d\n\n", (*m)[row*(SIZE+2)+col]);
        printf("\n-------------------------------------------------------\n");
*/
        if (first && path->top == 0 && m[row - 1][col] != 0 && m[row + 1][col] != 0 && m[row][col - 1] != 0 && m[row][col + 1] != 0)
        {
            break;
        }

        if (row == 10 && col == 10)
        {
            success = 1;
            //printf("SUCCESS\n");
            break;
        }

        int flag = 0;

        if (m[row][col + 1] == 0 && flag == 0) ///goRight
        {
            //printf("goRight\n");
            m[row][col] = RT;
            addElement(path, row, col);
            //printf("m[row][col]:%d(row:%d)(col:%d)\n", m[row][col], row, col);
            col++;
            flag = 1;
        }
        if (m[row + 1][col] == 0 && flag == 0) ///goDown
        {
            //printf("goDown\n");
            m[row][col] = DN;
            addElement(path, row, col);
            //printf("m[row][col]:%d(row:%d)(col:%d)\n", m[row][col], row, col);
            row++;
            flag = 1;
        }
        if (m[row][col - 1] == 0 && flag == 0) ///goLeft
        {
            //printf("goLeft\n");
            m[row][col] = LT;
            addElement(path, row, col);
            //printf("m[row][col]:%d(row:%d)(col:%d)\n", m[row][col], row, col);
            col--;
            flag = 1;
        }
        if (m[row - 1][col] == 0 && flag == 0) ///goUp
        {
            //printf("goUp\n");
            m[row][col] = UP;
            addElement(path, row, col);
            //printf("m[row][col]:%d(row:%d)(col:%d)\n", m[row][col], row, col);
            row--;
            flag = 1;
        }
        if (flag == 0) ///all direction has no road
        {
            //printf("flag == 0\n");
            m[row][col] = 9;
            Node *backRoad = removeElement(path);
            //printf("(row:%d)(col:%d)\n", tmp->row, tmp->col);
            row = backRoad->row;
            col = backRoad->col;
        }
        if (!first)
            first++;

        printf("\n------------------------------------------------------\n");
        printMaze(m);
        /*        for(int j = 0; j < SIZE+2; j ++)
        {
            for(int k = 0; k < SIZE+2; k ++)
            {
                printf("%d\t", m[j][k]);
            }
            printf("\n");
        }
*/
        /*
        printf("\n------------------------------------------------------\n");

        for(int i = 0 ; i < path->top ; i++)
            printf("(i:%d)row:%d\tcol:%d\n", i, path->data[i].row, path->data[i].col);
        printf("\n------------------------------------------------------\n");

        printf("ROW:%d\tCOL:%d\n", row, col);
        printf("top:%d\tR:%d C:%d\n", path->top, path->data[path->top-1].row, path->data[path->top-1].col);
//        printf("%d ", m[row][col]);
        printf("now:%d\n\n", (*m)[row*(SIZE+2)+col]);



*/
        //printf("\n======================================================\n");
    }
    if (success)
    {
        printf("success\n");
        return path;
    }
    else
    {

        printf("fail\n");
        return NULL;
    }
    /*
        while(row != SIZE && col != SIZE) //�X�f
        {
            printf("ROW:%d\tCOL:%d\n", row, col);
            printf("top:%d\tR:%d C:%d\n", path->top, path->data[path->top-1].row, path->data[path->top-1].col);
            printf("%d ", m[row][col]);
            printf("now:%d\n\n", (*m)[row*(SIZE+2)+col]);

            for(int i = 0 ; i < path->top ; i++)
                printf("(i:%d)row:%d\tcol:%d\n", i, path->data[i].row, path->data[i].col);
            getch();

            if( (*m)[row*(SIZE+2)+col] == WALL )
            {
                printf("WALL\n");
                removeElement( path);
                row = path->data[path->top].row;
                col = path->data[path->top].col;
            }




            addElement(path, row, col);
            for(int j = 0; j < SIZE+2; j ++)
            {
                for(int k = 0; k < SIZE+2; k ++)
                {
                    printf("%d\t", m[j][k]);
                }
                printf("\n");
            }

        }
        printf("\n-----------------out while------------------------\n");*/
}

void printPath(List *l)
{
    if (l == NULL)
        return;
    int j;
    for (j = 0; j < l->top; j++)
    {
        printf("(%d, %d) \n", l->data[j].row, l->data[j].col);
    }
}

int main()
{
    int **maze;
    initMaze(&maze, SIZE);
    printMaze(maze);
    printPath(findPath(maze, SIZE));
    printMaze(maze);
    return 0;
}

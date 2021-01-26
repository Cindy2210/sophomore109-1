/*Week 5 Question 2
partially test
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#include<conio.h>

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
    tmp->dir[0] = NULL;
    tmp->dir[1] = NULL;
    tmp->dir[2] = NULL;
    tmp->dir[3] = NULL;

    return tmp;
}
void initMaze(Grid **m, int s)
{
    int sizeWALL = s+2;
    //����̤W������
    *m = mallocFn(WALL);
    Grid *topHead = m;
    Grid *topTail = topHead;
    Grid *lastHead = topHead;
    printf("123\n");
    //Grid *head = topHead;
    for(int i = 0 ; i < sizeWALL-1 ; i++)
    {
        printf("!!\n");
        Grid *newGrid_R = mallocFn( WALL );
        printf("!!\n");


        topTail->dir[RIGHT] = newGrid_R;
        newGrid_R->dir[LEFT] = topTail;
        topTail = topTail->dir[RIGHT];

        Grid *newGrid_D = mallocFn(WALL);

        lastHead->dir[DOWN] = newGrid_D;
        newGrid_D->dir[UP] = lastHead;
        lastHead = lastHead->dir[DOWN];
    }
    (*m)->dir[RIGHT] = topHead->dir[RIGHT];
    (*m)->dir[DOWN] = topHead->dir[DOWN];
    printf("!!\n");

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
    for(int i = 0 ; i < sizeWALL-1 ; i++)
    {
        cur_r = cur_d;
        next_r = cur_d->dir[DOWN];
        for(int j = 0 ; j < sizeWALL-1 ; j++)
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

    
    struct Grid *lastTail = lastHead;
    struct Grid *downPtr = topTail;
    while(lastTail != NULL)
    {
        lastTail->state = WALL;
        downPtr->state = WALL;
        lastTail = lastTail->dir[RIGHT];
        downPtr = downPtr->dir[DOWN];
    }
    ///�[�J20%�����
    int wall = s*s*(0.2);
    srand(time(NULL));
//    srand(1);

    Grid *start = topHead->dir[RIGHT]->dir[DOWN];
    for(int i = 0 ; i < wall ; i++)
    {
        Grid *change = start;
        int row = rand() % s;
        int col = rand() % s;
        for(int j = 0 ; j < row ; j++)
            change = change->dir[RIGHT];
        for(int k = 0 ; k < col ; k++)
            change = change->dir[DOWN];
        if(change->state != 10)
            change->state = 10;
        else
            i--;
    }

}

void printMaze(Grid *m)
{
    Grid *j = m, *k;
    while(j != NULL)
    {
        k = j;
        while(k != NULL)
        {
            //printf("%d(%p) ", k->state, k);
            printf("%d\t", k->state);
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
    return 0;
}


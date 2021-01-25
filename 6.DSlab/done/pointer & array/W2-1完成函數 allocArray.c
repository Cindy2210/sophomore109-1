/*
Week 2 Question 1

Description
Please finish the function allocArray
This function will allocate a 2-D array with size m * n, 
then point the array using pointer p.

#include
#include
void allocArray(int ***p, int m, int n)
{
}

int main()
{
  int **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      printf("%p ", &(array[j][k]));
}

You will get 80 point if you can successfully allocate a 2-D array.
You will get 100 point if you can allocate consecutive memory for this 2-D array.
*/

#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n)///m is row, n is column
{
    int i ;
    *p = (int**)malloc(sizeof (int*)*m);
    int *tmp = malloc(sizeof (int)*m*n );
    for( i = 0 ; i < m ; i++)
        (*p)[i] = &tmp[n*i];

    return;
}
///pointer uses two-dimensional array
///Configure a two-dimensional dynamic array
///Configure a continuous memory(16bytes)
int main()
{
    int **array, *a;
    int j, k;
    allocArray(&array, 5, 10);
    for(j = 0; j < 5; j ++)
        for(k = 0; k < 10; k ++)
            array[j][k] = j * 10 + k;

    for(j = 0; j < 5; j ++)
    {
        for(k = 0; k < 10; k ++)
            printf("%p ", &(array[j][k]));
        printf("\n");
    }
}

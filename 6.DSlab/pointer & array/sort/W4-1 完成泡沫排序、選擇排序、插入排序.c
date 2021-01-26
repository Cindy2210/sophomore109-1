#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10

/*

Week 4 Question 1

Description
Please finish the three sorting function in template, bubble sort, selection sort and insertion sort.
You will get 80 point if you finish one of three, 90 point if two and 100 point for all three.
*/

void bubbleSort(int *array, int n)
{
    int i, j, k;
    for( i = 0 ; i < n-1 ; i++)
    {
        /*��ƨ�����A�p���b�e*/
        int flag = 0;

        for( j = 0 ; j < n-i-1 ; j++)
        {
            /*��j��j+1����Ƥ���A��j����� > j+1 �ɡB���*/
            if(array[j] > array[j+1])
            {
                flag = 1;
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
            /*Dedugging--------------
                        printf("#%d pass: \n", i+1);
                        printf("\t#%d compare: ", j+1);
                        for( k = 0 ; k < n-i ; k++)
                        {
                            //�C��compare�x��ƶq�|�H��i++�ӻ���A�G�j��H��-i�������I
                            printf("%d ",array[k]);
                        }
                        printf("\n");
                        */
        }
        /*Dedugging--------------
        printf("#final array: ");
        for( k = 0 ; k < n ; k++)
        {
            printf("%d ",array[k]);
        }
        printf("\n-------------------------------------------------------------------------\n\n");
        */
        if(flag == 0)
            break;
    }
}
void selectionSort(int *array, int n)
{
    int base, min_index, i;
    for(base = 0 ; base < n-1 ; base++)
    {
        min_index = base;
        for( i = base+1 ; i < n ; i++)
        {
            if(array[min_index] > array[i])
                min_index = i;
        }
        int temp = array[min_index];
        array[min_index] = array[base];
        array[base] = temp;
    }
    /*
    for( i = 0 ; i < n ; i++)
        printf("%d ", array[i]);
    printf("\n");
    */
}
void insertionSort(int *array, int n)
{
    int insert_i, insert_n, cp_i, i;

    for( insert_i = 1 ; insert_i < n ; insert_i++)
    {
        int insert_n = array[insert_i];
        //printf("insert_n = %d \n", insert_n);

        for( cp_i = insert_i-1 ; cp_i>=0 && array[cp_i] >= insert_n; cp_i--)
        {
            array[cp_i+1] = array[cp_i];

        }
        array[cp_i+1] = insert_n;
        /*printf("#%d insertion: ", insert_i);
        for( i = 0 ; i  < n ; i++)
        {
            printf("%d ", array[i]);
        }
        printf("\n\n");
        */
    }

}


int main()
{
    int array[SIZE];
    int j, k;
    srand(time(NULL));

    printf("BUBBLE SORT\n");
    for(j = 0; j < SIZE; j ++)
        array[j] = rand();

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n");

    bubbleSort(array, SIZE);

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n\n");



    printf("INSERTION SORT\n");
    for(j = 0; j < SIZE; j ++)
        array[j] = rand();

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n");

    insertionSort(array, SIZE);

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n\n");



    printf("SELECTION SORT\n");
    for(j = 0; j < SIZE; j ++)
        array[j] = rand();

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n");

    selectionSort(array, SIZE);

    for(j = 0; j < SIZE; j ++)
        printf("%d ", array[j]);
    printf("\n");



}


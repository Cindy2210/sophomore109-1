/*
Week 2 Question 3
Description

Please finish function enqueue and dequeue
Function enqueue will insert the data from the top of queue and return 1 on success, return -1 if not.
Function dequeue will remove one data from the bottom of queue and return a pointer point the data, return NULL if there are on data.

#include<stdio.h>
#include<string.h>
#define SIZE 100

struct Queue
{
    int data[SIZE];
    int top, bot;
};
int enqueue(struct Queue *queue, int data)
{
}
int *dequeue(struct Queue *queue)
{
}
int main()
{
    int data, *temp;
    char command[50];
    struct Queue queue;
    queue.top = 0;
    queue.but = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(enqueue(&queue, data) == 1)
            {
                printf("Successfully enqueue data %d into queue.\n");
            }
            else
            {
                printf("Failed to enqueue data into queue.\n");
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = dequeue(&queue);
            if(temp == NULL)
            {
                printf("Failed to dequeue a data from queue.\n");
            }
            else
            {
                printf("Dequeue data %d from queue.\n", *temp);
            }
        }
    }
}
You can get 80 point if you finish this two function.
You can get 100 point if you queue iscircularity.

*/
#include<stdio.h>
#include<string.h>

#define SIZE 3

struct Queue
{
    int data[SIZE];
    int top, bot;
    int length;
};

int enqueue(struct Queue *queue, int data)
{
    if(queue->length == SIZE ) ///means full
        return (-1);


    queue->data[(queue->bot)] = data;
    queue->bot++;
    queue->length++;///����e�����סA�]��enqueue,�ҥH����+1
    if( queue->bot == SIZE)
        queue->bot = 0;
    return(1);
}

int *dequeue(struct Queue *queue)
{
    if(queue->length == 0)///means empty
        return NULL;

    int temp = queue->top;
    queue->top++;
    queue->length--;///����e�����סA�]��dequeue,�ҥH����-1
    if(queue->top == SIZE)
        queue->top = 0;
    return &(queue->data[temp]);

}

int main()
{
    int data, *temp;
    char command[50];
    struct Queue queue;
    queue.top = 0;
    queue.bot = 0;
    queue.length = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(enqueue(&queue, data) == 1)
            {
                printf("Successfully enqueue data %d into queue.\n");
            }
            else
            {
                printf("Failed to enqueue data into queue.\n");
            }
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = dequeue(&queue);
            if(temp == NULL)
            {
                printf("Failed to dequeue a data from queue.\n");
            }
            else
            {
                printf("Dequeue data %d from queue.\n", *temp);
            }
        }/*
        printf("\n");
        for(int i = 0 ; i < SIZE ; i++)
            printf("i:%d data:%d\n", i, queue.data[i]);
        printf("TOP:%d   BOT:%d   leng:%d\n========================\n", queue.top, queue.bot, queue.length);
    */
    }
}

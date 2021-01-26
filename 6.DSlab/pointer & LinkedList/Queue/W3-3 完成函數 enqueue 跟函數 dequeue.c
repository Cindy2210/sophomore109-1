/*
Week 3 Question 3

Description
Please finish function enqueue and dequeue
Function enqueue will insert the data from the top of queue and return 1 on success, return -1 if not.
Function dequeue will remove one data from the bottom of queue and return a pointer point the data, return NULL if there are on data.

You can get 100 point if you finish this two function.
*/
#include<stdio.h>
#include<string.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *top, *bot;
};

int enqueue(struct Queue *queue, int data)
{
   struct Node *newnode = malloc(sizeof(struct Node));//�ؤ@�ӷs�`�I�s�J��C���
    newnode->data = data;
    newnode->next = NULL;

    if(queue->top == NULL)
    {
        /*�Ytop��null�A���ܬ��Ĥ@�Ӷ�J��C����*/
        queue->top = newnode;
        queue->bot = newnode;
    }
    else
    {
        queue->bot->next =  newnode;
        queue->bot = newnode;
    }
    return 1;
}


int *dequeue(struct Queue *queue)//���\�N�^�ǫ��V�Ӹ�ƪ�����
{
    if(queue->top == NULL)
        return NULL;
    else
    {
        struct Node *deq;
        deq = queue->top;
        queue->top = queue->top->next;
        return deq;
    }
}


int main()
{
    int data, *temp;
    char command[50];
    struct Queue queue;
    queue.top = NULL;
    queue.bot = NULL;

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
                printf("Successfully enqueue data %d into queue.\n", data);
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

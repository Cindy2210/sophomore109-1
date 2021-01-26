/*
Week 2 Question 2
Description

Please finish two function push and pop
Function push will push the data into stack and return 1 if success, 
return -1 if not.
Function pop will pop the top data from stack and 
return a pointer point to the data, 
return NULL if there is no data.

#include <stdio.h>
#include <string.h>
#define SIZE 100

struct Stack
{
    int data[SIZE];
    int top;
};

int push(struct Stack *stack, int data)
{
}

int *pop(struct Stack *stack)
{
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.top = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if(push(&stack, data) == 1)
            {
                printf("Successfully push data %d into stack.\n");
            }
            else
            {
                printf("Failed to push data into stack.\n");
            }
        }
        else if(strcmp(command, "pop") == 0) 
        {
            temp = pop(&stack);
            if(temp == NULL)
            {
                printf("Failed to pop a data from stack.\n");
            }
            else
            {
                printf("Pop data %d from stack.\n", *temp);
            }
        }
    }
}
You can get 100 point if finish this two function.
*/
#include <stdio.h>
#include <string.h>
#define SIZE 3

struct Stack
{
    int data[SIZE];
    int top;
    int length;
};

int push(struct Stack *stack, int data)///�^��int  �F��Jstack����m,�ƭ�
{

    if((stack->length) == SIZE)
    {
        return -1 ;
    }
    else
    {
        stack->top++;
        stack->length++;
        stack->data[(stack->top)] = data;
        return 1 ;
    }
}

int *pop(struct Stack *stack)///�^�ǫ��Ц�m
{
    if(stack->length == 0)
    {
        return NULL;
    }
    else
    {
        int tmp = stack->top;
        stack->top--;
        stack->length--;
        return &(stack->data[tmp]);
    }
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.top = -1;
    stack.length = 0;
    while(1)
    {
        scanf("%s", command);
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);

            if(push(&stack, data) == 1)
            {
                printf("Successfully push data %d into stack.\n");
            }
            else
            {
                printf("Failed to push data into stack.\n");
            }
        }
        else if(strcmp(command, "pop") == 0)
        {
            temp = pop(&stack);
            if(temp == NULL)
            {
                printf("Failed to pop a data from stack.\n");
            }
            else
            {
                printf("Pop data %d from stack.\n", *temp);
            }
        }
    }
}

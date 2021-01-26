/*
Week 3 Question 2
Description

Please finish two function push and pop
Function push will push the data into stack and return 1 if success, return -1 if not.
Function pop will pop the top data from stack and return a pointer point to the data, return NULL if there is no data.

You can get 100 point if finish this two function.
*/

#include<stdio.h>
#include<string.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *head, *top;
};

int push(struct Stack *stack, int data)
{
    /*�t�m�s�`�I���O����*/
    struct Node *newnode = malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->next = NULL;

    if( stack->top == NULL)
        {
            stack->head = newnode;
            stack->top = newnode;

        }
        else
        {
            newnode->next = stack->top;//�s�`�I���V���|������
            stack->top = newnode;//�s�`�I�������|������
        }
    return 1;
}

int *pop(struct Stack *stack)
{
    struct Node *pop_ptr;
    pop_ptr = stack->top;
    if( pop_ptr != NULL)
    {
        stack->top = stack->top->next;
        return pop_ptr;
    }
    else
        return NULL;
}

int main()
{
    int data, *temp;
    char command[50];
    struct Stack stack;
    stack.head = NULL;
    stack.top = NULL;
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

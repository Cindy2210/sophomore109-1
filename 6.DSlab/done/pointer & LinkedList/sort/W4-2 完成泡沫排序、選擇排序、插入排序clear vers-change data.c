//clear vers.
/*
Week 4 Question 2

Description
Please finish the three sorting function in template, bubble sort, selection sort and insertion sort.
You will get 80 point if you finish one of three, 90 point if two and 100 point for all three.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10

struct Node
{
	int data;
	struct Node *pre, *next;
};


void bubbleSort(struct Node **head)
{
    struct Node *right, *curt, *sorted;
    right = (*head)->next;
    curt = (*head);
    sorted = (*head);
    int flag = 0;
    while(sorted->next != NULL)
        sorted = sorted->next;

    //change data
    while(sorted != NULL)
    {
        while(right != NULL)
        {
            if( curt->data > right->data )
            {
                int temp = curt->data;
                curt->data = right->data;
                right->data = temp;
            }
            if(right->next == NULL)
                right = NULL;
            else
            {
                right = right->next;
                curt = curt->next;
            }
        }
        curt = (*head);
        right = (*head)->next;
        if( flag == 0)
            flag = 1;
        else
            sorted = sorted->pre;
    }
}


void selectionSort(struct Node **head)
{
    if(*head == NULL)
        return NULL;

    struct Node *unsorted = *head;//�}�l��̤p�Ȫ��Y
    struct Node *sorted = *head;//�ƧǦn�x�a��
    struct Node *find_min_p = unsorted;//�M��n�洫���̤p��
    struct Node *min_p = find_min_p;

    while(unsorted != NULL)
    {
        find_min_p = unsorted;
        min_p = find_min_p;

        while(1)
        {
            if(unsorted == NULL)
                return;
            if(min_p->data > find_min_p->data)
                min_p = find_min_p;

            if(find_min_p->next == NULL)
                break;
            find_min_p = find_min_p->next;

        }

        int tmp = min_p->data;
        min_p->data = unsorted->data;
        unsorted->data = tmp;


        if(unsorted != *head)
            sorted = sorted->next;
        unsorted = unsorted->next;
    }
}


void insertionSort(struct Node **head)
{
    struct Node *cou = (*head);
    int counts = 0;
    while(cou != NULL)
    {
        counts++;
        cou = cou->next;
    }

    struct Node *left, *targ, *unsort;
    if((*head)->next->data < (*head)->data)
    {
        int tmp = (*head)->next->data;
        (*head)->next->data = (*head)->data;
        (*head)->data = tmp;
    }

    targ = (*head)->next->next;//�n���J����
    left = targ->pre;
    unsort = targ;//�s�@�U�٨S�ܦ�target����

    for(int i = 1 ; i< counts-1 ; i++)
    {
        targ = unsort;
        left = targ->pre;
        int tmp = targ->data;
        while(tmp < left->data && left != NULL)
        {
            targ->data = left->data;
            targ = targ->pre;
            if(left->pre == NULL)
                break;
            left = left->pre;
        }
        targ->data = tmp;
        unsort = unsort->next;
    }
}


int main()
{
	int j;
	struct Node *head, *buf, *cur;

	srand(time(NULL));

	head = NULL;
	for(j = 0;j < SIZE;j ++)
	{
		buf = (struct Node *)malloc(sizeof(struct Node));
		buf->data = rand();
		buf->next = head;
		buf->pre = NULL;
		if(head != NULL)
			head->pre = buf;
		head = buf;
	}

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	bubbleSort(&head);

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	head = NULL;
	for(j = 0;j < SIZE;j ++)
	{
		buf = (struct Node *)malloc(sizeof(struct Node));
		buf->data = rand();
		buf->next = head;
		buf->pre = NULL;
		if(head != NULL)
			head->pre = buf;
		head = buf;
	}

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	selectionSort(&head);

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	head = NULL;
	for(j = 0;j < SIZE;j ++)
	{
		buf = (struct Node *)malloc(sizeof(struct Node));
		buf->data = rand();
		buf->next = head;
		buf->pre = NULL;
		if(head != NULL)
			head->pre = buf;
		head = buf;
	}

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	insertionSort(&head);

	cur = head;
	while(cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

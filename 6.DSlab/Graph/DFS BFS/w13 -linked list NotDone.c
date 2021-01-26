#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define white 0;
#define gray 1;
#define black 2;


struct Vertex
{
	struct Edge *edgeList[100];
	int edgeCount;
	int id;
};

struct Edge
{
	struct Vertex *end[2];
	int w;
};

struct Node 
{
	int coler;///white 0, gray 1, black 2;
	struct Vertex *predecessor;
};
struct List
{
	struct Node *head, *tail, *front, *now;
};

struct nodeQueue 
{
	struct Vertex *data;
    struct Node *next;
};
struct Queue 
{
	struct nodeQueue *top, *bot;
};
/*
void enqueue(struct Queue *queue, struct Vertex *v, int j)
{
   	struct nodeQueue *newnode = malloc(sizeof(struct nodeQueue));//建一個新節點存入佇列資料
    newnode->data = v[j];
    newnode->next = NULL;

    if(queue->top == NULL)
    {
        //若top為null，表示為第一個塞入佇列的值
        queue->top = newnode;
        queue->bot = newnode;
    }
    else
    {
        queue->bot->next =  newnode;
        queue->bot = newnode;
    }
    //return 1;
	return;
}


int* dequeue(struct Queue *queue)//成功就回傳指向該資料的指標
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
*/
/*
void initBFS(struct Queue*queue, struct Vertex *v)
{
	for(int i = 0 ; i < 10 ; i++)
		enqueue(queue, v, i);


}*/
/*
void BFS(struct Vertex *v)
{
	struct Queue queue;
	queue.top = NULL;
	queue.bot = NULL;
	initBFS(&queue, v);
	
}

void DFS(struct Vertex *v)
{
}
*/
void print(struct Vertex v[10])
{
	int j, k;
	for(int j = 0; j < 10; j ++)
    {
        printf("id:%d(%p) (J:%d):\n", v[j].id, &v[j].id, j);
        for(int k = 0; k < v[j].edgeCount; k ++)
        {
            printf("edge--(k:%d)\tv[j].edgeList[k]:(%p)\t\t", k,  v[j].edgeList[k]);
            if(v[j].edgeList[k]->end[0] == &v[j])
            {

				printf("if\n");
                printf("v[j].edgeList[k]->end[0]:(%p)\n", v[j].edgeList[k]->end[0]);
                printf("%d(%p)(end:%p) \t->end[1]\n", v[j].edgeList[k]->end[1]->id, &v[j].edgeList[k]->end[1]->id, v[j].edgeList[k]->end[1]);
            }
            else
            {
				printf("else\n");
                printf("v[j].edgeList[k]->end[1]:(%p)\n", v[j].edgeList[k]->end[1]);
                printf("%d(%p)(end:%p) \t->end[0]\n", v[j].edgeList[k]->end[0]->id, &v[j].edgeList[k]->end[0]->id, v[j].edgeList[k]->end[0]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main()
{
	struct Vertex v[10];
	struct Edge e[100];
	int j, k, i, l;

	srand(1);
	//�����I
	for(j = 0;j < 10;j ++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}

	//������
//	k = rand() % 20 + 1; //�䪺�ƶq

	k = 10;
	for(j = 0;j < k;j ++)
	{
		//�����ͨ�Ӻ��I
		i = rand() % 10;
		l = rand() % 10;
		printf("vert\ti=%d  l=%d\n", i, l);
		printf("edge\tj=%d \n", j);
		//�䪺���q
		e[j].w = rand() % 100;
		printf("w = %d\n", e[j].w);
		//��Ӻ��I���s��
		e[j].end[0] = &v[i];///�䪺0 vert�Ov[i]����}
		e[j].end[1] = &v[l];
		printf("id-i:%d id-l:%d \n", e[j].end[0]->id , e[j].end[1]->id );
        printf("\n-----------------------\n");
		//�b��Ӻ��I�[�J��
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount ++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount ++;
	}
	print(v);
	/*
	for(j = 0;j < 10;j ++)
    {
        BFS(&v[j]);
        printf("\n");
        DFS(&v[j]);
        printf("\n");
    }*/
}

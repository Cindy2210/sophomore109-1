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
/*
void BFS(struct Vertex *v)
{
    //initial

    struct Vertex *visit[100];//queue
    for(int i = 0 ; i < 100 ; i++)
        visit[i] = NULL;
    
    int color[100];
    for(int i = 0 ; i < 100 ; i++)
        color[i] = white;

    int *predec[100];
    for(int i = 0 ; i < 100 ; i++)
        predec[i] = NULL;
    
    int dist[100];
    for(int i = 0 ; i < 100 ; i++)
        dist[i] = -1;

    int visTop = 0;//added element index
    //put first vertex into visit
    visit[visTop] = &v[0];
    color[visTop] = gray;
    dist[visTop]++;//dist == 0 means start point
    predec[visTop] = -1;//perdec == -1 means start point
    visTop++;

    int VisTail = 0;
    //take visTop as the index of start point of searching

        for(int k = 0 ; k < visit[VisTail]->edgeCount ; k++)
        {
            if(visit[VisTail]->edgeList[k]->end[0] == &v[VisTail])
            {
                visit[visTop] = visit[VisTail]->edgeList[k]->end[1];//put visited node into queue
                dist[visTop] = dist[VisTail] +1;
                predec[visTop] = &visit[VisTail];
            }
            else
            {
                
            }
            
        }


}
*/
void DFS(struct Vertex *v)
{

void BFS(struct Vertex *v)
{
    printf("%d\n", v->edge)
}

void print(struct Vertex v[10])
{
	int j, k;
	for(int j = 0; j < 10; j ++)
    {
        printf("v[j]:(%p)\n", v[j]);
        printf("id:%d(%p) (J:%d)\n", v[j].id, &v[j].id, j);
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

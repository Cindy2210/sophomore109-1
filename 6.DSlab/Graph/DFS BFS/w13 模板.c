#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

void DFS(struct Vertex *v)
{
}

void BFS(struct Vertex *v)
{
}

void print(struct Vertex v[10])
{
	int j, k;
	for(j = 0;j < 10;j ++)
	{
		printf("j:%d\tid:%d \n", j, v[j].id);
		for(k = 0;k < v[j].edgeCount;k ++)
		{
		    printf("k:%d \n", k);
			if(v[j].edgeList[k]->end[0] == &v[j])
				printf("v[j].edgeList[k]->end[1]->id: %d \n", v[j].edgeList[k]->end[1]->id);
			else
				printf("v[j].edgeList[k]->end[0]->id: %d \n", v[j].edgeList[k]->end[0]->id);
            printf("w:%d \n\n", v[j].edgeList[k]->w);
		}
		printf("\n===================\n");
	}
}

int main()
{
	struct Vertex v[10];
	struct Edge e[100];
	int j, k, i, l;

	srand(time(NULL));
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
	for(j = 0;j < 10;j ++)
    {
        BFS(&v[j]);
        printf("\n");
        /*DFS(&v[j]);
        printf("\n");*/
    }
}

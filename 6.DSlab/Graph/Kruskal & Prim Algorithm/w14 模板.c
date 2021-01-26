/*
Week 14 Question 1
Description

請完成樣板中的 Prim's Algorithm 以及Kruskal's Algorithm

如果你只完成 Kruskal's Algorithm 給你 70 分

如果你只完成Prim's Algorithm 給你 80 分

兩個都完成給你 100 分
*/
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

//�Ч��쪺��s�b result
void Kruskal(struct Vertex v[10], struct Edge e[100], struct Edge *result[100])
{
}

//�Ч��쪺��s�b result
void prim(struct Vertex v[10], struct Edge e[100], struct Edge *result[100])
{
}

void print(struct Vertex v[10])
{
	int j, k;
	for(j = 0;j < 10;j ++)
	{
		printf("%d :", v[j].id);
		for(k = 0;k < v[j].edgeCount;k ++)
		{
			if(v[j].edgeList[k]->end[0] == &v[j])
				printf("%d ", v[j].edgeList[k]->end[1]->id);
			else
				printf("%d ", v[j].edgeList[k]->end[0]->id);

		}
		printf("\n");
	}
}

int main()
{
	struct Vertex v[10];
	struct Edge e[100];
	struct Edge *result[100];
	int j, k, i, l;

	srand(time(NULL));
	//�����I
	for(j = 0;j < 10;j ++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}

	//������
	k = rand() % 10 + 1; //�䪺�ƶq
	for(j = 0;j < k;j ++)
	{
		//�����ͨ�Ӻ��I
		i = rand() % 10;
		l = rand() % 10;
		//�䪺���q
		e[j].w = rand() % 100;
		//��Ӻ��I���s��
		e[j].end[0] = &v[i];
		e[j].end[1] = &v[l];
	printf("!!\n");
		//�b��Ӻ��I�[�J��
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount ++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount ++;
	}

	Kruskal(v, e, result);
	prim(v, e, result);
}

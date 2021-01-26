/*
Week 14 Question 1
Description

請完成樣板中的 Prim's Algorithm 以及Kruskal's Algorithm

如果你只完成 Kruskal's Algorithm 給你 70 分

如果你只完成Prim's Algorithm 給你 80 分

兩個都完成給你 100 分
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void print(struct Vertex v[10])
{
	int j, k;
	for (j = 0; j < 10; j++)
	{
		printf("%d :", v[j].id);
		for (k = 0; k < v[j].edgeCount; k++)
		{
			if (v[j].edgeList[k]->end[0]->id == v[j].id)
			{
				printf("%d ", v[j].edgeList[k]->end[1]->id);
				//printf("[1]%d ", v[j].edgeList[k]->end[1]->id);
			}
			else
			{
				printf("%d ", v[j].edgeList[k]->end[0]->id);
				//printf("[0]%d ", v[j].edgeList[k]->end[0]->id);
			}
		}
		printf("\n");
	}
}

void printEdge(struct Edge e[100], int edgeLength)
{
	int j, k;
	//printf("%d\n", edgeLength);
	for (j = 0; j < edgeLength; j++)
	{
		printf("(%p)%d \t(%p)%d\t", e[j].end[0], e[j].end[0]->id, e[j].end[1], e[j].end[1]->id);
		printf("w:%d(%p)\n", e[j].w, e[j]);

		//printf("j:%d\n", j);
	}

	//printf("!!!!\n");
	return;
}

int isTree(struct Vertex v[10], int root_i)
{
	int flag = 1;
	int ID[11];
	for (int j = 0; j <= 10; j++)
		ID[j] = 0;

	for (int i = 0; i < 10; i++)
	{
		if (v[root_i].edgeList[i])
		{
			if (v[root_i].edgeList[i]->end[0]->id == v[root_i].id)
			{
				ID[v[root_i].edgeList[i]->end[1]->id]++;
				ID[v[root_i].edgeList[i]->end[0]->id] = 1;
			}
			else if (v[root_i].edgeList[i]->end[1]->id == v[root_i].id)
			{
				ID[v[root_i].edgeList[i]->end[0]->id]++;
				ID[v[root_i].edgeList[i]->end[1]->id] = 1;
			}
			for (int k = 1; k <= 10; k++)
			{
				if (ID[k] == 2)
				{
					return 0;
				}
			}
		}
		else
			continue;
	}
	return 1;
}

//�P�_�ǤJ�� v �O�_����L
int isForest(struct Vertex v[10])
{
	int flag;
	/*flag == 0->isforest  ==1->not forest*/
	///is tree or not
	for (int i = 0; i < 10; i++)
	{
		flag = isTree(v, i);

		if (flag == 0) //not Tree
		{
			return flag;
			//break;
		}
	}
	return flag;
}

void Kruskal(struct Vertex v[10], struct Edge e[100], int edgeLength, struct Edge *result[100])
{
	struct Edge tmp[50];
	struct Edge sort[50];
	int mark[50];
	int min = 99999, min_i;
	//printf("edgeLength:%d\n", edgeLength);

	for (int i = 0; i < 50; i++)
		mark[i] = 1;
	for (int l = 0; l < edgeLength; l++)
	{
		min = 99999;
		for (int i = 0; i < edgeLength; i++)
		{

			if (min > e[i].w && mark[i])
			{
				min = e[i].w;
				min_i = i;
			}
		}
		sort[l].w = e[min_i].w;
		sort[l].end[0] = e[min_i].end[0];
		sort[l].end[1] = e[min_i].end[1];
		mark[min_i] = 0;
	}
	for (int k = 0; k < edgeLength; k++)
	{
		if (sort[k].end[0]->id > sort[k].end[1]->id)
		{
			struct Vertex *tmpID = sort[k].end[0];
			sort[k].end[0] = sort[k].end[1];
			sort[k].end[1] = tmpID;
		}
	}



	int tmpLength = 0;
	struct Vertex visited[10];
	int visited_i = 0;

	for (int j = 0; j < 10; j++)
	{
		visited[j].id = j + 1;
		visited[j].edgeCount = 0;
	}
	for (int j = 0; j < edgeLength; j++)
	{
		if (sort[j].end[0]->id == sort[j].end[1]->id)
			continue;
		visited[(sort[j].end[0]->id) - 1].edgeList[visited[(sort[j].end[0]->id) - 1].edgeCount] = &sort[j];
		visited[(sort[j].end[0]->id) - 1].edgeCount++;

		visited[(sort[j].end[1]->id) - 1].edgeList[visited[(sort[j].end[1]->id) - 1].edgeCount] = &sort[j];
		visited[(sort[j].end[1]->id) - 1].edgeCount++;

		if (isForest(visited))
		{
			result[tmpLength] = &sort[j];
			tmp[tmpLength].w = sort[j].w;

			tmp[tmpLength].end[0] = sort[j].end[0];

			tmp[tmpLength].end[1] = sort[j].end[1];
			tmpLength++;
		}
		else
		{
			visited[(sort[j].end[0]->id) - 1].edgeCount--;
			visited[(sort[j].end[1]->id) - 1].edgeCount--;
		}
	}
	printf("==============================================================\n\n");
	printEdge(tmp, tmpLength);
	printf("==============================================================\n\n");
	return;
}

//�Ч��쪺��s�b result
void prim(struct Vertex v[10], struct Edge e[100], int edgeLength, struct Edge *result[100])
{
	//sort edge
	struct Edge sort[50];
	int mark[50];
	int min = 99999, min_i;
	//printf("edgeLength:%d\n", edgeLength);

	for (int i = 0; i < 50; i++)
		mark[i] = 1;
	for (int l = 0; l < edgeLength; l++)
	{
		min = 99999;
		for (int i = 0; i < edgeLength; i++)
		{

			if (min > e[i].w && mark[i])
			{
				min = e[i].w;
				min_i = i;
			}
		}
		sort[l].w = e[min_i].w;
		sort[l].end[0] = e[min_i].end[0];
		sort[l].end[1] = e[min_i].end[1];
		mark[min_i] = 0;
	}
    
	//find this tree all node

	int vertFlag[10] = {0};

	for (int i = 0; i < edgeLength; i++)
	{
		vertFlag[e[i].end[0]->id - 1] = 1;
		vertFlag[e[i].end[1]->id - 1] = 1;
	}
    
	int nodeCount = 0;
	for (int i = 0; i < 10; i++)
		if (vertFlag[i] == 1)
			nodeCount++;
	// vert[i] == 1 means that node exist;; == 0 means not exist

	struct Edge tmp[50];
	int tmpLength = 0;
	int start = 0;
	while (vertFlag[start] == 0)
		start++;

	vertFlag[start]++;
	int counts = 1;
	int ID = start + 1;
	while (counts < nodeCount)
	{
		for (int i = 0; i < edgeLength; i++)
		{
			if (sort[i].end[0]->id == sort->end[1]->id)
				continue;
			for (int j = 0; j < 10; j++)
			{
				if (vertFlag[j] == 2)
				{
					ID = j + 1;
					if ((sort[i].end[0]->id == ID) && (vertFlag[sort[i].end[1]->id - 1] != 2)) //added edge
					{																		   
                        result[tmpLength] = &sort[i];
						tmp[tmpLength].w = sort[i].w;
						tmp[tmpLength].end[0] = sort[i].end[0];
						tmp[tmpLength].end[1] = sort[i].end[1];
						tmpLength++;

						vertFlag[sort[i].end[1]->id - 1]++; // ==2
						counts++;
						break;
					}
					if ((sort[i].end[1]->id == ID) && (vertFlag[sort[i].end[0]->id - 1] != 2)) //added edge
					{																		   
                        result[tmpLength] = &sort[i];
						tmp[tmpLength].w = sort[i].w;
						tmp[tmpLength].end[0] = sort[i].end[0];
						tmp[tmpLength].end[1] = sort[i].end[1];
						tmpLength++;

						vertFlag[sort[i].end[0]->id - 1]++; // ==2
						counts++;
						break;
					}
				}

				if (counts == nodeCount)
					break;
			}///end for loop j

			if (counts == nodeCount)
				break;
		}///end for loop i

		if (counts == nodeCount)
			break;
	}///end while loop
	printf("==============================================================\n\n");
	printEdge(tmp, tmpLength);
	printf("\n==============================================================\n");
}
int main()
{
	struct Vertex v[10];
	struct Edge e[100];
	struct Edge *result[100];
	int j, k, i, l;

	srand(10);
	//產生點
	for (j = 0; j < 10; j++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}

	//產生邊
	//k = rand() % 10 + 1; //邊的數量
	k = 15;
	for (j = 0; j < k; j++)
	{
		//先產生兩個端點
		i = rand() % 10;
		l = rand() % 10;
		//邊的重量
		e[j].w = rand() % 100;
		//兩個端點的連結
		e[j].end[0] = &v[i];
		e[j].end[1] = &v[l];
		printf("!!\n");
		//在兩個端點加入邊
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount++;
	}
	printEdge(e, k);
	printf("\n======================kruskal==============================\n");
	Kruskal(v, e, k, result);
	
	printf("\n===========================================================\n");
	printEdge(e, k);
	printf("\n=======================prim================================\n");
	prim(v, e, k, result);
}

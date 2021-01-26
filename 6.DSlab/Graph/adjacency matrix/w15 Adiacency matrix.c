#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Vertex
{
	struct Vertex *edgeList[100];
	int edgeCount;
	int id;
};
/*
void create(struct Vertex v[10], int m[10][10])
{
	//printf("??\n");
	for( int j = 0 ; j < 10 ; j++)
	{
		for(int k = 0 ; k < 10 ; k++)
		{
			//printf("j:%d k:%d\n", j, k);
			if(m[j][k] == 1)
			{
				v[j].edgeList[ v[j].edgeCount++] = &v[k];
				//printf("??\n");
			}
		}
	}
}*/

void create(struct Vertex v[10], int m[10][10])
{
	for (int j = 0; j < 10; j++)
		for (int k = 0; k < 10; k++)
			if (m[j][k] == 1)
				v[j].edgeList[v[j].edgeCount++] = &v[k];
}

void print(struct Vertex v[10])
{
	int j, k;
	for (j = 0; j < 10; j++)
	{
		printf("%d :", v[j].id);
		for (k = 0; k < v[j].edgeCount; k++)
		{
			printf(" %d", v[j].edgeList[k]->id);
		}
		printf("\n");
	}
}

int main()
{
	struct Vertex v[10];
	struct Edge *result[100];
	int j, k, i, l;
	int map[10][10];

	srand(time(NULL));
	//creat Vertex
	for (j = 0; j < 10; j++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}

	//build adjacency matrix
	for (j = 0; j < 10; j++)
	{
		for (k = 0; k < 10; k++)
		{
			if (rand() % 10 > 3)
				map[j][k] = 1;
			else
				map[j][k] = 0;
		}
	}
	printf("col:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
	printf("-------------------------------------------------------------------------------------\n");
	for (j = 0; j < 10; j++)
	{
		printf("row:%d||\t", j);
		for (k = 0; k < 10; k++)
		{
			printf("%d\t", map[j][k]);
		}
		printf("\n");
	}

	//creat graph
	create(v, map);

	print(v);
}

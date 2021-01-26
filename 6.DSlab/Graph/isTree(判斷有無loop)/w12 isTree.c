//Clear vers
/*
Week 12 Question 1
Description
請完成樣板中的 isForest 函數，該函數會判斷傳入的圖是否為一個樹林，如果就回傳 1 ，如果不是就回傳 0 。
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
int isTree(struct Vertex v[10], int root_i)
{
    int *edge_marked[9999], edge_i = 0, *data[9999], data_i = 0, cur_id = 1, now_ID;
    int flag = 1, j, k, *now_ID_ptr, visit_i = 0;

    for(int i = 0 ; i < 9999 ; i++)
        data[i] = NULL;

    if(v[root_i].edgeCount == 0)
        return flag;

    data[data_i] = &v[root_i].id;//data_i == 0
    data_i++;

    int first = 0;
    /*flag == 1 means is_tree, flag == 0 means not tree*/
    while(flag)
    {
        if( visit_i >= data_i )
            break;
        now_ID = *data[visit_i];//get value
        root_i = now_ID -1;

        for(k = 0; k < v[root_i].edgeCount; k ++)
        {
            int edge_flag = 0;
            int data_flag = 0;

            if(v[root_i].edgeList[k]->end[0] == &v[root_i])
            {
                for(int s = 0 ; s < edge_i ; s++)///�o����S���Q�s�L edge_flag == 0, ���Q�s���L edge_flag == 1
                {
                    if(edge_marked[s] == v[root_i].edgeList[k])
                    {
                        edge_flag = 1;
                        break;
                    }
                }
                for(int t = 0 ; t < data_i ; t++)///�o���I�S���Q�s�L data_flag == 0, ���Q�s���L data_flag == 1
                {
                    if(data[t] == &v[root_i].edgeList[k]->end[1]->id)
                    {
                        data_flag = 1;
                        break;
                    }
                }
                if(edge_flag && data_flag)///edge_flag == 1(��Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    continue;
                }
                if(!edge_flag && data_flag)///edge_flag == 0(��S���Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    flag = 0;///�N���Otree
                    break;
                }
                if(!edge_flag && !data_flag)
                {
                    data[data_i] = &v[root_i].edgeList[k]->end[1]->id;
                    data_i++;
                    edge_marked[edge_i] = v[root_i].edgeList[k];
                    edge_i++;

                }

            }
            else
            {
                int edge_flag = 0;
                int data_flag = 0;

                for(int s = 0 ; s < edge_i ; s++)///�o����S���Q�s�L edge_flag == 0, ���Q�s���L edge_flag == 1
                {
                    if(edge_marked[s] == v[root_i].edgeList[k])
                    {
                        edge_flag = 1;
                        break;
                    }
                }
                for(int t = 0 ; t < data_i ; t++)///�o���I�S���Q�s�L data_flag == 0, ���Q�s���L data_flag == 1
                {
                    if(data[t] == &v[root_i].edgeList[k]->end[0]->id)
                    {
                        data_flag = 1;
                        break;
                    }
                }
                if(edge_flag && data_flag)///edge_flag == 1(��Q�s�L) && data_flag == 1(�I�Q�s�L)
                    continue;
                if(!edge_flag && data_flag)///edge_flag == 0(��S���Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    flag = 0 ;///�N���Otree
                    break;
                }
                if(!edge_flag && !data_flag)
                {
                    data[data_i] = &v[root_i].edgeList[k]->end[0]->id;
                    data_i++;
                    edge_marked[edge_i] = v[root_i].edgeList[k];
                    edge_i++;
                }
            }
        }
        if(flag == 0)
            break;
        visit_i++;
        first++;
    }
    return flag;

}

//�P�_�ǤJ�� v �O�_����L
int isForest(struct Vertex v[10])
{
    int flag;
    /*flag == 0->isforest  ==1->not forest*/
    ///is tree or not
    for(int i = 0 ; i < 10 ; i++)
    {
        flag = isTree(v, i);

        if(flag == 0)//not Tree
        {
            return flag;
            //break;
        }
    }
    return flag;
}

void print(struct Vertex v[10])
{
    int j, k;
    for(j = 0; j < 10; j ++)
    {
        printf("%d :", v[j].id);
        for(k = 0; k < v[j].edgeCount; k ++)
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
    struct Vertex v[20];
    struct Edge e[999];
    int j, k, i, l;

    srand(time(NULL));
	//產生點
    for(j = 0; j < 10; j ++)
    {
        v[j].id = j + 1;
        v[j].edgeCount = 0;
    }

	k = rand() % 10 + 1; //邊的數量 
    //k = 10;//邊的數量

    printf("k:%d\n", k);
    for(j = 0; j < k; j ++)
    {
		//先產生兩個端點 
        i = rand() % 10;
        l = rand() % 10;

		//邊的重量
        e[j].w = rand() % 100;

		//兩個端點的連結 
        e[j].end[0] = &v[i];
        e[j].end[1] = &v[l];

        //printf("!!\n");
		//在兩個端點加入邊 
        v[i].edgeList[v[i].edgeCount] = &e[j];
        v[i].edgeCount ++;
        v[l].edgeList[v[l].edgeCount] = &e[j];
        v[l].edgeCount ++;
    }
    print(v);
	printf("%s", isForest(v)? "是樹林":"不是樹林");
    //	printf("%s", isForest(v)? "isForest":"notForest");
    return 0;
}
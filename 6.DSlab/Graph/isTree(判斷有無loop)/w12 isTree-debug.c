//Debug vers

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
int isTree(struct Vertex v[20], int root_i)
{
    int *edge_marked[999], edge_i = 0, *data[999], data_i = 0, cur_id = 1, now_ID;
    int flag = 1, j, k, *now_ID_ptr, visit_i = 0;

    for(int i = 0 ; i < 99 ; i++)
        data[i] = NULL;
//    printf("!!\n");

    if(v[root_i].edgeCount == 0)
        return flag;

    data[data_i] = &v[root_i].id;//data_i == 0
    data_i++;
    //printf("(%d) %d\n", *data[data_i-1], data_i-1);
    int first = 0;
    /*flag == 1 means is_tree, flag == 0 means not tree*/
    while(flag)
    {
        //printf("data_i:%d\n", data_i);
        //printf("visit_i:%d\n", visit_i);
        if( visit_i >= data_i )///not sure = !!!!!!!!!!!!!!
            break;

        now_ID = *data[visit_i];//get value
        root_i = now_ID -1;
        //printf("v:%d\n", visit_i);
        //printf("now_ID:%d \troot_i:%d\n", now_ID, root_i);
        for(k = 0; k < v[root_i].edgeCount; k ++)
        {
            int edge_flag = 0;
            int data_flag = 0;

            if(v[root_i].edgeList[k]->end[0] == &v[root_i])
            {
                //printf("first  if\t\t");
                //printf("v[root_i].edgeList[k]->end[0] == &v[root_i]\n");

                for(int s = 0 ; s < edge_i ; s++)///�o����S���Q�s�L edge_flag == 0, ���Q�s���L edge_flag == 1
                {
                    //printf("s:%d \tedge_marked:%p \n", s,edge_marked[s]);
                    if(edge_marked[s] == v[root_i].edgeList[k])
                    {
                        //printf("edge_marked[%d] (%p) \\\\\\ v[root_i].edgeList[%d]->end[1] (%p)\n", s, edge_marked[s], k, v[root_i].edgeList[k]->end[1]);
                        //printf("edge_flag = 1\n");
                        edge_flag = 1;
                        break;
                    }
                }
                for(int t = 0 ; t < data_i ; t++)///�o���I�S���Q�s�L data_flag == 0, ���Q�s���L data_flag == 1
                {
                    //printf("t:%d \tdata:%d(%p)  root_i:%d\n", t, (*data[t]), data[t], root_i );
                    if(data[t] == &v[root_i].edgeList[k]->end[1]->id)
                    {
                        //printf("data[%d]:%d(%p)  root_i:%d\n", t, (*data[t]), data[t], root_i );
                        //printf("data_flag = 1\n");
                        data_flag = 1;
                        break;
                    }
                }
                //printf("(visit_i:%d) (k:%d)\ted_f:%d dat_f:%d\n", visit_i, k, edge_flag, data_flag);

                if(edge_flag && data_flag)///edge_flag == 1(��Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    //printf("continue\n");
                    continue;
                }
                if(!edge_flag && data_flag)///edge_flag == 0(��S���Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    flag = 0 ;///�N���Otree
                    //printf("flag = 0\n");
                    //printf("break\n");
                    break;
                }
                if(!edge_flag && !data_flag)
                {
                    //printf("����\n");
                    data[data_i] = &v[root_i].edgeList[k]->end[1]->id;
                    data_i++;
                    edge_marked[edge_i] = v[root_i].edgeList[k];
                    edge_i++;
                    //printf("V:%p(%p) E:%p(%p)\n", data[data_i-1], v[root_i].edgeList[k]->end[1], edge_marked[edge_i-1], v[root_i].edgeList[k]);
                }
            }
            else
            {
                int edge_flag = 0;
                int data_flag = 0;

                //printf("second\t\t");
                //printf("v[root_i].edgeList[k]->end[1] == &v[root_i]\n");
                for(int s = 0 ; s < edge_i ; s++)///�o����S���Q�s�L edge_flag == 0, ���Q�s���L edge_flag == 1
                {
                    //printf("s:%d \tedge_marked:%p \n", s, edge_marked[s]);
                    if(edge_marked[s] == v[root_i].edgeList[k])
                    {
                        //printf("edge_marked[s] == v[root_i].edgeList[k]->end[0]\n");
                        //printf("edge_flag = 1;\n");
                        edge_flag = 1;
                        break;
                    }
                }
                for(int t = 0 ; t < data_i ; t++)///�o���I�S���Q�s�L data_flag == 0, ���Q�s���L data_flag == 1
                {
                    //printf("t:%d \tdata:%d(%p)  root_i:%d\n", t, (*data[t]), data[t], root_i );
                    if(data[t] == &v[root_i].edgeList[k]->end[0]->id)
                    {
                        //printf("data[%d]:%d(%p)  root_i:%d\n", t, (*data[t]), data[t], root_i );

                        /*if(myself == 0 && edge_flag == 1)
                        {
                            myself++;
                            continue;
                        }*/

                        //printf("data_flag = 1;\n");
                        data_flag = 1;
                        break;
                    }
                }
                //printf("(v:%d)(k:%d)\ted_f:%d dat_f:%d\n", visit_i, k, edge_flag, data_flag);
                if(edge_flag && data_flag)///edge_flag == 1(��Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    //printf("continue\n");
                    continue;
                }
                if(!edge_flag && data_flag)///edge_flag == 0(��S���Q�s�L) && data_flag == 1(�I�Q�s�L)
                {
                    flag = 0 ;///�N���Otree
                    //printf("flag = 0\n");
                    //printf("break\n");
                    break;
                }
                if(!edge_flag && !data_flag)
                {
                    //printf("����\n");

                    data[data_i] = &v[root_i].edgeList[k]->end[0]->id;
                    data_i++;
                    edge_marked[edge_i] = v[root_i].edgeList[k];
                    edge_i++;
                    //printf("V:%p(%p) E:%p(%p)\n", data[data_i-1], v[root_i].edgeList[k]->end[0], edge_marked[edge_i-1], v[root_i].edgeList[k]);
                }
            }
            //printf("((out_if___else))\n\n");
        }
        //printf("------------------(out__for)------------------\n");
        //printf("%d\n", flag);
        if(!flag)
        {
            //printf("flag = %d\n", flag);
            //printf("!\n");
            break;
        }
        //printf("visit_i++ ;\n");
        visit_i++;
        //printf("first++  BF_first:%d\n", first);
        first++;
    }
    return flag;
}

//�P�_�ǤJ�� v �O�_����L
int isForest(struct Vertex v[20])
{
    for(int j = 0; j < 10; j ++)
    {
        //printf("id:%d(%p) (J:%d):\n", v[j].id, &v[j].id, j);
        for(int k = 0; k < v[j].edgeCount; k ++)
        {
            //printf("edge--(k:%d)\tv[j].edgeList[k]:(%p)\t\t", k,  v[j].edgeList[k]);
            if(v[j].edgeList[k]->end[0] == &v[j])
            {
                //printf("v[j].edgeList[k]->end[0]:(%p)\n", v[j].edgeList[k]->end[0]);
                //printf("%d(%p)(end:%p) \t->end[1]\n", v[j].edgeList[k]->end[1]->id, &v[j].edgeList[k]->end[1]->id, v[j].edgeList[k]->end[1]);
            }
            else
            {
                //printf("v[j].edgeList[k]->end[1]:(%p)\n", v[j].edgeList[k]->end[1]);
                //printf("%d(%p)(end:%p) \t->end[0]\n", v[j].edgeList[k]->end[0]->id, &v[j].edgeList[k]->end[0]->id, v[j].edgeList[k]->end[0]);
            }
            //printf("\n");

            //printf("\tw:%d \n", v[j].edgeList[k]->w);
        }
        //printf("\n");
    }
    int flag;
    /*flag == 0->isforest  ==1->not forest*/
    ///is tree or not
    for(int i = 0 ; i < 10 ; i++)
    {
        //printf("(i:%d)\n-----------------------------------------\n", i);
        flag = isTree(v, i);
        //printf("(out)\n----------flag:%d-------------------------\n", flag);
        if(flag == 0)//not Tree
            {

    return flag;
                //break;
                }
        //printf("=======================================================\n");
    }
    return flag;
}

/*void print(struct Vertex v[10])
{
    int j, k;
    for(j = 0; j < 10; j ++)
    {
        printf("%d :", v[j].id);
        for(k = 0; k < v[j].edgeCount; k ++)
        {
            if(v[j].edgeList[k]->end[0] == &v[j])
                printf("%d(%p) \t->end[0]", v[j].edgeList[k]->end[1]->id, v[j].edgeList[k]->end[1]);
            else
                printf("%d(%p) \t->end[1]", v[j].edgeList[k]->end[0]->id, v[j].edgeList[k]->end[0]);

            printf("\tw:%d \n", v[j].edgeList[k]->w);
        }
        printf("\n");
    }

}
*/

void print(struct Vertex v[20])
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

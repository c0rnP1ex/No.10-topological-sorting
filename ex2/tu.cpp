#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<limits.h>  
#include<iostream>
using namespace std;

#define INFINITY 4270000 // 用整型最大值代替∞ 

#include"ALGraph.h"

#include"sqstack.h"

void FindInDegree(ALGraph G,int indegree[]); // 求顶点的入度

int TopologicalSort(ALGraph G);// 有向图G采用邻接表存储结构。若G无回路，则输出G的顶点的一个拓扑序列并返回1，否则返回0
	
int main()
{
	ALGraph g;
	CreateGraphF(g); // 利用数据文件创建无向图
	Display(g); // 输出无向图
	printf("输出有向图g的拓扑序列:\n");
	TopologicalSort(g); // 输出有向图f的拓扑序列  
	return 0;
}

void FindInDegree(ALGraph G,int indegree[])
{ //计算图G每个顶点的入度，并且保存在indegree数组
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i]=0; /* 赋初值 */
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->data.adjvex]++;
			p=p->nextarc;
		}
	}
}
int TopologicalSort(ALGraph G)
{   
	// 有向图G采用邻接表存储结构。
	// 若G无回路，则输出G的顶点的一个拓扑序列并返回1，否则返回0。
	int i, j, k, count = 0;
	int indegree[MAX_VERTEX_NUM];
	SqStack S;
	InitStack(S);
	FindInDegree(G, indegree);
	for (i = 0; i < G.vexnum; i++) {
		if (indegree[i] == 0) {
			Push(S, i);
		}
	}
	while (!StackEmpty(S)) {
		Pop(S, i);
		printf("%s ", G.vertices[i].data);
		count++;
		for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
			j = p->data.adjvex;
			if (--indegree[j] == 0) {
				Push(S, j);
			}
		}
	}
	if (count < G.vexnum) {
		printf("\n此有向图有回路");
		return 0;
	}
	return 1;
}

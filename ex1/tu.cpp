#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<limits.h>  

#include"MGraph.h"

#include"sqstack.h"

void FindInDegree(MGraph G,int indegree[]); // 求顶点的入度

int TopologicalSort(MGraph G);// 有向图G采用邻接矩阵存储结构。若G无回路，则输出G的顶点的一个拓扑序列并返回1，否则返回0
	
int main()
{
	MGraph g;
	CreateGraphF(g); // 利用数据文件创建无向图
	Display(g);      // 输出无向图
	printf("输出有向图g的拓扑序列:\n");
	TopologicalSort(g); // 输出有向图f的拓扑序列  	
	return 0;
}

void FindInDegree(MGraph G,int indegree[])
{ //计算图G每个顶点的入度，并且保存在indegree数组
	int i,j;	
	for(i=0;i<G.vexnum;i++)
		indegree[i]=0; /* 赋初值 */	
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
		if( G.arcs [j][i].adj == 1)
			indegree[i]++;	
}

int TopologicalSort(MGraph G)
{   // 有向图G采用邻接矩阵存储结构。
	// 若G无回路，则输出G的顶点的一个拓扑序列并返回1，否则返回0。
	/********** Begin **********/    
	int indegree[MAX_VERTEX_NUM],i,j,k;
	SqStack S;
	InitStack(S);
	FindInDegree(G,indegree);
	int count = 0;
	for(i=0;i<G.vexnum;i++){
		if(indegree[i]==0){
			Push(S,i);
		}
	}
	while(!StackEmpty(S)){
		Pop(S,i);
		count++;
		printf("%s ", G.vexs[i]);
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[i][j].adj==1){
				indegree[j]--;
				if(indegree[j]==0)
					Push(S,j);
			}
		}
	}
	if(count != G.vexnum){
		printf("\n此有向图有回路");
		return 0;
	}

	for(k=0;k<G.vexnum;k++){
		if(indegree[k]!=0){
			return 0;
		}
	}
	return 1;
	/********** End **********/
}

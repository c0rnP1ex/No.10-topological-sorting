#include<stdio.h>
#include<string.h>
#include"ALGraph.h" 
#include"LinkList.h"  



int LocateVex(ALGraph G,VertexType u)
{   // 初始条件：图G存在，u和G中顶点有相同特征 
	// 操作结果：若G中存在顶点u，则返回该顶点在图中位置；否则返回-1 	
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

int FirstAdjVex(ALGraph G,VertexType v)
{   // 初始条件：图G存在，v是G中某个顶点 
	// 操作结果：返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1 
	LinkList p;
	int v1;
	v1=LocateVex(G,v); // v1为顶点v在图G中的序号 
	p=G.vertices[v1].firstarc;
	if(p)
		return p->data.adjvex;
	else
		return -1;
}

int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{   // 初始条件：图G存在，v是G中某个顶点，w是v的邻接顶点 
	// 操作结果：返回v的(相对于w的)下一个邻接顶点的序号。若w是v的最后一个邻接点，则返回-1 
	LinkList p,p1; // p1在Point()中用作辅助指针
	ElemType e;
	int v1;
	v1=LocateVex(G,v);        // v1为顶点v在图G中的序号 
	e.adjvex=LocateVex(G,w);  // e.adjvex为顶点w在图G中的序号 
	p=Point(G.vertices[v1].firstarc,e,equal,p1); // p指向顶点v的链表中邻接顶点为w的结点 
	if(!p||!p->next)          // 没找到w或w是最后一个邻接点 
		return -1;
	else                       // p->data.adjvex==w 
		return p->next->data.adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号 	
}


void CreateGraphF(ALGraph &G)
{   // 采用邻接表 存储结构，由文件构造没有相关信息图或网G(用一个函数构造4种图) 
	int i,j,k,w;            // w是权值 
	VertexType va,vb;       // 连接边或弧的2顶点 
	ElemType e;
	char filename[13];
	FILE *graphlist;
	//printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
	scanf("%d",&G.kind);
	//printf("请输入数据文件名：");
	scanf("%s",filename);   
	graphlist=fopen(filename,"r"); // 以读的方式打开数据文件，并以graphlist表示 
	fscanf(graphlist,"%d",&G.vexnum);
	fscanf(graphlist,"%d",&G.arcnum);
	for(i=0;i<G.vexnum;++i)        // 构造顶点向量 
	{
		fscanf(graphlist,"%s",G.vertices[i].data);
		G.vertices[i].firstarc=NULL; // 初始化与该顶点有关的出弧链表 
	}
	for(k=0;k<G.arcnum;++k)          // 构造相关弧链表 
	{
		if(G.kind%2)                 // 网 
			fscanf(graphlist,"%s%s%d",va,vb,&w);
		else                         // 图 
			fscanf(graphlist,"%s%s",va,vb);
		i=LocateVex(G,va);          // 弧尾 
		j=LocateVex(G,vb);          // 弧头 
		e.info=0;                   // 给待插表结点e赋值，图无权 
		e.adjvex=j;                 // 弧头 
		if(G.kind%2)                // 网 
		{
			e.info = w;
		}
		ListInsert(G.vertices[i].firstarc,1,e); // 插在第i个元素(出弧)的表头
		if(G.kind>=2)  // 无向图或网，产生第2个表结点，并插在第j个元素(入弧)的表头 
		{
			e.adjvex=i;                    // e.info不变，不必再赋值 
			ListInsert(G.vertices[j].firstarc,1,e);   // 插在第j个元素的表头
		}
	}
	fclose(graphlist);                    // 关闭数据文件 
} 


void Display(ALGraph G)
{    // 输出图的邻接表G 
	int i;
	LinkList p;
	switch(G.kind)
	{
      case DG: printf("有向图\n");	      break;
      case DN: printf("有向网\n");          break;
      case UDG:printf("无向图\n");         break;
      case UDN:printf("无向网\n");
	}
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);
	printf("\n%d条弧(边):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			printf("%s→%s ",G.vertices[i].data,G.vertices[p->data.adjvex].data);
			if(G.kind%2)            // 网 
				printf(":%d\t",p->data.info );			
			p=p->nextarc;
		}
		printf("\n");
	}
} 

int equal(ElemType a,ElemType b)
{   
	if(a.adjvex==b.adjvex)
		return 1;
	else
		return 0;
}

void visit(VertexType i)
{
	printf("%s ",i);
}

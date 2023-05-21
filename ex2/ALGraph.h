#ifndef   __ALGraph_H__
#define   __ALGraph_H__

typedef char VertexType[20]; // 顶点类型为字符串 
#define MAX_VERTEX_NUM  20
typedef enum{DG,DN,UDG,UDN}GraphKind; // {有向图,有向网,无向图,无向网} 

typedef struct 
{
	int adjvex; // 该弧所指向的顶点的位置 
	int info; // 网的权值指针 
}ElemType;

typedef struct ArcNode 
{
	ElemType data; // 除指针以外的部分都属于ElemType 
	struct ArcNode *nextarc; // 指向下一条弧的指针 
}ArcNode;           // 表结点 

typedef struct
{
	VertexType data; // 顶点信息 
	ArcNode *firstarc; // 第一个表结点的地址,指向第一条依附该顶点的弧的指针 
}VNode,AdjList[MAX_VERTEX_NUM]; // 头结点 

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;       // 图的当前顶点数和弧数 
	GraphKind kind;          // 图的种类标志 
}ALGraph;

#define LNode ArcNode        // 定义单链表的结点类型是图的表结点的类型 
#define next nextarc         // 定义单链表结点的指针域是表结点指向下一条弧的指针域 
typedef ArcNode *LinkList;   // 定义指向单链表结点的指针是指向图的表结点的指针 


int equal(ElemType a,ElemType b);
void visit(VertexType i);
int LocateVex(ALGraph G,VertexType u);//若G中存在顶点u，则返回该顶点在图中位置；否则返回-1
int FirstAdjVex(ALGraph G,VertexType v); // 返回v的第一个邻接顶点的序号；否则返回-1 
int NextAdjVex(ALGraph G,VertexType v,VertexType w);//v是图G中某个顶点，w是v的邻接顶点，返回v的(相对于w的)下一个邻接顶点的序号
void CreateGraphF(ALGraph &G);// 采用邻接表存储结构，由文件构造没有相关信息图或网G
void Display(ALGraph G);  // 输出图的邻接表G 


#endif
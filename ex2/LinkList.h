#ifndef   __LinkList_H__
#define   __LinkList_H__ // 函数结果状态代码

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#include"ALGraph.h" 

typedef  LNode * LinkList; // 另一种定义LinkList的方法

// 不带头结点的单链表的部分基本操作(9个)
 #define DestroyList ClearList // DestroyList()和ClearList()的操作是一样的
 void InitList(LinkList &L); 
 void ClearList(LinkList &L);
 int ListEmpty(LinkList L);
 int ListLength(LinkList L);
 int GetElem(LinkList L,int i,ElemType &e);
 int LocateElem(LinkList L,ElemType e,int(*compare)(ElemType,ElemType));
 int ListInsert(LinkList &L,int i,ElemType e);
 int ListDelete(LinkList &L,int i,ElemType &e);
 void ListTraverse(LinkList L,void(*vi)(ElemType));

 LinkList Point(LinkList L,ElemType e,int(*equal)(ElemType,ElemType),LinkList &p);//查找表L中满足条件的结点。如找到
 
#endif
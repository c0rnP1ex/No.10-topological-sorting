#include<stdio.h>
#include<stdlib.h>

#include"sqstack.h" 

void InitStack(SqStack &S)
{ 
	if(!(S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
     exit(OVERFLOW); // 存储分配失败
    S.top=S.base;
	S.stacksize=STACK_INIT_SIZE; 
}

void DestroyStack(SqStack &S)
{ 
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0; 
}

void ClearStack(SqStack &S)
{ 
	S.top=S.base;
}

int StackEmpty(SqStack S)
{
	if(S.top==S.base)
     return TRUE;
	else
     return FALSE; 	
 }

int StackLength(SqStack S)
{ 
	return S.top-S.base;
}

int GetTop(SqStack S,SElemType &e)
{ 
	if(S.top>S.base)
   {
     e=*(S.top-1);
     return OK;
   }
   else
     return ERROR;
 }

void Push(SqStack &S,SElemType e)
{ 
	if(S.top-S.base>=S.stacksize) // 栈满，追加存储空间
	{
     S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
     if(!S.base)
       exit(OVERFLOW); // 存储分配失败
     S.top=S.base+S.stacksize;
     S.stacksize+=STACKINCREMENT;
	}
   *(S.top)++=e; 
}

int Pop(SqStack &S,SElemType &e)
{ 
	if(S.top==S.base)
     return ERROR;
	e=*--S.top;
	return OK;
}

void StackTraverse(SqStack S,void(*visit)(SElemType))
{
	while(S.top>S.base)
		visit(*S.base++);
	printf("\n");
}

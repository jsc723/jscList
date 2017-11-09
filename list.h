#ifndef LIST_H
#define LIST_H

#include "jscobj.h"
//--------------------enum----------------------//
typedef enum ListState{
	INS_DEL,
	RAND
}ListState;
typedef enum NodeKind{
	DATA,
	HELPER
}NodeKind;
typedef enum printOption{
	p_len = 0x01,
	p_state = 0x02,
	p_len_state = 0x03,
	p_helper = 0x04,
	p_values = 0x08,
	p_all = 0x0f
}printOption;
typedef enum bool{
	false,
	true
}bool;

//-------------------node-----------------------//
typedef struct BaseNode
{
	NodeKind kind;
	struct BaseNode *next; 
}BaseNode,*pBaseNode;

typedef struct Node
{
	NodeKind kind;
	struct Node *next;
	int data;
}Node,*pNode;

typedef struct HNode
{
	NodeKind kind;
	struct HNode *next;
	struct BaseNode *down; //Node or HNode
	
}HNode,*pHNode;
//-------------------list-----------------------//

typedef struct List *pList;
typedef struct List
{
	/****/Dec_Method(List);/****/
	
	pNode (*getEleAdr)(int index,bool useHelper);
	int (*getValue)(int index);
	void (*setValue)(int index,int value);
	pList (*print)(printOption option);
	pList (*pushFront)(int value);
	pList (*pushBack)(int value);
	pList (*insert)(int index,int value);
	void (*insertAfterAdr)(pNode p,int value);
	int (*popFront)();
	int (*popBack)();
	int (*pop)(int index);
	void (*toRand)();
	void (*toInsDel)();
	void (*changeLen)(int delta);
	
	ListState state;
	int length;
	pNode nodes;
	pHNode helper;
	int helperMaxLevel;
}List;

//--------------------functions----------------------//
pList List$$new();
void List$$init(pList list);


pNode List$getEleAdr(int index,bool useHelper);
int List$getValue(int index);
void List$setValue(int index,int value);
pList List$print(printOption option);
pList List$pushFront(int value);
pList List$pushBack(int value);
pList List$insert(int index,int value);
void List$insertAfterAdr(pNode p,int value);
int List$popFront();
int List$popBack();
int List$pop(int index);
void List$toRand();
void List$toInsDel();
void List$changeLen(int delta);

pNode newNode(int value);
pHNode newHNode();
int downData(pHNode h);
void showHelper(pHNode helper);
void delHelper(pHNode h);
void delHelperLink(pHNode p);
int pow(int x,int y);
#endif

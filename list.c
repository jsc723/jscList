#include "list.h"
#include "jscobj.h"
#include "stdio.h"
#include "stdlib.h"


Def_Method(List)

pList List$$new()
{
	pList lst = (pList)malloc(sizeof(List));
	List$$init(lst);
	return lst;
}
void List$$init(pList list)
{
	/****/Ist_Method(list,List)/****/
	
	list->getEleAdr = List$getEleAdr;
	list->getValue = List$getValue;
	list->setValue = List$setValue;
	list->insert = List$insert;
	list->insertAfterAdr = List$insertAfterAdr;
	list->pushFront = List$pushFront;
	list->pushBack = List$pushBack;
	list->pop = List$pop;
	list->popBack = List$popBack;
	list->popFront = List$popFront;
	list->print = List$print;
	list->toRand = List$toRand;
	list->toInsDel = List$toInsDel;
	list->changeLen = List$changeLen;
	
	list->state = INS_DEL;
	list->nodes = NULL;
	list->helper = NULL;
	list->helperMaxLevel = 0;
	list->length = 0;
}
pList List$print(printOption option)
{
	/****/getSelf(List)/****/
	pNode i = self->nodes;
	if(option&p_len)
	{
		printf("*** Length:%d ***",self->length);
	}
	if(option&p_state)
	{
		printf("*** State: %s ***",self->state==INS_DEL?"INS_DEL":"RAND");
	}
	if(option&(p_state|p_len))
		printf("\n");
	if(option&p_helper)
	{
		printf("Helper: (level %d)\n",self->helperMaxLevel);
		showHelper(self->helper);
	}
	if(option&p_values)
	{
		for(;i!=NULL;i=i->next)
			printf("%d => ",i->data);
		printf("X\n",self->length,self->state==INS_DEL?"INS_DEL":"RAND");
	}
	return this;
}
pList List$pushFront(int value)
{
	/****/getSelf(List)/****/
	pNode p = newNode(value);
	p->next = self->nodes;
	self->nodes = p;
	this->changeLen(1);
	return this;
}
pList List$pushBack(int value)
{
	/****/getSelf(List)/****/
	this->insert(self->length,value);
	return this;
}
pList List$insert(int index,int value)
{
	/****/getSelf(List)/****/
	pNode p,q;
	if(index>self->length)
		index = self->length;
	else if(index<=0)
		this->pushFront(value);
	else
	{
		this->insertAfterAdr(this->getEleAdr(index-1,false),value);
	}
	return this;
}
void List$insertAfterAdr(pNode p,int value)
{
	/****/getSelf(List)/****/
	pNode q = newNode(value);
	q->next = p->next;
	p->next = q;
	this->changeLen(1);
}
int List$popFront()
{
	/****/getSelf(List)/****/
	int n;
	pNode p = self->nodes;
	if(p==NULL)
	{
		printf("Error in popFront: the list is empty!\n");
		exit(4);
	}
	n = p->data;
	self->nodes = p->next;
	this->changeLen(-1);
	return n;
}
int List$popBack()
{
	/****/getSelf(List)/****/
	return this->pop(self->length-1);
}
int List$pop(int index)
{
	/****/getSelf(List)/****/
	pNode p,q;
	int r;
	if(self->nodes==NULL||index<0||index>=self->length)
	{
		printf("Error in pop: element doesn't exist!\n");
		exit(4);
	}
	if(index==0)
		return this->popFront();
	p = this->getEleAdr(index-1,false);
	q = p->next;
	p->next = q->next;
	r = q->data;
	free(q);
	this->changeLen(-1);
	return r;
}
pNode List$getEleAdr(int index, bool useHelper)
{
	/****/getSelf(List)/****/
	pBaseNode p;
	int unit,k;
	if(index<0||index>=self->length)
	{
		printf("Error in getEleAdr: index is out of range!\n"); 
		exit(2);
	}
	if(!useHelper)
	{
	    for(p = (pBaseNode)self->nodes;index!=0;index--)
	    	p = p->next;
	}
	else
	{
		if(self->state!=RAND)
			this->toRand();
		p = self->helper;
		k = self->helperMaxLevel;
		unit = pow(10,k);
		while(true)
		{
			unit = pow(10,k--);
			while(unit<=index)
			{
				index-=unit;
				p = p->next;
			}
			if(p->kind==DATA)
				break;
			p = ((pHNode) p)->down;
		}
	}
	return p;
}
int List$getValue(int index)
{
	/****/getSelf(List)/****/
	return this->getEleAdr(index,true)->data;
}
void List$setValue(int index,int value)
{
	/****/getSelf(List)/****/
	this->getEleAdr(index,true)->data = value;
}
void List$toRand()
{
	/****/getSelf(List)/****/
	pHNode p,head;
	pBaseNode q = (pBaseNode)self->nodes;
	int count,i;
	if(self->state==RAND)
		return;
	self->state = RAND;
	do
	{
		head = newHNode();
		p = head;
		count = 0;
		self->helperMaxLevel++;
		while(1)
		{
			p->down = q;
			for(i=0;i<10 && q!=NULL;i++)
			{
				q = q->next;
			}
			if(q==NULL)
				break;
			p->next = newHNode();
			p = p->next;
			count++;
		}
		q = (pBaseNode)head;
	}while(count>10);
	self->helper = head;
}
void List$toInsDel()
{
	/****/getSelf(List)/****/
	self->state = INS_DEL;
	delHelper(self->helper);
	self->helper = NULL;
	self->helperMaxLevel = 0;
}
void List$changeLen(int delta)
{
	/****/getSelf(List)/****/
	self->length += delta;
	if(self->state == RAND)
		this->toInsDel();
}
//-------------------------------------------------------------//
pNode newNode(int value)
{
	pNode p = (pNode)malloc(sizeof(Node));
	if(p==NULL)
	{
		printf("Error when creating a new node!\n");
		exit(1);
	}
	p->kind = DATA;
	p->data = value;
	p->next = NULL;
	return p;
}
pHNode newHNode()
{
	pHNode p = (pHNode)malloc(sizeof(HNode));
	if(p==NULL)
	{
		printf("Error when creating a new helper node!\n");
		exit(1);
	}
	p->kind = HELPER;
	p->down = NULL;
	p->next = NULL;
}
int downData(pHNode h)
{
	pBaseNode p = (pBaseNode)h;
	if(h==NULL)
		return -1;
	while(p!=NULL && p->kind!=DATA)
		p = ((pHNode)p)->down;
	return ((pNode)p)->data;
}
void showHelper(pHNode helper)
{
	pHNode q,p  = helper;
	if(helper==NULL)
	{
		printf("NULL\n");
		return;
	}
	do
	{
		for(q=p;q!=NULL;q=q->next)
		{
			printf("[%d]->",downData(q));
		}
		printf("X\n");
		p = p->down;
	}while(p->kind==HELPER);
}
void delHelperLink(pHNode p)
{
	pHNode q;
	while(p!=NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
}
void delHelper(pHNode h)
{
	pHNode q;
	while(h->kind!=DATA)
	{
		q = h;
		h = h->down;
		delHelperLink(q);
	}
}
int pow(int x,int y)
{
	int i,p = 1;
	for(i=0;i<y;i++)
		p*=x;
	return p;
}

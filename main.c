#include <stdio.h>
#include <stdlib.h>
#include "jscobj.h"
#include "list.h"
#include <time.h>


void start(pList list)
{
	int i;
	for(i=20000;i>=0;i--)
		m(list)->pushFront(i);
}
void access(pList list)
{
	int i;
	for(i=40;i<200;i+=10)
		m(list)->setValue(i,100+i);
	for(i=0;i<10;i+=1)
		m(list)->insert(10,-1);
}
void delsome(pList list)
{
	int i;
	for(i=0;i<50;i++)
		m(list)->pop(200);
}
void timeTest()
{
	clock_t a,b;
	int i;
	pList list = List$$new();
	start(list);
	//*
	a = clock();
	for(i=0;i<20000;i++)
		m(list)->getEleAdr(i,false);
	b = clock();
	printf("time without helper: %ld ms\n",b-a);
	//*/
	a = clock();
	m(list)->toRand();
	b = clock();
	printf("time of toRand: %ld ms\n",b-a);
	a = clock();
	for(i=0;i<20000;i++)
		m(list)->getEleAdr(i,true);
	b = clock();
	printf("time with helper: %ld ms\n",b-a);
	a = clock();
	m(list)->toInsDel();
	b = clock();
	printf("time of toInsDel: %ld ms\n",b-a);
}
void reverseI(pList list)
{
	pNode x = NULL,y = list->nodes, z;
	if(y==NULL)
		return;
	z = y->next;
	while(1)
	{
		y->next = x;
		if(z==NULL)
			break;
		x = y;
		y = z;
		z = z->next;
	}
	list->nodes = y;
}
void reverseTest()
{
	int i;
	pList list = List$$new();
	start(list);
	m(list)->print(p_values);
	reverseI(list);
	m(list)->print(p_values);
}
int main()
{
	timeTest(); 
	/*
	pList p = List$$new();
	start(p);
	access(p);
    m(p)->print(p_all);
    */
    //reverseTest();
	return 0;
}

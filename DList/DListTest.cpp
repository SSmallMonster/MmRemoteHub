/*************************************************************************
# File Name: main.cpp
# Author: 周明明
# mail: 1018602442@qq.com
	> Created Time: Sun 19 May 2019 01:15:26 AM PDT
 ************************************************************************/

#include<iostream>
#include "DList.h"
#include <malloc.h>
using namespace std;

int main()
{
	DList list;
	for(int i = 0; i < 20; i+=2)
	{
		NODE pNew = (NODE)malloc(sizeof(Node));
		pNew->data = i;
		list.InsertTailNode(pNew);
	}
	NODE pEach = NULL;
	list.DLEachNode(pEach);

	for(int i = 1; i < 20; i+=2)
	{
		NODE pNew = (NODE)malloc(sizeof(Node));
		pNew->data = i;

		NODE pBefore = NULL;
		if(RET::SUCCESS == list.FindSpecNode(i - 1, pBefore))
		{
			list.InsertMiddleNode(pBefore,pNew);
		}
		else
		{
			free(pNew);
			pNew = NULL;
			printf("Index: %d Find error",i);
		}
	}
	list.DLEachNode(pEach);
	
#if 0	
	for(int i = 1; i < 20; i+=2)
	{
		NODE pNode = NULL;
		if(RET::SUCCESS == list.FindSpecNode(i, pNode))
		{
			list.PopSpecNode(pNode);
		}
		else
		{
			printf("Index: %d Find error",i);
		}
	}
	list.DLEachNode(pEach);
#endif
	return 0;
}

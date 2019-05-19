/*************************************************************************
# File Name: DList.h
# Author: 周明明
# mail: 1018602442@qq.com
	> Created Time: Sun 19 May 2019 12:43:23 AM PDT
 ************************************************************************/
#ifndef _DLIST_H_
#define _DLIST_H_

#define _DEBUG_

#include <iostream>
#include <malloc.h>
using namespace std;
//template <typename DataType>
namespace RET
{
	const int SUCCESS = 0;
	const int FAIL = -1;
};

typedef struct Node
{
	int data;
	Node *pNext;
	Node *pPre;
}*NODE;

class DList
{
	public:
		//无参构造函数
		DList()
		{
			_iListLen = 0;
			CreateHead();
		}
		
		~DList()
		{
			printf("Delete DList object now\n");
			NODE pTemp = NULL;
#ifdef _DEBUG_
			NODE pCopy = NULL;
			NODE pHeadCopy = _pHead;
#endif
			while(RET::SUCCESS == DLEveryNode(pTemp))
			{
#ifdef _DEBUG_
			NODE pCopy = pTemp;
#endif
				if(RET::SUCCESS != PopSpecNode(pTemp))
				{
					printf("PopNode:%p error",pTemp);
				}
#ifdef _DEBUG_
				else
				{
					printf("Node:%p Pop Success remain len:%d\n",pCopy,_iListLen);
				}
#endif
				pTemp = NULL;
			}
			if(_iListLen == 1)
			{
				if(RET::SUCCESS != PopSpecNode(_pHead))
				{
					printf("PopHeadNode:%p error\n",_pHead);
				}
#ifdef _DEBUG_
				else
				{
					printf("HeadNode:%p Pop Success, remain len:%d\n",pHeadCopy,_iListLen);
				}
#endif
			}
		}
		//插入节点:尾插
		void InsertTailNode(NODE pNew)
		{
			NODE pTailNode = _pHead->pPre;
			
			pNew->pNext = _pHead;
			_pHead->pPre = pNew;
			pTailNode->pNext = pNew;
			pNew->pPre = pTailNode;
			
			_iListLen++;
		}

		//Middle insert
		void InsertMiddleNode(NODE pBefore, NODE pNew)
		{
			pNew->pNext = pBefore->pNext;
			pNew->pNext->pPre = pNew;
			pBefore->pNext = pNew;
			pNew->pPre = pBefore;
			_iListLen++;
		}

		int FindSpecNode(int iData, NODE &pOut)
		{
			if(_iListLen == 1)
			{
				return RET::FAIL;
			}
			NODE pTemp = _pHead->pNext;	
			while(pTemp != _pHead)
			{
				if(pTemp->data == iData)
				{
					pOut = pTemp;
					return RET::SUCCESS;
				}
				pTemp = pTemp->pNext;
			}
		}
		
		int PopSpecNode(NODE &pPopNode)
		{
			if(_iListLen == 0 || pPopNode == NULL)
			{
				return RET::FAIL;
			}
			NODE pAfter = pPopNode->pNext;
			NODE pBefore = pPopNode->pPre;
		
			pAfter->pPre = pBefore;
			pBefore->pNext = pAfter;
			_iListLen--;

			//if has some malloc,please free here
			pPopNode->pNext = NULL;
			pPopNode->pPre = NULL;
			free(pPopNode);
			pPopNode = NULL;

			return RET::SUCCESS;
		}

		void DLEachNode(NODE pNode)
		{
			printf("Start DLeach DList Len:%d\n",_iListLen);
			int iIndex = 0;
			if(pNode == _pHead  || pNode == NULL)
			{
				pNode = _pHead->pNext;
			}

			while(pNode != _pHead)
			{
				printf("Index:%d Node:%p Value:%d\n",iIndex,pNode,pNode->data);
				pNode = pNode->pNext;
			}
		}
		
		int DLEveryNode(NODE &pNode)
		{
			if(pNode != NULL || _iListLen == 1)
			{
				return RET::FAIL;
			}
			pNode = _pHead->pNext;
			return RET::SUCCESS;
		}
	private:
		void CreateHead()
		{
			_pHead = (NODE)malloc(sizeof(Node));
			if(_pHead != NULL)
			{
				_pHead->pNext = _pHead;
				_pHead->pPre = _pHead;
				_iListLen++;
			}
			else
			{
				cout << "DList Init error" << endl;
			}
		}

	private:
		NODE _pHead;
		int _iListLen;
};
#endif

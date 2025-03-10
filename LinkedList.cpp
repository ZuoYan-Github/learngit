#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//head = [-2, 5, -1, -10, 1, -1, 10, 2, 2, 2, 5, 5] //示例链表										  
//Definition for singly-linked list.

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
												  
class Solution
{
public:
	ListNode *head = NULL;
	ListNode* InitialList(bool IfHead, bool IFCycle);
	void removeSublists(bool IfHead, bool IFCycle);
	void PrintList(bool IfHead, bool IFCycle);
};

void Solution::PrintList(bool IfHead, bool IFCycle)
{
	ListNode *temp;

	if (IfHead)
	{
		temp = head->next;
	}
	else
	{
		temp = head;
	}

	if (IFCycle)
	{

		printf("%d ", temp->val);
		temp = temp->next;
		while (temp != head) {								//打印 
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
	else
	{

		while (temp != NULL) {								//打印 
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
}

ListNode* Solution::InitialList(bool IfHead,bool IFCycle)
{
	//主动控制链表长度，随机初始化具体元素
	//各种情况，有无头节点、是否循环（暂时考虑这四种请款,是否双向无影响）
	///先考虑无头节点、无循环的情况
	head = (ListNode*)malloc(sizeof(ListNode));			//动态内存分配 
	ListNode *temp = head;								//创建一个临时指针，并且指向头结点 

	int key;
	printf("输入链表节点值，00结束：\n");
	if (!IfHead)
	{
		scanf("%d", &temp->val);						//从键盘输入头结点的值 
	}

	scanf("%d", &key);									//从键盘输入头结点的值
	while (key != 00)									//只要不输入00就会一直创建新的结点 
	{	
		//控制下整体流程，在申请下一个节点之前先判断 是否有下一个值
		ListNode *a = (ListNode*)malloc(sizeof(ListNode));
		temp->next = a;
		temp = a;
		temp->val = key;

		scanf("%d", &key);
	}


	if (IFCycle)
	{
		temp->next = head;
	}
	else
	{
		temp->next = NULL;
	}

	PrintList(IfHead, IFCycle);

	return head;
}

void Solution::removeSublists(bool IfHead, bool IFCycle)
{
	//基本算法：从头到尾遍历整个链表，判断后对下一个元素进行删减，再与下下个元素进行判断，依次类推，一遍即可
	ListNode *temp;
	ListNode *temp1, *temp2;

	if (IfHead)
	{
		temp = head->next;
	}
	else
	{
		temp = head;
	}

	int aCycle = 0;										//Cycle的情况下判断是否还有删减

	while (temp != NULL) 
	{				
		temp1 = temp->next;
		while (temp1 != NULL&&temp->val *temp1->val == 10)
		{
			temp2 = temp1;
			temp1 = temp1->next;
			temp->next = temp1;
			if (temp2 == head)
			{
				head = head->next;
			}
			free(temp2);
			aCycle++;
		}

		temp = temp->next;

		if (temp == head)
		{
			if (aCycle == 0)
				break;

			if (IfHead)
				break;

			aCycle = 0;
		}

	}


	PrintList(IfHead, IFCycle);
}

int main()
{
	Solution test;
	bool IfHead = false, IFCycle = false;
	int key;
	printf("链表是否有头节点(0-无；1-有)：\n");
	scanf("%d", &key);
	if (key != 0)
	{
		IfHead = true;
	}
	printf("是否为循环链表(0-非；1-是)：\n");
	scanf("%d", &key);
	if (key != 0)
	{
		IFCycle = true;
	}

	test.InitialList(IfHead, IFCycle);							//是否有头节点，是否循环
	test.removeSublists(IfHead, IFCycle);
	//system("pause");

	return 1;
}

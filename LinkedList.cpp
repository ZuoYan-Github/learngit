#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
		
//链表累乘函数，输入链表当前节点，当前节点与下一个节点相乘，返回结果
int multipl(ListNode* listnode)
{
	int result;

	result = listnode->val * listnode->next->val;

	return result;
}


class Solution
{
public:
	ListNode *head = NULL;
	ListNode *end = NULL;
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
		end = temp;
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
	ListNode *temp, *pretemp;
	ListNode *temp1, *temp2 , *temp3;
	ListNode *standard1, *standard2;

	int a_Cycle;


	while (1)
	{
		bool iffree = false;
		temp = head;
		pretemp = head;
		int result, preresult = 0;
		bool cycle = false;
		if (IFCycle)
		{
			if (IfHead)
			{
				standard1 = standard2 = head;
			}
			else
			{
				standard1 = head;
				standard2 = NULL;
			}
			cycle = true;
		}
		else
		{
			standard1 = standard2 = NULL;
		}

		a_Cycle = 0;

		//暂不考虑循环
		while (temp != standard1 || cycle)
		{
			temp1 = temp->next;	
			result = temp->val;
			preresult = 0;

			cycle = false;

			while (abs(result) <= 10)
			{
				if (temp1 == standard2)
					break;

				result *= temp1->val;

				if(result == 10)
					iffree = true;

				//2 5 5

				if (preresult == 10 && (result != 10||temp1->next == standard2))
				{
					if (temp1->next == standard2&&result == 10)
					{
						temp3 = standard2;							//记录删除后的第一个节点
					}
					else
					{
						temp3 = temp1;								//记录删除后的第一个节点
					}

					if (IfHead)										//记录头
					{
						if (temp == head->next)
						{
							head->next = temp3;
						}
						else
						{
							pretemp->next = temp3;
						}
					}
					else
					{
						if (temp == head)
						{
							head = temp3;
							if (IFCycle)
							{
								standard1 = head;
								end->next = head;
							}

							cycle = true;
						}
						else
						{

							pretemp->next = temp3;
						}
					}

					//删掉从 temp 到当前 temp1 的所有节点
					while (temp != temp3)
					{
						temp2 = temp;

						if (cycle)
						{
							if (end == temp)
							{
								end = pretemp;
							}

						}
						temp = temp->next;
						free(temp2);

						a_Cycle++;
					}

					break;
				}

				if (preresult != 10)
				{
					preresult = result;
				}

				temp1 = temp1->next;
			}

			if (!iffree)
			{
				pretemp = temp;
				temp = temp->next;
			}
			iffree = false;

		}

		if (a_Cycle == 0)
			break;
	}


	//当前节点与之后的所有节点依次累乘，如果满足乘积为10，删除累成的所有节点(如果绝对值大于10退出循环)；否则进入下一个节点的判断
	//无头节点时 Head 的归属问题(第一个节点删减需要特殊考虑，其它节点不需要)
	//末尾时需要进行判断，当是末尾时指针指向 NULL
	//头节点需要记录头的指针，其余节点需要记录上个节点的指针
	//循环中有头节点的情况只是把判断依据由NULL转换为Head即可
	//循环中无头节点的情况，就直接相连了，其余不用管，将第一个NULL换为Head即可

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
	system("pause");

	return 1;
}

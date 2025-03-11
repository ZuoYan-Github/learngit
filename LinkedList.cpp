#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//head = [-2, 5, -1, -10, 1, -1, 10, 2, 2, 2, 5, 5] //ʾ������										  
//Definition for singly-linked list.

struct ListNode 
{
	int val;					

	ListNode *next;				
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
		
//�����۳˺�������������ǰ�ڵ㣬��ǰ�ڵ�����һ���ڵ���ˣ����ؽ��
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
		while (temp != head) {								//��ӡ 
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
	else
	{

		while (temp != NULL) {								//��ӡ 
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("\n");
	}
}

ListNode* Solution::InitialList(bool IfHead,bool IFCycle)
{
	//�������������ȣ������ʼ������Ԫ��
	//�������������ͷ�ڵ㡢�Ƿ�ѭ������ʱ�������������,�Ƿ�˫����Ӱ�죩
	///�ȿ�����ͷ�ڵ㡢��ѭ�������
	head = (ListNode*)malloc(sizeof(ListNode));			//��̬�ڴ���� 
	ListNode *temp = head;								//����һ����ʱָ�룬����ָ��ͷ��� 

	int key;
	printf("��������ڵ�ֵ��00������\n");
	if (!IfHead)
	{
		scanf("%d", &temp->val);						//�Ӽ�������ͷ����ֵ 
	}

	scanf("%d", &key);									//�Ӽ�������ͷ����ֵ
	while (key != 00)									//ֻҪ������00�ͻ�һֱ�����µĽ�� 
	{	
		//�������������̣���������һ���ڵ�֮ǰ���ж� �Ƿ�����һ��ֵ
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
	//�����㷨����ͷ��β�������������жϺ����һ��Ԫ�ؽ���ɾ�����������¸�Ԫ�ؽ����жϣ��������ƣ�һ�鼴��
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

		//�ݲ�����ѭ��
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
						temp3 = standard2;							//��¼ɾ����ĵ�һ���ڵ�
					}
					else
					{
						temp3 = temp1;								//��¼ɾ����ĵ�һ���ڵ�
					}

					if (IfHead)										//��¼ͷ
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

					//ɾ���� temp ����ǰ temp1 �����нڵ�
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


	//��ǰ�ڵ���֮������нڵ������۳ˣ��������˻�Ϊ10��ɾ���۳ɵ����нڵ�(�������ֵ����10�˳�ѭ��)�����������һ���ڵ���ж�
	//��ͷ�ڵ�ʱ Head �Ĺ�������(��һ���ڵ�ɾ����Ҫ���⿼�ǣ������ڵ㲻��Ҫ)
	//ĩβʱ��Ҫ�����жϣ�����ĩβʱָ��ָ�� NULL
	//ͷ�ڵ���Ҫ��¼ͷ��ָ�룬����ڵ���Ҫ��¼�ϸ��ڵ��ָ��
	//ѭ������ͷ�ڵ�����ֻ�ǰ��ж�������NULLת��ΪHead����
	//ѭ������ͷ�ڵ���������ֱ�������ˣ����಻�ùܣ�����һ��NULL��ΪHead����

	PrintList(IfHead, IFCycle);
}

void main()
{
	Solution test;
	bool IfHead = false, IFCycle = false;
	int key;
	printf("�����Ƿ���ͷ�ڵ�(0-�ޣ�1-��)��\n");
	scanf("%d", &key);
	if (key != 0)
	{
		IfHead = true;
	}
	printf("�Ƿ�Ϊѭ������(0-�ǣ�1-��)��\n");
	scanf("%d", &key);
	if (key != 0)
	{
		IFCycle = true;
	}
	
	test.InitialList(IfHead, IFCycle);							//�Ƿ���ͷ�ڵ㣬�Ƿ�ѭ��
	test.removeSublists(IfHead, IFCycle);
	system("pause");
}

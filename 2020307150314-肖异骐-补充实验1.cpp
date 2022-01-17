#include <iostream>
using namespace std;

/*
* 已知n个人围城环，从第k个人开始报数，数到m时出列，直到所有人出列
*/
class Per
{
public:
	int number;//记录序号
	Per* next;
	Per* pre;
};
class circle//双向循环链表
{
public:
	int length;//队伍的长度
	Per* head;
	Per* tail;
	circle()//初始化链表
	{
		length = 0;
		head = new Per();
		tail = head;
	}
	void pushback(int n)//在链表末尾加一个序号为n的人
	{
		Per* tmp = new Per();
		tmp->number = n;
		tail->next = tmp;
		tmp->pre = tail;
		tail = tmp;
		tmp->next = head->next;
		head->next->pre = tail;
		length++;
	}
	void Kill(int k, int m)//从序号为k的开始报数，报到m的删除
	{
		Per* tmp = head;
		for (int i = 1; i < k; i++)//数到第k-1个
		{
			tmp = tmp->next;
		}
		while (1)
		{
			for (int i = 1; i <= m; i++)//从上一个开始向后数m个
			{
				tmp = tmp->next;
			}
			cout << tmp->number << " ";
			length--;
			if (length == 0) {
				break;
			}
			tmp->pre->next = tmp->next;//删除该节点
			tmp->next->pre = tmp->pre;
		}
	}
};
int main()
{
	int n,k,m;
	cout << "please typing n k m"<<endl;
	cin >> n >>k>>m;//输入数据
	if (k <= 0 || m <= 0 ||k>n)//判断输入是否合法
	{
		while(1)
		{
			cout << "Your input is illegal,please type significant number." << endl;
			cout << "Please enter it again.(k , m > 0)" << endl;
			cin >> n >> k >> m;
			if (k > 0 && m > 0&&k<=n) break;
		}
	}
	circle test;
	for (int i = 1; i <= n; i++)
	{
		test.pushback(i);
	}
	test.Kill(k, m);
}
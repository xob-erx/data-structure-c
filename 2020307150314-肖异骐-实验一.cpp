#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;
/*
* 作者：大数据201 肖异骐 2020307150314
* 创建时间：2021/9/25
*/
/*
* 问题：
* 1.创建动态int数组怎么全部初始化为0
* 2.SearchFv()可以改为return一个图书和数量的map。
* 3.SearchBst()可以改成return book*
* 4.动态初始化数组怎么全部赋值为0
* 5.排序除了气泡法还有别的算法吗
* 6.new 的时候要做异常处理
* 7.从txt中读取信息中文编码错误
* 8.插入时如果输入价格时输入非法，怎么提高健壮性
*/

class Book
{
public:
	char* no;
	char* name;
	float price;
	Book(char* a, char* b, float p) :no(a),name(b),price(p){		
	}//构造函数
	Book(){}
	int Set()//输入
	{
		char* a = new char[20];
		char* b = new char[50];
		float p;
		std::cin >> a >> b >> p;
		if (p == 0) return 1;//输入异常时返回1
		else {
			no = a; name = b; price = p;
			return 0;
		}
	}
	void Show()//按要求输出Book的信息
	{
		std::cout << no << " " << name << " ";
		std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) << price << std::endl;
	}
};
class SList
{
	Book* elem;
	int length;
public:
	SList()//构造链表
	{
		try {
			elem = new Book[100];//长度为100
		}
		catch (const bad_alloc& e)
		{
			cout << "Memory allocation failed." << endl;
			exit;
		}
		length = 0;//长度
	}
	int getlength() {
		return length;
	}
	void Set()//输入顺序表
	{
		while (1)
		{
			Book temp;
			if (temp.Set() == 1) break;
			elem[length] = temp;
			length++;
		}
	}
	void Show()//输出顺序表
	{
		for (int i = 0; i < length; i++)
		{
			elem[i].Show();
		}
	}
	void Sort()//按价格排序
	{
		//冒泡法
		for (int i = 0; i < length - 1; i++)
		{
			for (int j = i + 1; j < length; j++)
			{
				if (elem[i].price < elem[j].price)
				{
					Book tmp;
					tmp = elem[i];
					elem[i] = elem[j];
					elem[j] = tmp;
				}
			}
		}
	}
	float RisePrice()//涨价并返回涨价前的平均值
	{
		float avg = 0;//定义平均值
		for (int i = 0; i < length; i++)
		{
			avg += elem[i].price;
		}
		avg /= length;
		for (int i = 0; i < length; i++)//涨价
		{
			if (elem[i].price < avg)
			{
				elem[i].price *= 1.2;
			}
			else {
				elem[i].price *= 1.1;
			}
		}
		return avg;
	}
	void Invert()//逆序排列
	{
		for (int i = 0; i < length / 2; i++)//将表中首尾交换位置
		{
			Book temp;
			temp = elem[i];
			elem[i]= elem[length - 1 - i];
			elem[length - 1 - i] = temp;
		}
	}
	Book SearchEx()//查找最贵的书
	{
		float max = elem[0].price;//设置初始最大值
		int maxsize = 0;//设置最大值位置
		for (int i = 1; i < length; i++)//遍历寻找最大值
		{
			if (elem[i].price > max)
			{
				max = elem[i].price;
				maxsize = i;
			}
		}
		return elem[maxsize];
	}
	void SearchFv()//查找最喜欢的书
	{
		//输入查找数量和书名 
		cout << "Please type the number to find "<<endl;
		int num;
		cin >> num;
		string* Sname = new string[num];//储存需要搜索的书
		Book* tmp = new Book[num];//储存搜索到的书
		int* counter = new int[num]; //储存搜索到的书的数目,并全初始化为0
		for (int i = 0; i < num; i++)
		{
			counter[i] = 0;
			cout << "Start typing book" << i + 1  << endl;
			cin >> Sname[i];
		}
		//开始查找
		cout << "Start finding......."<<endl;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (!strcmp(Sname[i].c_str(), elem[j].name))
				{
					tmp[i] = elem[j];
					counter[i]++;
				}
			}
		}
		for (int i = 0; i < num; i++)
		{
			if (counter[i] == 0) {
				cout << "Sorry, I didn't find your favorite!" << endl;
			}
			else {
				cout << counter[i] << endl;
				tmp[i].Show();
			}
		}

	}
	void SearchBst()//查找最佳位置
	{
		//输入查找数量和书的序号
		cout << "Please type the number to find" << endl;
		int num;
		cin >> num;
		int* site = new int[num];
		//Book* tmp = new Book[num];//储存搜索到的书
		for (int i = 0; i < num; i++)//输入
		{
			cout << "Start typing book " << i + 1 << endl;
			cin >> site[i];
		}
		cout << "Start finding......."<<endl;
		for (int i = 0; i < num; i++)
		{
			if (site[i] <= 0 || site[i] > length)
			{
				cout << "Sorry, the book in the best location does not exist"<<endl;
			}
			else
			{
				elem[site[i]].Show();
			}
		}
		
	}
	void insert()//插入新图书
	{
		//输入插入位置和信息
		int site;
		Book ins;
		cout << "Type the insertion location" << endl;
		cin >> site;
		if (site <= 0 || site > (length + 1))
		{
			cout << "Sorry, the storage location is illegal" << endl;
		}
		//输入图书信息
		else
		{
			cout << "Type insert book information" << endl;
			ins.Set();
			for (int i = (length - 1); i >= (site - 1);i--)
			{
				elem[i + 1] = elem[i];
			}
			elem[site - 1] = ins;
			length++;
			cout << "Insert successful" << endl;
		}
	}
	void del(int site)//删除指定图书
	{
		if (site <= 0 || site > length)
		{
			cout<<"Sorry, the outbound location is illegal!" << endl;
		}
		else
		{
			for (int i = site - 1; i < length; i++)
			{
				elem[i] = elem[i + 1];
			}
			length--;
			cout << "Delete successful" << endl;
		}
	}
	void unique()//去重
	{
		int* sign = new int[length];//用于标记哪些是重复的1为重复，0为不重复
		for (int i = 0; i < length; i++)//全部赋值为0
		{
			sign[i] = 0;
		}
		for (int i = 0; i < length-1; i++)//双循环比较
		{
			if (sign[i] == 0)//如果前面出现有则会跳过
			{
				for (int j = i + 1; j < length; j++)
				{
					if (strcmp(elem[i].no , elem[j].no)==0)
					{
						sign[j]++;
					}
				}
			}
		}
		Book *tmp = new Book[100];
		int tlen = 0;
		for (int i = 0; i < length; i++)
		{
			if (sign[i] == 0)
			{
				tmp[tlen] = elem[i];
				tlen++;
			}
		}
		this->elem = tmp;
		length = tlen;
	}
};
int main()
{
	SList test;
	cout << "1.Type book information" << endl
		<< "2.Show information" << endl
		<< "3.Sort" << endl
		<< "4.Price increase" << endl
		<< "5.Reverse order storage" << endl
		<< "6.Find the most expensive book" << endl
		<< "7.Find your favorite books" << endl
		<< "8.Find the best location" << endl
		<< "9.Insert new book" << endl
		<< "10.Delete book information" << endl
		<< "11.Unique" << endl
		<< "12.Exit program" << endl;
	while (true)
	{
		cout << "---------------------------------------" << endl
			<< "Please select an action......" << endl;
		int op;
		cin >> op;
		switch (op) {
		case 1:
			cout << "Begin typing" << endl;
			test.Set();
			break;
		case 2:
			test.Show();
			break;
		case 3:
			test.Sort();
			cout << "Sort successful" << endl;
			break;
		case 4:
			cout<<"the average price is" << test.RisePrice() << endl;
			cout << "Price modified successfully" << endl;
			break;
		case 5:
			test.Invert();
			cout << "Reverse successful" << endl;
			break;
		case 6:
			cout << "The expensive book is" << endl;
			test.SearchEx().Show();
			break;
		case 7:
			test.SearchFv();
			break;
		case 8:
			test.SearchBst();
			break;
		case 9:
			test.insert();
			break;
		case 10:
			int site;
			cout << "Typing the location to delete" << endl;
			cin >> site;
			test.del(site);
			break;
		case 11:
			test.unique();
			cout << "unique successful" << endl;
			break;
		case 12:
			cout << "Exit program" << endl;
			return 0;
		default:
			cout << "-_-,Please enter a valid number" << endl;
		}
	}

}
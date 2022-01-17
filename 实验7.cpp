/*
titlie:基于Dijsktra算法求最短路径
author：肖异骐 2020307150314
create time：2021/11/25
*/
/*
* 内容：输入有多少城市有多少路径，并输入要求的两城市，输出最短路径长度和路径
* 问题：1. 输入城市name时多输了有bug
* 2.输入路径时名字输错了没办法报错
*/
#include <iostream>
#include <String>
#include <fstream>
#define MaxInt 32767
using namespace std;

template <typename T>
class AMGraph
{
	int citynum , roadnum;//城市的数量,路径的数量
	T *Vertex;//v节点
	int **Edge;//e边
public:
	AMGraph(int cityn,int roadn)
	{
		citynum = cityn; roadnum = roadn;
		Vertex = new T[citynum];//对一维二维数组进行初始化
		Edge = new int*[citynum];
		for (int i = 0; i < citynum; i++) {
			Edge[i] = new int[citynum];
		}
		for (int i = 0; i < citynum; i++)//把邻接矩阵全初始化为无穷远
		{
			for (int j = 0; j < citynum; j++) {
				Edge[i][j] = MaxInt;
			}
		}
	}
	void inCityname(string* city)
	{
		for (int i = 0; i < citynum; i++)
		{
			Vertex[i] = city[i];
		}
	}
	void cinCityname()//输入cityname
	{
		for (int i = 0; i < citynum; i++) {
			//cout << "please type the " << i << " city name";
			cin >> Vertex[i];
		}
	}
	void getCityname()//输出城市名字
	{
		for (int i = 0; i < citynum; i++)
		{
			cout << Vertex[i] <<" ";
		}
		cout << endl;
	}
	void getAMGraph()//输出矩阵
	{
		for (int i = 0; i < citynum; i++)
		{
			for (int j = 0; j < citynum; j++)
			{
				cout << Edge[i][j]<<" ";
			}
			cout << endl;
		}
	}
	int getcitySerialnum(string s)//获取该城市的序号
	{
		for (int i = 0; i < citynum; i++)
		{
			if (s.compare(Vertex[i]) == 0)//判断相等
			{
				return i;
			}
		}

	}
	void pushbackRoad(string x, string y, int distance)
	{
		Edge[getcitySerialnum(x)][getcitySerialnum(y)] = distance;
	}
	void cinRoad()//输入路径
	{
		for (int i = 0; i < roadnum; i++)
		{
			string x, y; int distance;
			cin >> x >> y >> distance;
			Edge[getcitySerialnum(x)][getcitySerialnum(y)] = distance;
		}
	}
	int ShortPath(string b, string e,int& nodnum,string *roadpath)
	{
		int begin = getcitySerialnum(b);//定义开始的节点和结束的节点
		int end = getcitySerialnum(e);
		bool* S = new bool[citynum];//用于存储是否找到最短路径
		int* Path = new int[citynum];//用于存储该节点最短路径的上一节点
		int* D = new int[citynum];//存储到起点的最短路径
		int t = begin;
		for (int i = 0; i < citynum; i++)//初始化
		{
			S[i] = false;
			Path[i] = -1;
			D[i] = MaxInt;
		}
		S[t] = true; Path[t] = t; D[t] = 0;
		while (t != end)//Dijsktra
		{
			for (int i = 0; i < citynum; i++)
			{
				if (Edge[t][i] < MaxInt && S[i] == false && Edge[t][i] + D[t] < D[i])
				{
					Path[i] = t;
					D[i] = Edge[t][i] + D[t];
				}
			}
			int tmp = -1; int min = MaxInt;//确定一个最短路径
			for (int i = 0; i < citynum; i++)
			{
				if (S[i] == false)
				{
					if (D[i] < min)
					{
						min = D[i];
						tmp = i;
					}
				}
			}
			if (tmp == -1)//说明没有通路了
			{
				return 0;
			}
			S[tmp] = true;
			t = tmp;
		}

		int* road = new int[citynum];
		int nod = end; nodnum = 0;
		while (nod != begin)
		{
			road[nodnum++] = nod;
			nod = Path[nod];
		}
		road[nodnum] = begin;
		for (int i = 0; i <= nodnum; i++)
		{
			roadpath[nodnum-i] = Vertex[road[i]];
		}
		return D[end];
	}
};
int main()
{
	int p;
	std::cout << "File input,please type 0 , keyboard entry,please type 1"<<endl;
	cin >> p;
	if (p == 0)//文件输入
	{
		std::cout << "Please type your file address.(ps:testdata.txt)" << endl;
		string filename;
		cin >> filename;
		ifstream testfile(filename);
		if (!testfile.is_open())
		{
			std::cout << "can not open this file" << endl;
			return 0;
		}
		while (1)
		{
			int citynum, roadnum;//定义城市和路的数量
			//cout << "Please enter the number of cities and the number of roads" << endl;
			testfile >> citynum >> roadnum;
			if (citynum == 0 && roadnum == 0)	break;
			AMGraph<string> g(citynum, roadnum);//定义邻接矩阵
			string* city = new string[citynum];
			for (int i = 0; i < citynum; i++)
			{
				testfile >> city[i];
			}
			g.inCityname(city);
			//g.cinCityname();
			for (int i = 0; i < roadnum; i++)
			{
				string x, y; int distance;
				testfile >> x >> y >> distance;
				g.pushbackRoad(x, y, distance);
			}
			//g.cinRoad();
			string begin, end;//定义开始与结束的城市名并输入
			testfile >> begin >> end;
			string* roadpath = new string[citynum];//用于存储路径
			int nodnum;//用于存储路径的节点数
			if (g.ShortPath(begin, end, nodnum, roadpath) == 0) {//发现没有通路
				std::cout << "No access found" << endl;
			}
			else {
				std::cout << "the shortest path is ";
				std::cout << g.ShortPath(begin, end, nodnum, roadpath) << endl << "the road path is: ";
				for (int i = 0; i <= nodnum; i++)
				{
					std::cout << roadpath[i];
					if (i != nodnum)	std::cout << "-->";
				}
				std::cout << endl;
			}
		}
	}
	else if (p == 1)//键盘输入
	{
		while (1)
		{
			int citynum, roadnum;//定义城市和路的数量
			std::cout << "Please enter the number of cities and the number of roads" << endl;
			cin >> citynum >> roadnum;
			if (citynum == 0 && roadnum == 0)	break;
			AMGraph<string> g(citynum, roadnum);//定义邻接矩阵
			g.cinCityname();
			g.cinRoad();
			string begin, end;//定义开始与结束的城市名并输入
			cin >> begin >> end;
			string* roadpath = new string[citynum];//用于存储路径
			int nodnum;//用于存储路径的节点数
			if (g.ShortPath(begin, end, nodnum, roadpath) == 0) {//发现没有通路
				std::cout << "No access found" << endl;
			}
			else {
				std::cout << "the shortest path is ";
				std::cout << g.ShortPath(begin, end, nodnum, roadpath) << endl << "the road path is: ";
				for (int i = 0; i <= nodnum; i++)
				{
					std::cout << roadpath[i];
					if (i != nodnum)	std::cout << "-->";
				}
				std::cout << endl;
			}
		}
	}
	else {
		std::cout << "please type 0 or 1;" << endl;
	}
	
}
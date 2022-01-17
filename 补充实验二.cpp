/*随机生成迷宫求最短路径
author:肖异骐 2020307150314
create time:2021-10-27*/

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Queue//define sqqueue
{
public:
	T* base;
	int front;//queue top
	int rear;//queue tail
	int maxsize;
	Queue(int len) {
		try {
			base = new T[len];
			front = rear = 0;
			maxsize = len;
		}
		catch (const bad_alloc& e) {
			cout << "Memory allocation failed." << endl;
			exit;
		}
	}
	int getlength()
	{
		return (rear - front + maxsize) % maxsize;
	}
	void Push(T data)//enter the queue
	{
		if ((rear + 1) % maxsize == front)	cout << "The queue is full,failed to enter the queue" << endl;
		else {
			base[rear] = data;
			rear = (rear + 1) % maxsize;
		}
	}
	T Pop()//out of the queue
	{
		if (rear == front)//the queue is empty
		{
			cout << "The queue is empty,failed to out of the queue" << endl;
			return 0;
		}
		else
		{
			T data = base[front];
			front = (front + 1) % maxsize;
			return data;
		}
	}

};
class Point//define piont
{
public:
	int x_n, y_n;
	Point(){}
	Point(int x, int y) :x_n(x), y_n(y) {}
	bool operator==(Point p)//重载 == 判断两点是否相等
	{
		if (x_n == p.x_n && y_n == p.y_n)	return true;
		else
		{
			return false;
		}
	}
	bool operator!=(Point p)
	{
		if (x_n == p.x_n && y_n == p.y_n) return false;
		else return true;
	}
	Point Moveup() {
		Point p(x_n, y_n-1);
		return p;
	}
	Point Movedown() {
		Point p(x_n, y_n+1);
		return p;
	}
	Point Moveleft() {
		Point p(x_n-1,y_n);
		return p;
	}
	Point Moveright() {
		Point p(x_n+1, y_n);
		return p;
	}
};
class Path//定义路径点和上个到达点
{
public:
	Point position;
	int pre;
	Path(){}
	Path(Point tmp, int p) {
		position.x_n = tmp.x_n;
		position.y_n = tmp.y_n;
		pre = p;
	}
};
/*
直接随机生成迷宫可能会导致迷宫没有通路，且不美观
下面我使用的算法让迷宫形成树的形状且可以随机生成起点和终点
简单来说就是先让迷宫由四面都是墙的房间组成，
然后再从起点开始对墙打洞，直到不能打洞为止*/
class Maze//define	
{
private:
	int graph[100][100];
	int x_size, y_size;//必须是奇数
	Point start;//起点
	Point end;//终点
public:
	Maze(int x,int y) {
		x_size = x; y_size = y;
		start.x_n = rand() % (x_size)+1; start.y_n = 0;//随机生成在x轴的起点
		for (int i = 0; i <= x_size+1; i++)//将迷宫设置成每个空地旁边都有墙 
		{
			if (i % 2 == 0) {
				for (int j = 0; j <= y_size + 1; j++)
				{
					graph[i][j] = 2;
				}
			}
			else {
				for (int j = 0; j <= y_size + 1; j++) {
					if (j % 2 == 0) {
						graph[i][j] = 2;
					}
					else
					{
						graph[i][j] = 1;
					}
				}
			}
		}
		for (int i = 0; i <= y_size + 1; i++)//将最外层墙变为3
		{
			graph[0][i] += 1;
			graph[x_size+1][i] += 1;
		}
		for (int i = 1; i <= x_size; i++)
		{
			graph[i][0] += 1;
			graph[i][y_size + 1] += 1;
		}
		srand((unsigned)time(NULL));//随机数种子
		delWall(start);
		vector<Point> wall;//用于存放可以删除的墙的位置
		Point crash = start.Movedown();//第一个打通的墙
		delWall(crash);
		if (getnum(crash) == 2) 
		{
			delWall(crash.Moveleft());
			delWall(crash.Moveright());
			getwall(crash.Moveleft(), &wall);
			getwall(crash.Moveright(), &wall);
		}
		else {
			//delWall(crash);
			getwall(crash,&wall);
		}
		while (wall.size() != 0)
		{
			int size = rand() % wall.size();//从删除待选墙中随机选一个
			Point tmp = wall[size];
			if (getnum(tmp.Movedown()) + getnum(tmp.Moveup()) == 1)//判断这面墙是否可以打通和方向
			{
				delWall(tmp);
				if (getnum(tmp.Movedown()) == 1) {
					delWall(tmp.Movedown());
					getwall(tmp.Movedown(), &wall);
				}
				else {
					delWall(tmp.Moveup());
					getwall(tmp.Moveup(), &wall);
				}
			}
			else if (getnum(tmp.Moveleft()) + getnum(tmp.Moveright()) == 1)
			{
				delWall(tmp);
				if (getnum(tmp.Moveright()) == 1) {
					delWall(tmp.Moveright());
					getwall(tmp.Moveright(), &wall);
				}
				else {
					delWall(tmp.Moveleft());
					getwall(tmp.Moveleft(), &wall);
				}
			}
			wall.erase(wall.begin() + size);//删除该点
		}
		end.x_n = (rand() + 1) % x_size / 2 + 1;//随机选取终点
		end.y_n = y_size + 1;
		delWall(end);
		//cout << wall.size()<<endl;
	}
	void getwall(Point p, vector<Point> *wall) //获取该点旁边能打通的墙并压入待打通墙数组
	{
		if (getnum(p.Movedown()) == 2) {
			wall->push_back(p.Movedown());
		}
		if (getnum(p.Moveup()) == 2) {
			wall->push_back(p.Moveup());
		}
		if (getnum(p.Moveleft()) == 2) {
			wall->push_back(p.Moveleft());
		}
		if (getnum(p.Moveright()) == 2) {
			wall->push_back(p.Moveright());
		}
	}
	int getnum(Point p) //获取该点迷宫的数字
	{
		return graph[p.x_n][p.y_n];
	}
	void delWall(Point p)//打通墙
	{
		graph[p.x_n][p.y_n] = 0;
	}
	void drawpath(Point p)//绘制路线
	{
		graph[p.x_n][p.y_n] = 1;
	}
	void mark(Point p)//用于标记已经搜寻过的点
	{
		graph[p.x_n][p.y_n] = -1;
	}
	void Show()//输出图形
	{
		for (int i = 0; i <= y_size + 1; i++)
		{
			for (int j = 0; j <= x_size + 1; j++)
			{
				if (graph[j][i] == 0||graph[j][i]==-1)//0,-1表示通路，-1是标记过的通路 
				{
					cout<<"  ";
				}
				else if(graph[j][i]==1){//1表示最短路径
					cout << "**";
				}
				else {//其余的是墙
					cout << "##";
				}
				//cout << graph[j][i]<<" ";
			}
			cout << endl;
		}
	}
	int Shortestpath()//获取最短路径 
	{
		Queue<Path> Q(400);
		Path Start(start, -1);
		Q.Push(Start);
		int i = 0;
		mark(Q.base[i].position);
		do//开始寻路
		{
			if (getnum(Q.base[i].position.Movedown()) == 0)//找i位置的周围可联通的点，并将其压入队列
			{
				mark(Q.base[i].position.Movedown());//标记该点
				Path tmp(Q.base[i].position.Movedown(), i);
				Q.Push(tmp);//压入
			}
			if (getnum(Q.base[i].position.Moveleft()) == 0)
			{
				mark(Q.base[i].position.Moveleft());
				Path tmp(Q.base[i].position.Moveleft(), i);
				Q.Push(tmp);
			}
			if (getnum(Q.base[i].position.Moveright()) == 0)
			{
				mark(Q.base[i].position.Moveright());
				Path tmp(Q.base[i].position.Moveright(), i);
				Q.Push(tmp);
			}
			if (getnum(Q.base[i].position.Moveup()) == 0)
			{
				mark(Q.base[i].position.Moveup());
				Path tmp(Q.base[i].position.Moveup(), i);
				Q.Push(tmp);
			}
			i++;
		} while (Q.base[i].position.Movedown() != end);//当找到终点上一个的点终止
		int len=0;
		while (i!=0)//绘制最短路径
		{
			drawpath(Q.base[i].position);
			i = Q.base[i].pre;
			len++;
		}
		return len;//返回长度
	}
};
int main()
{
	Maze m(21, 21);
	m.Show();
	cout<<"The shourtestpath is " << m.Shortestpath() << endl;
	cout << "Drawing route......"<<endl;
	m.Show();
	
}
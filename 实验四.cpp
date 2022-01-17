/*基于字符串匹配模式算法的病毒感染问题
author: 肖异骐
create timt:2021-11-2*/
#include <iostream>
using namespace std;

class String//define qsstring class
{
private:
	char* str;
	int length;
public:
	String(int maxlen)
	{
		str = new char[maxlen + 1];
		length = 0;
	}
	int getlen()
	{
		return length;
	}
	void getnext(int next[]) 
	{
		//next = new int[length];
		int i = 0,j=-1; next[0] = -1;
		while (i < length - 1)
		{
			if (j == -1 || str[i] == str[j]) {
				++i; ++j; next[i] = j;
			}
			else j = next[j];
		}
	}
	void copystr()
	{
		for (int i = 0; i < length; i++)
		{
			str[i + length] = str[i];
		}
		length += length;
	}
	friend int Index_BF(String s, String t, int pos,int len);
	friend int Index_KMP(String S, String T, int next[]);
	friend istream& operator>>(istream& in, String& S);
};
istream& operator>>(istream& in, String& S)
{
	in >> S.str;
	while (S.str[S.length] != '\0') {
		S.length++;
	}
	return in;
}
int Index_BF(String s, String t, int pos,int len)//此处模式串t以被复制以得到环状的模拟，pos为从t的pos位开始查询，查询的长度为t复制前的长度
{
	int i, j;
	i = 0; //下标 
	j = pos; //下标 
	while (i < s.getlen() && j < pos+len) {
		if (s.str[i] == t.str[j]) { ++i; ++j; }	//继续比较后继字符 
		else { i = i - j + pos + 1; j = pos; }	//指针后退重新开始匹配
	}
	if (j == pos +len) return i - len; //模式串全部读完，表示匹配，返回开始匹配位置的下标 
	else return -1;
}

int Index_KMP(String S, String T, int next[])//
{
	int i, j;
	i = j = 0;
	while (i <= S.length - 1 && j <= T.length - 1)
	{
		if (j == -1 || S.str[i] == T. str[j]) {	//从各自的第一位开始比较，如果相同，比较下一位 
			++i;
			++j;
		}
		else {
			j = next[j];
		}
	}
	if (j > T.length - 1)		//匹配成功 
		return i - T.length + 1;// 
	else			//匹配失败 
		return 0;
}
void VirusDetection(String s, String t)//病毒检测
{
	int tlen = t.getlen();
	t.copystr();//将t复制一份加在t的尾部
	for (int i = 0; i < tlen; i++)
	{
		if (Index_BF(s, t, i, tlen) != -1)
		{
			cout << "YES" << endl;
			break;
		}
	}
	cout << "NO" << endl;
}
int main()
{
	while (1)
	{
		String s(100), t(100);
		cin >> t >> s;
		if (s.getlen() == 1 && t.getlen() == 1)break;
		VirusDetection(s, t);
	}
}
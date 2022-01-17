/*基于哈夫曼树的数据压缩算法
author：肖异骐 2020307150314
create time:2021-11-11*/

/*问题：
1.CountNum感觉可以使用递归
2.构造哈夫曼树37行的循环可以改进，可以不用双循环
3.解码效率，可以先将编码长度排序，这样效率会接近KMP
*/
#include <iostream>
using namespace std;
template <typename T>
class HFnode
{
public:
	int weight, parent, lchild, rchild;
	char* code; int codelen;//用于存储编码，和编码长度
	T data;
};

class HuffmanTree 
{
public:
	int length;
	HFnode<char>* HT;
	HuffmanTree(int n,char *out,int *sum)//n 是输入叶子的长度，out是输入的字符，sum是其权
	{
		length = 2 * n - 1;
		HT = new HFnode<char> [length + 1];
		for (int i = 1; i <= length; i++)
		{
			HT[i].parent = 0; HT[i].lchild = 0; HT[i].rchild = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			HT[i].data = out[i-1]; HT[i].weight = sum[i-1];
		}
		for (int i = n + 1; i <= length; i++)//找1--i中HT权最小的两个以及父亲节点为0
		{
			int s1=0, s2=0, min1 = 100, min2 = 100;
			for (int j = 1; j <= i - 1; j++)
			{
				if (HT[j].parent == 0 && HT[j].weight < min2)
				{
					if (HT[j].weight < min1) {
						s2 = s1; min2 = min1;
						s1 = j; min1 = HT[j].weight;
					}
					else {
						s2 = j; min2 = HT[j].weight;
					}
				}
			}//开始赋值
			HT[s1].parent = i; HT[s2].parent = i;
			HT[i].lchild = s1; HT[i].rchild = s2;
			HT[i].weight = HT[s1].weight + HT[s2].weight;
		}
	}
	void Show()//输出哈夫曼树的数据
	{
		for (int i = 1; i <= length; i++)
		{
			cout << i <<" " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild << " " << HT[i].rchild << endl;
		}
	}
	void Code(int Fa,char *code,int pionter)//通过哈夫曼树进行编码,Fa是父亲节点的编号，code是父亲节点形成的编码，pionter是编码目前的长度
	{
		if (HT[Fa].lchild == 0 && HT[Fa].rchild == 0)//是叶子，将编码存进
		{
			HT[Fa].code = new char[pionter];
			for (int i = 0; i < pionter; i++)//将code复制进HTcode
			{
				HT[Fa].code[i] = code[i];
			}
		}
		else//不是叶子，编码需要继续添加
		{
			HT[HT[Fa].lchild].code = new char[pionter + 1];
			HT[HT[Fa].lchild].codelen = pionter + 1;
			HT[HT[Fa].rchild].code = new char[pionter + 1];
			HT[HT[Fa].rchild].codelen = pionter + 1;
			for (int i = 0; i < pionter; i++)
			{
				HT[HT[Fa].lchild].code[i] = code[i];
				HT[HT[Fa].rchild].code[i] = code[i];
			}
			HT[HT[Fa].lchild].code[pionter] = '0';
			HT[HT[Fa].rchild].code[pionter] = '1';
			Code(HT[Fa].lchild, HT[HT[Fa].lchild].code, pionter + 1);
			Code(HT[Fa].rchild, HT[HT[Fa].rchild].code, pionter + 1);
		}
	}
	void AllCode()//输出所有的编码
	{
		for (int i = 1; i <= (length + 1) / 2; i++)
		{
			cout << HT[i].data << ":";
			for (int j = 0; j < HT[i].codelen; j++) {
				cout << HT[i].code[j];
			}
			cout << " ";
		}
		cout << endl;
	}
	char* GetCode(char* str,int length)//获取str在该哈夫曼树的编码,lenght是str的长度
	{
		char* code = new char[1000]; int pionter = 0;
		for (int i = 0; i < length; i++)
		{
			for (int j = 1; j <= (length + 1) / 2; j++)
			{
				if (HT[j].data == str[i])
				{//输出编码
					for (int k = 0; k < HT[j].codelen; k++) {
						code[pionter++] = HT[j].code[k];
					}
					break;
				}
			}
		}
		return code;
	}
	char* Decode(char *code,int codeLen)//对编码进行解码,codeLen是编码的长度
	{
		char* str = new char[1000]; //解码后的源文本
		int i = 0, strLen = 0;
		while (i < codeLen)//BF算法
		{
			for (int j = 1; j <= (length + 1) / 2; j++)//从HT[j]的编码开始判断，因为是前置编码，所以只要有判断不对的就跳到下一个
			{
				int pionter = 0;
				while (HT[j].code[pionter] == code[i + pionter])
				{
					pionter++;
					if (pionter == HT[j].codelen)
					{
						str[strLen++] = HT[j].data;
						i += pionter;
						j = length;//用于跳出双循环
						break;
					}
				}
			}
		}
		return str;
	}
};
int CountNum(char* str, char* out, int* num,int length)//计算str中出现的字符及其数量，str是输入的字符串，out是输出的字符串，num是对应的数量，length是str的长度
{
	int pionter = 0;
	for (int i = 0; i < length; i++)
	{
		int j = 0;
		for (j = 0; j < pionter; j++)
		{
			if (str[i] == out[j]) {
				num[j]++;
				break;
			}
		}
		if (j >= pionter - 1 && str[i] != out[pionter-1]) {
			out[pionter] = str[i];
			num[pionter] = 1;
			++pionter;
		}
	}
	return pionter;
}
int Getlength(char* str)//获取字符串长度
{
	int len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}
int main()
{
	int Counter = 1;
	while (1)
	{
		char* str = new char[100];
		cout << "Please enter the " << Counter << " string" << endl; Counter++;
		cin >> str;
		if (str[0] == '0')
		{
			break;
		}
		int length = Getlength(str);//获取字符串的长度
		char* out = new char[length]; int* num = new int[length];
		int Len = CountNum(str, out, num, length);//out是出现过的字符，num是对应的数量
		for (int i = 0; i < Len; i++) {//输出出现过的字符以及对应出现的数量
			cout << out[i] << ":" << num[i] << " ";
		}
		cout << endl;
		HuffmanTree H1(Len, out, num);//构造哈夫曼树
		H1.Show();//按课本要求输出
		char* emptycode = new char[0];//创建一个编码的初始字符串
		H1.Code(H1.length, emptycode, 0);
		H1.AllCode();//输出各个字符的编码
		char* code = H1.GetCode(str, length);//获取str的编码
		int codeLen = 0;
		while (code[codeLen] == '0' || code[codeLen] == '1') {//输出编码并获取编码长度
			cout << code[codeLen]; codeLen++;
		}
		cout << endl;
		char* str1 = H1.Decode(code, codeLen);
		for (int i = 0; i < length; i++) {
			cout << str1[i];
		}
		cout << endl;
	}
	
	
}
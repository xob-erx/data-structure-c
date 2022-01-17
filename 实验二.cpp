/*
基于栈的中辍算术表达式求值
author：肖异骐 2020307150314
create time：2021-10-19
*/
#include<iostream>
using namespace std;
/*
1.输入宽容度不够，健壮性不强
2.Precede不够优美
*/
//Define template stack
template <typename T>
class Stack
{
	T* top;//Stack top pointer
	T* base;//Stack bottom pointer
	T Size;
public:
	Stack(int len):Size(len)//Constructor the stack Size=len
	{
		try{
			base = new T[len];//Allocate memory
			top = base;
		}
		catch (const bad_alloc& e)//Catch exception
		{
			cout << "Memory allocation failed." << endl;
			exit;
		}
	}
	int Push(T e)
	{
		if (top - base == Size) {
			cout << "The stack is full"<< endl;
			return 0;//error
		}
		*top++ = e;
		return 1;
	}
	T Pop()
	{
		if (top == base) {
			cout << "The stack is empty"<<endl;
			return 0;//error
		}
		return *--top;
	}
	T GetTop()
	{
		return *(top-1);
	}
};
char Precede(char s1, char s2)//compare the priority of operators
{
	if (s1 == '+' || s1 == '-')
	{
		if (s2 == '+' || s2 == '-' || s2 == ')' || s2 == '=')	return '>';
		else return '<';
	}
	else if (s1 == '*' || s1 == '/')
	{
		if (s2 == '(')	return '<';
		else return '>';
	}
	else if(s1=='(')
	{
		if (s2 == ')')	return '=';
		else return '<';
	}
	else if (s1 == ')')//how can?
	{
		return '>';
	}
	else if (s1 == '=') {
		if (s2 == '=') return '=';
		else return '<';
	}
	else {
		//error
		return 0;
	}
}
bool isnum(char s)//Judge whether it is a number
{
	if ((s <= '9' && s>='0') || s == '.') return true;
	else return 0;
}
double calculate(double n1, double n2, char op)//calculator
{
	switch (op)
	{
	case '*':return (n1 * n2); break;
	case '/':return (n1 / n2); break;
	case '+':return (n1 + n2); break;
	case '-':return (n1 - n2); break;
	}
}

int main()
{
	Stack<char> stackR(100); stackR.Push('=');//Register operator
	Stack<double> stackD(100); //Deposit operand
	char* str = new char[200];//Initialize input char
	cin.get(str,200);
	//cout << Precede(str[0], str[1]);
	int i = 0;

	while (str[i] != '='||stackR.GetTop()!='=')//=is the end
	{
		if (str[i] == ' ')i++;//if typying space is not error
		if (isnum(str[i]) == true) {//pointer is a number
			char* number = new char[20]; int len = 0; double n = 0;
			while (isnum(str[i]) == true) {
				number[len++] = str[i++];
			}
			n = atof(number);
			stackD.Push(n);
		}
		else {
			double n1, n2;
			switch (Precede(stackR.GetTop(), str[i]))
			{
			case '<':
				stackR.Push(str[i++]); ; break;
			case '>':
				n2 = stackD.Pop(); n1 = stackD.Pop();
				stackD.Push(calculate(n1, n2, stackR.Pop()));
				break;
			case '=':
				stackR.Pop(); i++; break;
			}
		}
	}
	cout << stackD.GetTop();
	
}
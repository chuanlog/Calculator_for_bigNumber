#include<iostream>
#include"bigNumber.h"
#include"CalculateFuntions.h"
using namespace std;

int main()
{
	string a, b;
	while (1)
	{ 
		cout << "Input the first number:" << endl;
		cin >> a;
		//cout << a << endl;//������
		cout << "Input the operator:" << endl;
		char s;
		bool op = false;
		cin >> s;
		if (s == '-')
		{
			op = true;
		}
		cout << "Input the second number:" << endl;
		cin >> b;
		//cout << b << endl;//������
		bigNumber num1, num2, result;
		num1.read_in(a);
		num2.read_in(b);
		//num1.test();
		//num2.test();//������
		Calculate(op, num1, num2, result);
		string res=result.show_list_result();
		cout << "The result is:" ;
		cout << res << endl;
	}
}
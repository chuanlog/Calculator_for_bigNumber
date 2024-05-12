#include<iostream>
using namespace std;

//定义双向链表的节点结构体
struct node
{
	int data;
	node* prev;
	node* next;
	node()
	{
		data = 0;
		prev = NULL;
		next = NULL;
	}//结构体的数据的初始化。
};
//在表头插入节点，利用头插法逐位创建链表，实现数字从低位到高位存储，便于运算
void insert(node*& head, char num)
{
	if (head == NULL)
	{
		node* p = new node;
		head = p;
		head->data = (int)num - 48;
		return;
	}//若链表为空，则创建头节点并将头指针指向头节点
	else
	{
		node* p = new node;
		head->prev = p;
		p->data = (int)num - 48;
		p->next = head;
		head = p;
	}//若链表非空，则将传入的数字存到一个新节点里并将该节点插入表头
}
void insert2(node*& head, int num)
{
	if (head == NULL)
	{
		node* p = new node;
		head = p;
		head->data = num;
		return;
	}//若链表为空，则创建头节点并将头指针指向头节点
	else
	{
		node* p = new node;
		head->prev = p;
		p->data = num;
		p->next = head;
		head = p;
	}//若链表非空，则将传入的数字存到一个新节点里并将该节点插入表头
}

//通过为短的数补零使它们一样长
void make_them_the_same_length(node*& end1, node*& end2, int len1, int len2)
{
	if (len1 > len2)
	{
		int dif = len1 - len2;
		int i;
		for (i = 0; i < dif; i++)
		{
			node* p = new node;
			p->data = 0;
			end2->next = p;
			p->prev = end2;
			end2 = p;
		}
	}
	else if (len1 < len2)
	{
		int dif = len2 - len1;
		int i;
		for (i = 0; i < dif; i++)
		{
			node* p = new node;
			p->data = 0;
			end1->next = p;
			p->prev = end1;
			end1 = p;
		}
	}
}

//比较长度相等的数的大小,返回bool值为假，则num1大，反之则num2大。
bool find_the_bigger_number(node*& end1, node*& end2)
{
	node* p = end1;
	node* q = end2;
	bool bigger = false;
	do
	{
		if (p->data < q->data)bigger = !bigger; break;//This "break" is very important which takes me two days to find it and write it.>_<
		p = p->prev;
		q = q->prev;
	} while (p);
	return bigger;
}

//逐位处理实现加法
int addition(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, int len1, int len2)
{
	if (len1 != len2)make_them_the_same_length(end1, end2, len1, len2);
	int count = 0;//计数器
	int carry = 0;//进位
	int num = 0;//结果位
	node* number1 = head1;
	node* number2 = head2;
	do
	{
		num = number1->data + number2->data + carry;
		if (num > 10)
		{
			carry = (num - num % 10) / 10;
			num = num % 10;
		}
		else if (num == 10)
		{
			num = 0;
			carry = 1;
		}
		else
		{
			carry = 0;
		}//判断进位
		insert2(res_head, num); count++;
		if (res_head->next == nullptr)res_end = res_head;
		number1 = number1->next;
		number2 = number2->next;
	} while (number1);
	if (carry)insert2(res_head, carry), count++;
	return count;
}

//逐位处理实现减法,num1-num2
int subtraction(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, int len1, int len2, bool& res_sign)
{
	int count = 0;//计数器
	int borrow = 0;//借位
	int num = 0;//结果
	res_sign = false;
	bool bigger = false;
	if (len1 == len2)
	{
		bigger = find_the_bigger_number(end1, end2);
	}
	else if (len1 < len2)
	{
		bigger = !bigger;
	}//判断大小
	if (len1 != len2)make_them_the_same_length(end1, end2, len1, len2);//补齐长度
	if (!bigger)//num1>num2
	{
		node* num1 = head1;
		node* num2 = head2;
		do
		{
			num = num1->data - num2->data - borrow;
			if (num < 0)
			{
				borrow = 1;
				num += 10;
			}
			else
			{
				borrow = 0;
			}//判断借位
			insert2(res_head, num); count++;
			num1 = num1->next;
			num2 = num2->next;
		} while (num1);
	}
	else//num1<num2
	{
		res_sign = !res_sign;
		node* num1 = head1;
		node* num2 = head2;
		do
		{
			num = num2->data - num1->data - borrow;
			if (num < 0)
			{
				borrow = 1;
				num += 10;
			}
			else
			{
				borrow = 0;
			}//判断借位
			insert2(res_head, num); count++;
			num1 = num1->next;
			num2 = num2->next;
		} while (num2);
	}
	node* p = res_head;
	while (p->data == 0 && count != 1)
	{
		p->next->prev = nullptr;
		res_head = p->next;
		delete p; count--;
		p = res_head;
	}//删除结果前面的零
	return count;
}

//逆向输出链表（测试用）
void show_list(node*& end, int len)
{
	node* p = end;
	node* q = end->prev;
	int count = 0;
	int n = len % 3;
	int i = 0;
	while (i < n)
	{
		cout << p->data;
		p = q;
		q = q->prev;
		i++;
	}
	if (n)cout << ',';
	while (p)
	{
		cout << p->data;
		count++;
		if ((count) % 3 == 0)cout << ',';
		p = q; if (p == nullptr)break;
		q = q->prev;
	}
	cout << '\b' << ' ' << '\b';
	cout << endl;
}
//输出链表
void show_list_result(node*& head, int len)
{
	if (len == 0)
	{
		cout << 0;
	}
	else if (len == 1)
	{
		cout << head->data;
	}
	else if (len == 2)
	{
		cout << head->data << head->next->data;
	}
	else if (len == 3)
	{
		cout << head->data << head->next->data << head->next->next->data;
	}
	else
	{
		node* p = head;
		node* q = head->next;
		int count = 0;
		int n = len % 3;
		int i = 0;
		while (i < n)
		{
			cout << p->data;
			p = q;
			q = q->next;
			i++;
		}
		if (n)cout << ',';
		while (p)
		{
			cout << p->data;
			count++;
			if ((count) % 3 == 0 && count != (len - n))cout << ',';
			p = q; if (p == nullptr)break;
			q = q->next;
		}
	}
	/*cout << '\b' << ' ' << '\b';
	cout << endl;*/
}

//删除链表释放空间
void delete_list(node* head)
{
	node* p = head;
	for (; head != NULL; head = p)
	{
		p = head->next;
		delete head;
	}
	delete head;
	head = NULL;
}

int main()
{
	int sampleNumber;
	cin >> sampleNumber;
	for (; sampleNumber; sampleNumber--)
	{
		char operation = 0;
		bool operating = false;
		cin >> operation;
		if (operation == '-')
		{
			operating = true;
		}//判断运算符，operating为假则为加，反之为减。
		char ignore = getchar();//忽视回车。
		/***************************下面读入第一个大数并以双链表的形式存储***************************/
		node* number1_head = NULL, * number1_end = NULL;
		int number1_length = 0;
		char temp_num = 0;//考虑到输入中有逗号和负号，先用字符形式存储数位
		bool number1_sign = false;//记录符号，和上面一样false为正true为负
		temp_num = getchar();
		do
		{

			if (temp_num == '-')
			{
				number1_sign = true;
				temp_num = getchar();
				continue;
			}//判断正负数符号
			else if (temp_num == ',' || temp_num == '\12')
			{
				temp_num = getchar();
				continue;
			}//跳过逗号和LF
			else
			{
				insert(number1_head, temp_num);
				temp_num = getchar();
				number1_length++;//记录数字长度
				if (number1_head->next == nullptr)number1_end = number1_head;//尾指针指向第一个创建的节点
			}//如果读入数位，就建立新的节点并插入表头,insert函数中包含建立头节点，故不用再进行判断。
		} while (temp_num != '\n');
		/*第一个大数的存储完成，与其有关的变量有number1_length,number1_head,number1_end以及number1_sign(bool值false为+)*/
		node* number2_head = NULL, * number2_end = NULL;
		int number2_length = 0;
		temp_num = 0;//考虑到输入中有逗号和负号，先用字符形式存储数位
		bool number2_sign = false;//记录符号，和上面一样false为正true为负
		temp_num = getchar();
		do
		{

			if (temp_num == '-')
			{
				number2_sign = true;
				temp_num = getchar();
			}//判断正负数符号
			else if (temp_num == ',' || temp_num == '\12')
			{
				temp_num = getchar();
			}//跳过逗号
			else
			{
				insert(number2_head, temp_num);
				temp_num = getchar();
				number2_length++;//记录数字长度
				if (number2_head->next == nullptr)number2_end = number2_head;//尾指针指向第一个创建的节点
			}//如果读入数位，就建立新的节点并插入表头,insert函数中包含建立头节点，故不用再进行判断。
		} while (temp_num != '\n');
		/*第二个大整数存储完成*/
		node* result_head = nullptr;
		node* result_end = nullptr;
		bool result_sign = false;
		if (!operating)//计算加法
		{
			if ((!number1_sign) && (!number2_sign))
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				show_list_result(result_head, count);
			}//两正数加法
			else if (number1_sign && number2_sign)
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				cout << '-';
				show_list_result(result_head, count);
			}//两负数加法
			else if ((!number1_sign) && (number2_sign))//正数加负数
			{
				int count = subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}
			else//负数加正数
			{
				int count = subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, number2_length, number1_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}
		}
		else//计算减法
		{
			if ((!number1_sign) && (!number2_sign))
			{
				int count = subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}//两正数减法
			else if (number1_sign && number2_sign)
			{
				int count = subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, number2_length, number1_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}//两负数减法
			else if ((!number1_sign) && (number2_sign))
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				show_list_result(result_head, count);
			}//正数减负数
			else
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				cout << '-';
				show_list_result(result_head, count);
			}//负数减正数
		}
		if (sampleNumber != 1)cout << endl;
		delete_list(number1_head);
		delete_list(number2_head);
		delete_list(result_head);//删除链表，释放内存
	}
	return 0;
}
#include<iostream>
using namespace std;

//����˫������Ľڵ�ṹ��
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
	}//�ṹ������ݵĳ�ʼ����
};
//�ڱ�ͷ����ڵ㣬����ͷ�巨��λ��������ʵ�����ִӵ�λ����λ�洢����������
void insert(node*& head, char num)
{
	if (head == NULL)
	{
		node* p = new node;
		head = p;
		head->data = (int)num - 48;
		return;
	}//������Ϊ�գ��򴴽�ͷ�ڵ㲢��ͷָ��ָ��ͷ�ڵ�
	else
	{
		node* p = new node;
		head->prev = p;
		p->data = (int)num - 48;
		p->next = head;
		head = p;
	}//������ǿգ��򽫴�������ִ浽һ���½ڵ��ﲢ���ýڵ�����ͷ
}
void insert2(node*& head, int num)
{
	if (head == NULL)
	{
		node* p = new node;
		head = p;
		head->data = num;
		return;
	}//������Ϊ�գ��򴴽�ͷ�ڵ㲢��ͷָ��ָ��ͷ�ڵ�
	else
	{
		node* p = new node;
		head->prev = p;
		p->data = num;
		p->next = head;
		head = p;
	}//������ǿգ��򽫴�������ִ浽һ���½ڵ��ﲢ���ýڵ�����ͷ
}

//ͨ��Ϊ�̵�������ʹ����һ����
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

//�Ƚϳ�����ȵ����Ĵ�С,����boolֵΪ�٣���num1�󣬷�֮��num2��
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

//��λ����ʵ�ּӷ�
int addition(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, int len1, int len2)
{
	if (len1 != len2)make_them_the_same_length(end1, end2, len1, len2);
	int count = 0;//������
	int carry = 0;//��λ
	int num = 0;//���λ
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
		}//�жϽ�λ
		insert2(res_head, num); count++;
		if (res_head->next == nullptr)res_end = res_head;
		number1 = number1->next;
		number2 = number2->next;
	} while (number1);
	if (carry)insert2(res_head, carry), count++;
	return count;
}

//��λ����ʵ�ּ���,num1-num2
int subtraction(node*& head1, node*& head2, node*& end1, node*& end2, node*& res_head, node*& res_end, int len1, int len2, bool& res_sign)
{
	int count = 0;//������
	int borrow = 0;//��λ
	int num = 0;//���
	res_sign = false;
	bool bigger = false;
	if (len1 == len2)
	{
		bigger = find_the_bigger_number(end1, end2);
	}
	else if (len1 < len2)
	{
		bigger = !bigger;
	}//�жϴ�С
	if (len1 != len2)make_them_the_same_length(end1, end2, len1, len2);//���볤��
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
			}//�жϽ�λ
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
			}//�жϽ�λ
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
	}//ɾ�����ǰ�����
	return count;
}

//����������������ã�
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
//�������
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

//ɾ�������ͷſռ�
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
		}//�ж��������operatingΪ����Ϊ�ӣ���֮Ϊ����
		char ignore = getchar();//���ӻس���
		/***************************��������һ����������˫�������ʽ�洢***************************/
		node* number1_head = NULL, * number1_end = NULL;
		int number1_length = 0;
		char temp_num = 0;//���ǵ��������ж��ź͸��ţ������ַ���ʽ�洢��λ
		bool number1_sign = false;//��¼���ţ�������һ��falseΪ��trueΪ��
		temp_num = getchar();
		do
		{

			if (temp_num == '-')
			{
				number1_sign = true;
				temp_num = getchar();
				continue;
			}//�ж�����������
			else if (temp_num == ',' || temp_num == '\12')
			{
				temp_num = getchar();
				continue;
			}//�������ź�LF
			else
			{
				insert(number1_head, temp_num);
				temp_num = getchar();
				number1_length++;//��¼���ֳ���
				if (number1_head->next == nullptr)number1_end = number1_head;//βָ��ָ���һ�������Ľڵ�
			}//���������λ���ͽ����µĽڵ㲢�����ͷ,insert�����а�������ͷ�ڵ㣬�ʲ����ٽ����жϡ�
		} while (temp_num != '\n');
		/*��һ�������Ĵ洢��ɣ������йصı�����number1_length,number1_head,number1_end�Լ�number1_sign(boolֵfalseΪ+)*/
		node* number2_head = NULL, * number2_end = NULL;
		int number2_length = 0;
		temp_num = 0;//���ǵ��������ж��ź͸��ţ������ַ���ʽ�洢��λ
		bool number2_sign = false;//��¼���ţ�������һ��falseΪ��trueΪ��
		temp_num = getchar();
		do
		{

			if (temp_num == '-')
			{
				number2_sign = true;
				temp_num = getchar();
			}//�ж�����������
			else if (temp_num == ',' || temp_num == '\12')
			{
				temp_num = getchar();
			}//��������
			else
			{
				insert(number2_head, temp_num);
				temp_num = getchar();
				number2_length++;//��¼���ֳ���
				if (number2_head->next == nullptr)number2_end = number2_head;//βָ��ָ���һ�������Ľڵ�
			}//���������λ���ͽ����µĽڵ㲢�����ͷ,insert�����а�������ͷ�ڵ㣬�ʲ����ٽ����жϡ�
		} while (temp_num != '\n');
		/*�ڶ����������洢���*/
		node* result_head = nullptr;
		node* result_end = nullptr;
		bool result_sign = false;
		if (!operating)//����ӷ�
		{
			if ((!number1_sign) && (!number2_sign))
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				show_list_result(result_head, count);
			}//�������ӷ�
			else if (number1_sign && number2_sign)
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				cout << '-';
				show_list_result(result_head, count);
			}//�������ӷ�
			else if ((!number1_sign) && (number2_sign))//�����Ӹ���
			{
				int count = subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}
			else//����������
			{
				int count = subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, number2_length, number1_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}
		}
		else//�������
		{
			if ((!number1_sign) && (!number2_sign))
			{
				int count = subtraction(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}//����������
			else if (number1_sign && number2_sign)
			{
				int count = subtraction(number2_head, number1_head, number2_end, number1_end, result_head, result_end, number2_length, number1_length, result_sign);
				if (result_sign)cout << '-';
				show_list_result(result_head, count);
			}//����������
			else if ((!number1_sign) && (number2_sign))
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				show_list_result(result_head, count);
			}//����������
			else
			{
				int count = addition(number1_head, number2_head, number1_end, number2_end, result_head, result_end, number1_length, number2_length);
				cout << '-';
				show_list_result(result_head, count);
			}//����������
		}
		if (sampleNumber != 1)cout << endl;
		delete_list(number1_head);
		delete_list(number2_head);
		delete_list(result_head);//ɾ�������ͷ��ڴ�
	}
	return 0;
}
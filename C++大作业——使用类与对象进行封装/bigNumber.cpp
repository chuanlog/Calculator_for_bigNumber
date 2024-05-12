#include "bigNumber.h"
#include <iostream>
using namespace std;

void bigNumber::insert(char num)
{
    if (head == nullptr)
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

void bigNumber::insert2(int num)
{
    if (head == nullptr)
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

void bigNumber::read_in(string number)
{
    const char* num1 = &number[0];
    int len1 = strlen(num1);
    int i = 0;
    char temp_num;
    for (i = 0; i < len1; i++)
    {
        temp_num = number[i];
        if (temp_num == '-')
        {
            sign = true;
        }
        else if (temp_num == ',' || temp_num == '\12')
        {
            //ʲô��������
        }
        else if (temp_num == '.')
        {
            insert(temp_num);
            point = head;
        }
        else
        {
            insert(temp_num);
            if (point == nullptr)
            {
                int_len++;
            }
            else
            {
                fra_len++;
            }
            if (head->next == nullptr)
            {
                end = head;
            }//����β�ڵ㡣
        }
    }
    if (fra_len == 0)
    {
        insert('.');
        point = head;
    }
}

void bigNumber::show_list_int(int len, string& res)
{   
    node* p = head;
    int n = len % 3;
    int count = 0;
    while (count < n)
    {
        res += char(p->data + 48);
        count++;
        p = p->next;
    }
    if (len > 3 && n != 0)res += ',';
    count = 0;
    while (p != point)
    {
        res += char(p->data + 48); count++;
        if (count % 3 == 0 && count != len - n)res += ',';
        p = p->next;
    }
}

void bigNumber::show_list_fra(string& res)
{
    res += '.';
    node* p = point->next;
    while (p)
    {
        res += char(p->data+48);
        p = p->next;
    }
}

string bigNumber::show_list_result()
{
    string res;//��ʼ��������ַ���
    if (sign)res += '-';
    /*��ɾȥ����ǰ�����*/
    node* p = head;
    node* q = end;
    while (p->data == 0)
    {
        head = p->next;
        head->prev = nullptr;
        delete p;
        p = head;
    }
    while (q->data == 0)
    {
        end = q->prev;
        end->next = nullptr;
        delete q;
        q = end;
    }
    /*���Ϊ������*/
    if (head == end && head == point)res += '0';
    /*ͳ������λ��*/
    int len = 0;
    p = head;
    while (p != point)
    {
        len++;
        p = p->next;
    }
    show_list_int(len, res);
    if (point->next != nullptr)
    {
        if (len == 0)res += '0';
        show_list_fra(res);
    }
    return res;
}

void bigNumber::test()
{
    node* p = head;
    while (p)
    {
        cout << p->data<<' ';
        p = p->next;
    }
    cout << endl;
}
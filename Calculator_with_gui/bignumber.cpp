#include "bigNumber.h"
#include <cstring>
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

void bigNumber::insert2(int num)
{
    if (head == nullptr)
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
            //什么都不用做
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
            }//创建尾节点。
        }
    }
    if (fra_len == 0)
    {
        insert('.');
        point = head;
    }
}

void bigNumber::show_list_int(int len,string&res)
{
    node* p = head;
    int n = len % 3;
    int count = 0;
    while (count < n)
    {
        res.push_back(char(p->data+48));
        count++;
        p = p->next;
    }
    if (len > 3 && n != 0)res+= ',';
    count = 0;
    while (p != point)
    {
        res.push_back(char(p->data+48)); count++;
        if (count % 3 == 0 && count != len - n)res+= ',';
        p = p->next;
    }
}

void bigNumber::show_list_fra(string&res)
{
    res+= '.';
    node* p = point->next;
    while (p)
    {
        res.push_back(char(p->data+48));
        p = p->next;
    }
}

string bigNumber::show_list_result()
{
    string res;//初始化结果空字符串
    if (sign)res+= '-';
    /*先删去链表前后的零*/
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
    /*结果为零的情况*/
    if (head == end && head == point)res+= '0';
    /*统计整数位数*/
    int len = 0;
    p = head;
    while (p != point)
    {
        len++;
        p = p->next;
    }
    show_list_int(len,res);
    if (point->next != nullptr)
    {
        if(len==0)
        {
            res.push_back(char(0+48));
        }
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

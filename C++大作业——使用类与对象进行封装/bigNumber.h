#pragma once
#include"node.h"
#include <string>
#include<iostream>
using namespace std;

class bigNumber
{
public:
    node* head;//头指针，指向最高位
    node* end;//尾指针，指向最低位
    node* point;//小数点指针，指向小数点位
    int int_len;//整数部分长度
    int fra_len;//小数部分长度
    bool sign;//符号
    bigNumber()//构造函数
    {
        head = nullptr;
        end = nullptr;
        point = nullptr;
        int_len = 0;
        fra_len = 0;
        sign = false;
    }//构造函数
    ~bigNumber()//析构函数
    {
        node* p = head;
        node* q = head;
        head = nullptr;
        while (q->next)
        {
            q = p->next;
            q->prev = nullptr;
            delete p;
            p = q;
        }
        delete q;
        p = nullptr;
        q = nullptr;
        head = nullptr;
        end = nullptr;
        point = nullptr;
        int_len = 0;
        fra_len = 0;
        sign = false;
    }//析构函数

    void insert(char num);//传入字符 ，并在表头插入节点

    void insert2(int num);//传入整形，并在表头插入节点

    void read_in(string number);//以字符串初始化数字

    void show_list_int(int len,string&res);//输出整数部分

    void show_list_fra(string& res);//输出小数部分

    string show_list_result();//输出结果链表

    void test();//调试用，用于直观看到链表状态
};


#pragma once
#include"node.h"
#include <string>
#include<iostream>
using namespace std;

class bigNumber
{
public:
    node* head;//ͷָ�룬ָ�����λ
    node* end;//βָ�룬ָ�����λ
    node* point;//С����ָ�룬ָ��С����λ
    int int_len;//�������ֳ���
    int fra_len;//С�����ֳ���
    bool sign;//����
    bigNumber()//���캯��
    {
        head = nullptr;
        end = nullptr;
        point = nullptr;
        int_len = 0;
        fra_len = 0;
        sign = false;
    }//���캯��
    ~bigNumber()//��������
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
    }//��������

    void insert(char num);//�����ַ� �����ڱ�ͷ����ڵ�

    void insert2(int num);//�������Σ����ڱ�ͷ����ڵ�

    void read_in(string number);//���ַ�����ʼ������

    void show_list_int(int len,string&res);//�����������

    void show_list_fra(string& res);//���С������

    string show_list_result();//����������

    void test();//�����ã�����ֱ�ۿ�������״̬
};


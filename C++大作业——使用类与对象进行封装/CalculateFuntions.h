#pragma once
#include"bigNumber.h"
using namespace std;

//ͨ��ǰ����ʹ������һ�£����ڼ���
void make_them_the_same_length(bigNumber& num1,bigNumber& num2)
{
    if (num1.int_len >num2.int_len)
    {
        int dif = num1.int_len - num2.int_len;
        int i;
        for (i = 0; i < dif; i++)
        {
            node* p = new node;
            p->prev = num2.end;
            num2.end->next = p;
            num2.end = p;
        }
    }
    else
    {
        int dif = num2.int_len - num1.int_len;
        int i;
        for (i = 0; i < dif; i++)
        {
            node* p = new node;
            p->prev = num1.end;
            num1.end->next = p;
            num1.end = p;
        }
    }
    if (num1.fra_len > num2.fra_len)
    {
        int dat = num1.fra_len - num2.fra_len;
        int i;
        for (i = 0; i < dat; i++)
        {
            node* p = new node;
            p->next = num2.head;
            num2.head->prev = p;
            num2.head = p;
        }
    }
    else
    {
        int dat = num2.fra_len - num1.fra_len;
        int i;
        for (i = 0; i < dat; i++)
        {
            node* p = new node;
            p->next = num1.head;
            num1.head->prev = p;
            num1.head = p;
        }
    }
}

//�Ƚϴ�С������false��num1>num2,����num1<=num2
bool find_the_bigger_number(bigNumber& num1, bigNumber& num2)
{
    node* p = num1.end;
    node* q = num2.end;
    bool bigger = false;
    do
    {
        if (p->data > q->data)
        {
            bigger = false; break;
        }
        else if (p->data < q->data)
        {
            bigger = true; break;
        }
        else if (p->data == q->data)
        {
            p = p->prev;
            q = q->prev;
        }
    } while (p);
    return bigger;
}

//��λ���мӷ�
void addition(bigNumber& num1,bigNumber& num2,bigNumber& result)
{
    int count = 0;
    int carry = 0;//��λ
    int num = 0;
    node* p = num1.head;
    node* q = num2.head;
    do
    {
        if (p->data == -2 && q->data == -2)
        {
            result.insert('.');
            result.point = result.head; count++;
            if (count == 1)result.end = result.head;
            p = p->next;
            q = q->next;
        }
        else
        {
            num = p->data + q->data + carry;
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
            }
            result.insert2(num); count++;
            if (count == 1)result.end = result.head;
            p = p->next;
            q = q->next;
        }
    } while (p);
    if (carry)result.insert2(carry);
}

//��λ���м���
void subtraction(bigNumber& num1, bigNumber& num2, bigNumber& result)
{
    bool bigger = find_the_bigger_number(num1, num2);
    int borrow = 0;//��λ
    int num = 0;//���λ
    int count = 0;//������
    node* p = num1.head; node* q = num2.head;
    if (!bigger)//num1>num2
    {
        do
        {
            if (p->data == -2)
            {
                p = p->next;
                q = q->next;
                result.insert( '.'); count++;
                result.point = result.head;
                if (count == 1)result.end = result.head;
            }
            else
            {
                num = p->data - q->data - borrow;
                if (num < 0)
                {
                    borrow = 1;
                    num += 10;
                }
                else
                {
                    borrow = 0;
                }//�жϽ�λ
                result.insert2(num); count++;
                if (count == 1)result.end = result.head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
    else//num2>num1
    {
        result.sign = true;
        do
        {
            if (p->data == -2)
            {
                p = p->next;
                q = q->next;
                result.insert( '.'); count++;
                result.point = result.head;
                if (count == 1)result.end = result.head;

            }
            else
            {
                num = q->data - p->data - borrow;
                if (num < 0)
                {
                    borrow = 1;
                    num += 10;
                }
                else
                {
                    borrow = 0;
                }//�жϽ�λ
                result.insert2(num); count++;
                if (count == 1)result.end = result.head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
}

//���㣬�������������������ʽ����result��
void Calculate(bool op, bigNumber& number1, bigNumber& number2, bigNumber& result)
{
    make_them_the_same_length(number1, number2);
    if (!op)//����ӷ�
    {
        if ((!number1.sign) && (!number2.sign))
        {
            addition(number1, number2, result);
        }//�������ӷ�
        else if (number1.sign && number2.sign)
        {
            result.sign = true;
            addition(number1, number2, result);
        }//�������ӷ�
        else if ((!number1.sign) && (number2.sign))//�����Ӹ���
        {
            subtraction(number1, number2, result);
        }
        else//����������
        {
            subtraction(number2, number1, result);
        }
    }
    else//�������
    {
        if ((!number1.sign) && (!number2.sign))
        {
            subtraction(number1, number2, result);
        }//����������
        else if (number1.sign && number2.sign)
        {
            subtraction(number2, number1, result);
        }//����������
        else if ((!number1.sign) && (number2.sign))
        {
            addition(number1, number2, result);
        }//����������
        else
        {
            result.sign = true;
            addition(number1, number2, result);
        }//����������
    }
}
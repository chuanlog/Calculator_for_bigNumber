#pragma once
#include"bigNumber.h"
using namespace std;

//通过前后补零使链表长度一致，便于计算
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

//比较大小，返回false则num1>num2,否则num1<=num2
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

//逐位进行加法
void addition(bigNumber& num1,bigNumber& num2,bigNumber& result)
{
    int count = 0;
    int carry = 0;//进位
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

//逐位进行减法
void subtraction(bigNumber& num1, bigNumber& num2, bigNumber& result)
{
    bool bigger = find_the_bigger_number(num1, num2);
    int borrow = 0;//借位
    int num = 0;//结果位
    int count = 0;//计数器
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
                }//判断进位
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
                }//判断借位
                result.insert2(num); count++;
                if (count == 1)result.end = result.head;
                p = p->next;
                q = q->next;
            }
        } while (p);
    }
}

//计算，并将结果以逆序链表形式存入result中
void Calculate(bool op, bigNumber& number1, bigNumber& number2, bigNumber& result)
{
    make_them_the_same_length(number1, number2);
    if (!op)//计算加法
    {
        if ((!number1.sign) && (!number2.sign))
        {
            addition(number1, number2, result);
        }//两正数加法
        else if (number1.sign && number2.sign)
        {
            result.sign = true;
            addition(number1, number2, result);
        }//两负数加法
        else if ((!number1.sign) && (number2.sign))//正数加负数
        {
            subtraction(number1, number2, result);
        }
        else//负数加正数
        {
            subtraction(number2, number1, result);
        }
    }
    else//计算减法
    {
        if ((!number1.sign) && (!number2.sign))
        {
            subtraction(number1, number2, result);
        }//两正数减法
        else if (number1.sign && number2.sign)
        {
            subtraction(number2, number1, result);
        }//两负数减法
        else if ((!number1.sign) && (number2.sign))
        {
            addition(number1, number2, result);
        }//正数减负数
        else
        {
            result.sign = true;
            addition(number1, number2, result);
        }//负数减正数
    }
}
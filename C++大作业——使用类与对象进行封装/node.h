#pragma once
struct node
{
    int data;
    node* prev;
    node* next;
    node()
    {
        data = 0;
        prev = nullptr;
        next = nullptr;
    }
};
//��������ڵ㼰�乹�캯��
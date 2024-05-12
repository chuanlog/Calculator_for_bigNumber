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
//定义链表节点及其构造函数

#include <stdlib.h>
#include <iostream>
using namespace std;
#define ERROR false;
#define OK true;
typedef bool Status;
typedef int ElemType;

struct LNode //链表节点结构体
{
    ElemType data;
    LNode *next;
};

LNode *CreateList_Head(int n) //创建链表头插法
{
    ElemType data;
    LNode *head, *p;
    head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;
    for (int i = 0; i < n; ++i)
    {
        cin >> data;
        p = (LNode *)malloc(sizeof(LNode));
        p->data = data;
        p->next = head->next;
        head->next = p;
    }
    return head;
}

LNode *CreateList_Rear(int n) //创建链表尾插法
{
    ElemType data;
    LNode *head, *rear, *p;
    head = rear = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;
    for (int i = 0; i < n; ++i)
    {
        cin >> data;
        p = (LNode *)malloc(sizeof(LNode));
        p->data = data;
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    return head;
}

Status ListInsert(LNode *head, int pos, ElemType e) //在第pos位置前插入元素e
{
    LNode *p = head;
    int i = 0;
    while (!p && i < pos - 1)
    {
        p = p->next;
        ++i;
    }
    if (!p || i > pos - 1)
        return ERROR;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete(LNode *head, int pos) //删除指定位置的元素
{
    LNode *p = head;
    int i = 0;
    while (!p && i < pos - 1)
    {
        p = p->next;
        ++i;
    }
    if (!(p->next) || i > pos - 1)
        return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    free(q);
    return OK;
}

ElemType Get_Elem_pos(LNode *head, int pos) //按序查找
{
    int i = 0;
    LNode *p = head;
    while (!p && i < pos)
    {
        p = p->next;
        ++i;
    }
    if (!p || i > pos)
        return ERROR;
    return p->data;
}

LNode *Get_Elem_value(LNode *head, int e) //按值查找
{
    LNode *p = head;
    while (!p && p->data != e)
        p = p->next;
    return p;
}
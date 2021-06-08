#include <stdlib.h>
#include <iostream>
using namespace std;
typedef int ElemType;
typedef bool Status;
#define ERROR false;
#define OK true;

struct DuLNode
{
    ElemType data;  //元素值
    DuLNode *prior; //指向前一个节点的指针
    DuLNode *next;  //指向后一个节点的指针
};

DuLNode *CreateList_Head(int n) //双向链表前插法
{
    ElemType data;
    DuLNode *head, *p;
    head = (DuLNode *)malloc(sizeof(DuLNode));
    head->next = head->prior = head;
    for (int i = 0; i < n; ++i)
    {
        cin >> data;
        p = (DuLNode *)malloc(sizeof(DuLNode));
        p->data = data;
        p->prior = head;
        p->next = head->next;
        head->next->prior = p;
        head->next = p;
    }
    return head;
}

DuLNode *CreateList_Rear(int n) //双向链表尾插法
{
    ElemType data;
    DuLNode *head, *p, *rear;
    head = rear = (DuLNode *)malloc(sizeof(DuLNode));
    head->next = head->prior = head;
    rear->next = head;
    for (int i = 0; i < n; ++i)
    {
        cin >> data;
        p = (DuLNode *)malloc(sizeof(DuLNode));
        p->data = data;
        p->prior = rear;
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    return head;
}

Status DuLinkList_Insert(DuLNode *head, int pos, ElemType e) //在pos位置插入元素e
{
    DuLNode *p = head, *s;
    int i = 0;
    while (p->next != head && i < pos - 1) //此处判断是否为末尾有所不同
    {
        p = p->next;
        ++i;
    }
    if ((p->next == head && i != pos - 1) || i > pos - 1)
        return ERROR;
    s = (DuLNode *)malloc(sizeof(DuLNode));
    s->data = e;
    s->next = p->next;
    s->prior = p;
    p->next->prior = s;
    p->next = s;
    return OK;
}

Status DuLinkList_Delete(DuLNode *head, int pos) //删除pos位置的元素
{
    DuLNode *p = head;
    int i = 0;
    while (p->next != head && i < pos) //此处判断是否为末尾有所不同
    {
        p = p->next;
        ++i;
    }
    if ((p->next == head && i != pos) || i > pos)
        return ERROR;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}
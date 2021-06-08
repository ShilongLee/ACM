#include <stdlib.h>
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10   //线性表存储空间的分配增量
#define OVERFLOW false
#define ERROR false
#define OK true
typedef bool Status;

template <typename ElemType> //自定义元素类型
struct SqList
{
    ElemType *elem; //存储空间基地址，也就是数组头指针
    int length;     //当前长度
    int listsize;   //分配给线性表的总存储空间，以sizeof(ElemType)为单位

    SqList() //构造空的线性表L
    {
        elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        length = 0;
        listsize = LIST_INIT_SIZE;
    }

    Status insert(int pos, ElemType e) //在pos位置前插入元素e  这里pos从1开始 实际元素从0开始
    {
        if (pos < 1 || pos > length + 1) //位置不合法
            return ERROR;
        if (length >= listsize) //空间不足重新分配，realloc重新分配的地址仍然连续，所以依然是连续地址的线性表
        {
            ElemType *newbase = (ElemType *)realloc(elem, (listsize + LISTINCREMENT) * sizeof(ElemType)); //新的基地址
            if (!newbase)
                return OVERFLOW;
            elem = newbase;
            listsize += LISTINCREMENT;
        }
        ElemType *p = &elem[pos - 1];                      //要插入e的位置
        for (ElemType *i = &elem[length - 1]; i >= p; --i) //把这个位置及后面的元素都往后移一位，以腾出这个空间插入e
            *(i + 1) = *i;
        *p = e;   //插入e
        ++length; //表长加1
        return true;
    }

    int del(int pos) //删除pos位置的元素
    {
        if (pos < 1 || pos > length) //范围超限
            return ERROR;
        ElemType *p = elem[pos - 1];               //删除元素的位置
        for (ElemType *i = p; i < length - 1; ++i) //把要删除的位置后面的元素往前移一位
            *i = *(i + 1);
        --length;
        return OK;
    }

    int search(ElemType e, Status (*compare)(ElemType, ElemType)) //根据自定义比较函数返回e所在的位置  关于*compare函数指针详见https://blog.csdn.net/u010280075/article/details/88914424
    {
        int pos = 1;
        ElemType *p = elem;
        while (pos <= length && !(*compare)(*p++, e))
            ++i;
        if (i <= length)
            return i;
        else
            return false;
    }
};
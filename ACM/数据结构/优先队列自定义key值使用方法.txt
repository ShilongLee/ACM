#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
struct node
{
    int ans;
    int key;
    node(int a,int b)
    {
        ans=a;
        key=b;
    }
    bool operator<(const node& a) const//大顶堆//默认是大顶堆，从下到上是升序。
    {
        return key<a.key;
    }
};

int main()
{
    node a(1,2);
    node b(2,1);
    node c(3,3);
    priority_queue<node>qu;
    qu.push(a);
    qu.push(b);
    qu.push(c);
    while(!qu.empty())
    {
        cout<<qu.top().ans<<endl;
        qu.pop();
    }
}

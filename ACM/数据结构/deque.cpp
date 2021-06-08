#include<deque>
#include<iostream>
#include<vector>
using namespace std;
void test()
{
    vector<int>v(2);
    v[0]=10;
    int *p=&v[0];
    cout<<*p<<endl;
    v.push_back(20);
    cout<<*p<<endl;
    deque<int>d(2);
    d[0]=10;
    int *q=&d[0];
    cout<<*q<<endl;
    d.push_back(20);
    cout<<*q<<endl;
}
int main()
{
//    deque<int>deq;
//    for(int i=1; i<=10; ++i)
//        deq.push_front(i);
//    while(!deq.empty())
//    {
//        cout<<deq.front()<<' ';
//        deq.pop_front();
//    }
test();
}
//deque的用法
//

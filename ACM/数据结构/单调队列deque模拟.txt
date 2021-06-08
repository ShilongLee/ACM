#include<iostream>
#include<string.h>
#include<deque>
using namespace std;
struct node
{
    int pos,val;
} a[1000005];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1; i<=n; ++i)
    {
        cin>>a[i].val;
        a[i].pos=i;
    }
    deque<node>d;
    for(int i=1; i<=n; ++i)
    {
        while(!d.empty()&&d.back().val>=a[i].val)
            d.pop_back();
        d.push_back(a[i]);
        while(i-k>=d.front().pos)
            d.pop_front();
        if(i>=k)
            cout<<d.front().val<<' ';
    }
    d.clear();
    cout<<endl;
    for(int i=1; i<=n; ++i)
    {

        while(!d.empty()&&d.back().val<=a[i].val)
            d.pop_back();
        d.push_back(a[i]);
        while(i-k>=d.front().pos)
            d.pop_front();
        if(i>=k)
            cout<<d.front().val<<' ';
    }
}
//单调队列deque模拟
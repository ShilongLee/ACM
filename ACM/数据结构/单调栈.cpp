#include<iostream>
#include<stack>
using namespace std;
stack<int>s;
int main()
{
    int a[5]= {1,8,3,9,2};
    for(int i=0; i<5; ++i)
    {
        while(!s.empty()&&s.top()>a[i])
            s.pop();
            s.push(a[i]);
    }
    while(!s.empty())
    {
        cout<<s.top()<<' ';
        s.pop();
    }
}
//单调栈
//输出的时候从栈顶输出得，所以输出反着看

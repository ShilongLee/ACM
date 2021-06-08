#include<iostream>
#include<string.h>
using namespace std;
const int N=30005;
int n,m;
int rt[N];
int mem[30005];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int main()
{
    while(cin>>n>>m&&(n||m))
    {
        for(int i=0; i<n; ++i)
            rt[i]=i;
        for(int i=0; i<m; ++i)
        {
            int k;
            cin>>k;
            for(int j=0; j<k; ++j)
                cin>>mem[j];
            for(int j=1; j<k; ++j)
                rt[fin(mem[j])]=fin(mem[0]);
        }
        int sum=1;
        for(int i=1; i<n; ++i)
            if(fin(0)==fin(i))
                sum++;
        cout<<sum<<endl;
    }
}
//poj1611
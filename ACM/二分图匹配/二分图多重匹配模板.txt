#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<string>
using namespace std;
const int N=1050;
const int M=505;
bool mapp[N][M],vis[N];
int n,m,mid,num[N],link[N][M];
bool match(int x)
{
    for(int i=0; i<m; ++i)
    {
        if(!vis[i]&&mapp[x][i])
        {
            vis[i]=true;
            if(num[i]<mid)
            {
                link[i][num[i]++]=x;
                return true;
            }
            else
            {
                for(int j=0; j<num[i]; ++j)
                    if(match(link[i][j]))
                    {
                        link[i][j]=x;
                        return true;
                    }
            }
        }
    }
    return false;
}
bool hugry()
{
    memset(num,0,sizeof(num));
    for(int i=0; i<n; ++i)
    {
        memset(vis,0,sizeof(vis));
        if(!match(i))
            return false;
    }
    return true;
}
int main()
{
    while(cin>>n>>m&&(n||m))
    {
        memset(link,-1,sizeof(link));
        memset(mapp,0,sizeof(mapp));
        for(int i=0; i<n; ++i)
        {
            int y;
            char c;
            string s;
            cin>>s;
            while(1)
            {
                cin>>y;
                c=getchar();
                mapp[i][y]=1;
                if(c=='\n')
                    break;
            }
        }
        int l=0,r=n;
        while(l<=r)
        {
            mid=(l+r)/2;
            if(hugry())
                r=mid-1;
            else
                l=mid+1;
        }
        cout<<l<<endl;
    }
    return 0;
}
//poj2289
//二分图多重匹配
//思路：
//为右边每一个点设置一个num[i]，代表这个点最大可以匹配个数，再设置一个link[i][j]，代表右边的第i个点匹配的第j个点是link[i][j]。
//匹配成功（i没有匹配满）---->link[i][num[i]++]=x
//不成功（i已经匹配满）--->match(link[i][j])/** j从1到num[i]*/ 从头到尾找有没有元素可以改一下匹配，如果有点可以改，这个位置就被让出来了，就可以匹配了，从头到尾都没有能让位的点，匹配失败。

#include<iostream>
#include<string.h>
using namespace std;
const int N=505;
const int M=100005;
const int inf=0x3f3f3f3f;
int n,m,w;
int u[M],v[M],W[M];
int dis[N];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>w;
        for(int i=1; i<=m; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            u[i]=x;
            v[i]=y;
            W[i]=z;
            u[m+w+i]=y;
            v[m+w+i]=x;
            W[m+w+i]=z;
        }
        for(int i=m+1; i<=m+w; ++i)
        {
            int x,y,z;
            cin>>x>>y>>z;
            u[i]=x;
            v[i]=y;
            W[i]=z;
            W[i]=-W[i];
        }
        memset(dis,inf,sizeof(dis));
        for(int k=1; k<=n-1; ++k)
            for(int i=1; i<=2*(m)+w; ++i)
                dis[v[i]]=min(dis[v[i]],dis[u[i]]+W[i]);
        int flag=0;
        for(int k=1; k<=n-1; ++k)
        {
            if(flag)
                break;
            for(int i=1; i<=2*(m)+w; ++i)
            {
                if(dis[v[i]]>dis[u[i]]+W[i])
                {
                    flag=1;
                    break;
                }
            }
        }
        if(flag)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
}

//POJ 3259
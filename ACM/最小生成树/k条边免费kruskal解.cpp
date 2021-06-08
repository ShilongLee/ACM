#include<iostream>
#include<string.h>
#include<iomanip>
#include<algorithm>
#include<math.h>
using namespace std;
const int N=605;
struct node
{
    int x,y;
    double len;
} edge[N*N];
int s,p,num;
int rt[N];
double x[N*N],y[N*N];
bool cmp(node a,node b)
{
    return a.len<b.len;
}
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        num=0;
        cin>>s;
        cin>>p;
        for(int i=1; i<=p; ++i)
            rt[i]=i;
        for(int i=1; i<=p; ++i)
        {
            cin>>x[i]>>y[i];
            for(int j=1; j<=i; ++j)
                if(i!=j)
                {
                    edge[++num].x=i;
                    edge[num].y=j;
                    edge[num].len=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                }
        }
        sort(edge+1,edge+num+1,cmp);
        double ans=0;
        int cnt=p;
        for(int i=1; i<=num; ++i)
        {
            if(cnt<=s)
                break;
            int xx=fin(edge[i].x);
            int yy=fin(edge[i].y);
            if(xx!=yy)
            {
                rt[xx]=yy;
                ans=edge[i].len;
                cnt--;
            }
        }
        cout<<fixed<<setprecision(2)<<ans<<endl;
    }
    return 0;
}
//poj2349
//k条边免费

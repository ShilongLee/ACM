#include<iostream>
#include<string.h>
#include<algorithm>
#include<iomanip>
#include<math.h>
using namespace std;
const int N=105;
const int M=N*N;
int rt[105];
struct node
{
    int x,y;
    double len;
} edge[M];
int n;
int num;
double x[M],y[M],z[M],r[M];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    return rt[x]=fin(rt[x]);
}
bool cmp(node a,node b)
{
    return a.len<b.len;
}
int main()
{
    while(cin>>n&&n)
    {
        num=0;
        for(int i=1; i<=n; ++i)
                rt[i]=i;
        for(int i=1; i<=n; ++i)
        {
            cin>>x[i]>>y[i]>>z[i]>>r[i];
            for(int j=1; j<=i; ++j)
            {
                if(i!=j)
                {
                    edge[++num].x=i;
                    edge[num].y=j;
                    double len=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]))-r[i]-r[j];
                    if(len<0) len=0;
                    edge[num].len=len;
                }
            }
        }
        sort(edge+1,edge+num+1,cmp);
//        for(int i=1;i<=num;++i)
//            cout<<edge[i].len<<' ';
//        cout<<endl;
        double sum=0;
        for(int i=1; i<=num; ++i)
        {
            int xx=fin(edge[i].x);
            int yy=fin(edge[i].y);
            if(xx!=yy)
            {
                rt[xx]=yy;
                sum+=edge[i].len;
            }
        }
        cout<<fixed<<setprecision(3)<<sum<<endl;
    }
}
//poj2031
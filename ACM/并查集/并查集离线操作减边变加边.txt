#include<iostream>
#include<string.h>
#include<map>
using namespace std;
const int N=10005;
long long ene[N];
int n,m,q;
int rt[N];
struct node
{
    int a,b;
} edge[20005];
int a[50005];
int b[50005];
int ans[50005];
int fin(int x)
{
    if(rt[x]==x)
        return x;
    else
        return rt[x]=fin(rt[x]);
}
int main()
{
    int cas=0;
    while(cin>>n)
    {
        map<int,map<int,int> >mp;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(ans,0,sizeof(ans));
        for(int i=1; i<=n; ++i)
            cin>>ene[i];
        for(int i=1; i<=n; ++i)
            rt[i]=i;
        cin>>m;
        for(int i=1; i<=m; ++i)
        {
            int a,b;
            cin>>a>>b;
            a++;
            b++;
            edge[i].a=a;
            edge[i].b=b;
            mp[edge[i].a][edge[i].b]=0;
            mp[edge[i].b][edge[i].a]=0;
            
        }
        cin>>q;
        int k=q;
        while(q--)
        {
            string query;
            cin>>query;
            int l,r;
            if(query=="query")
            {
                cin>>l;
                l++;
                a[q+1]=l;
                b[q+1]=-1;
            }
            else if(query=="destroy")
            {
                cin>>l>>r;
                l++;
                r++;
                a[q+1]=l;
                b[q+1]=r;
                mp[l][r]=1;
            }
        }
        for(int i=1; i<=m; ++i)
        {
            if(!mp[edge[i].a][edge[i].b]&&!mp[edge[i].b][edge[i].a])
            {
                int xx=fin(edge[i].a);
                int yy=fin(edge[i].b);
                if(xx!=yy)
                {
                    if(ene[xx]>ene[yy])
                        rt[yy]=xx;
                    else if(ene[xx]<ene[yy])
                        rt[xx]=yy;
                    else
                        rt[max(xx,yy)]=min(xx,yy);
                }
            }
        }
        int num=1;
//        cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
//        for(int i=1;i<=n;++i)
//        cout<<rt[i]<<' '<<endl;
//            cout<<"\\\\\\\\\\\\\\\\\\\\\\\\" <<endl;
        for(int i=1; i<=k; ++i)
        {
            if(b[i]==-1)
            {
                int xx=fin(a[i]);
                if(xx!=a[i]&&ene[xx]>ene[a[i]])
                    ans[num++]=xx-1;
                else
                    ans[num++]=-1;
            }
            else
            {
                int xx=fin(a[i]);
                int yy=fin(b[i]);
                if(xx!=yy)
                {
                    if(ene[xx]>ene[yy])
                        rt[yy]=xx;
                    else if(ene[xx]<ene[yy])
                        rt[xx]=yy;
                    else
                        rt[max(xx,yy)]=min(xx,yy);
                }
            }
        }
        if(cas++) cout<<endl;
        for(int i=num-1; i>=1; i--)
            cout<<ans[i]<<endl;
            mp.clear();
    }
    return 0;
}
//ZOJ 3261
//用并查集来维护能互相联系到的点，并让并查集的根节点(集合代表）是这个集合中权值最大且序号最小的元素。如何实现？只要在合并集合函数中进行判断即可，让权值大的点成为根节点。
//
//问题出在拆边（destroy）上，并查集并无法实现这个功能。但是有一个很巧妙的做法，先记录Q条指令，对于不会被destroy的边，直接连起来。然后倒着处理这Q条指令，遇到destroy后将这条边在加上即可。
//
//有几个要注意的地方：
//①每个星球只能向比自己power大的星球，所以如果这个星球所在集合的代表和这个星球power一样大（只是序号更小所以成为了集合代表），那么这个星球也是没法求援的。
//②两组输出的数据间需要加一个空行，最后一组数据不需要输出空行
//③个人是用一个结构体来记录边的信息的，然后用map来判断哪些边会被destroy。然后就出现了问题，后来才知道map会对key值进行排序，所以要重载操作符（<和==都要重载）
//④记得初始化时清空map（WA的教训 ）
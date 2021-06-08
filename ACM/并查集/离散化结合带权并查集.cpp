#include<string.h>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;
int st[10005];
int en[10005];
int ans[10005];
int rt[10005];
int dis[10005];
int pos[10005];
map<int,int>mapp;
int fin(int x)
{
    if(x==rt[x])
        return x;
    int root=fin(rt[x]);
    dis[x]^=dis[rt[x]];
    return rt[x]=root;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0; i<=2*m+10; ++i)
        rt[i]=i;
    int cnt=1;
    for(int i=1; i<=m; ++i)
    {
        char str[5];
        scanf("%d%d%s",&st[i],&en[i],&str);
        if(strcmp(str,"even")==0)
            ans[i]=0;
        else
            ans[i]=1;
        pos[cnt++]=st[i];
        pos[cnt++]=en[i];
    }
    sort(pos+1,pos+cnt);
//    for(int i=1;i<cnt;++i)
//        cout<<pos[i]<<' ';
//    cout<<endl;
    int num=1;
    for(int i=1; i<cnt; ++i)
        if(pos[i]!=pos[i-1])
//            cout<<pos[i]<<' '<<num<<endl;
            mapp[pos[i]]=num++;
    int sum=0;
//    for(int i=1; i<=m; ++i)
//        cout<<st[i]<<' '<<en[i]<<' '<<ans[i]<<endl;
    for(int i=1; i<=m; ++i)
    {
        st[i]=mapp[st[i]];
        en[i]=mapp[en[i]];
        st[i]--;
        int xx=fin(st[i]);
        int yy=fin(en[i]);
        if(xx!=yy)
        {
            rt[xx]=yy;
            dis[xx]=dis[st[i]]^dis[en[i]]^ans[i];
        }
        else if(dis[st[i]]^dis[en[i]]!=ans[i])
            break;
        sum++;
//        for(int j=0;j<=n;++j)
//            cout<<rt[j]<<' ';
//        cout<<endl;
    }
    printf("%d\n",sum);
}
//poj 1733 
//离散化过程，先输入1~n个数--->a[1]~a[n],然后对a[1]~a[n]进行排序，最后用一个新的数组mapp进行数值和位置的映射-->mapp[a[i]]=i。下一次取数a[i],可以用mapp直接获得a[i]的位置，也就是离散化后的值。
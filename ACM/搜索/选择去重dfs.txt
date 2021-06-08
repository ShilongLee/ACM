#includestdio.h
#includealgorithm
#includestring.h
using namespace std;
int a[105],ans[105],flag=0,k,n;
int cmp(int a,int b)
{
    return ab;
}
void dfs(int now,int nb,int st)
{
    if(nown)
        return ;
    if(now==n)
    {
        flag=1;
        for(int i=1; inb; i++)
        {
            if(i!=nb-1)
                printf(%d+,ans[i]);
            else
                printf(%dn,ans[i]);
        }
        return ;
    }
    for(int i=st; i=k; i++)
    {
        if(i==sta[i]!=a[i-1])
        {
            ans[nb]=a[i];
            dfs(now+a[i],nb+1,i+1);
        }
    }
}
int main()
{
    while(~scanf(%d%d,&n,&k)&&n&&k)
    {
        memset(ans,0,sizeof(ans));
        for(int i=1; i=k; i++)
            scanf(%d,&a[i]);
        printf(Sums of %dn,n);
        sort(a+1,a+k+1,cmp);
        flag=0;
        dfs(0,1,1);
        if(flag==0)
            printf(NONEn);
    }
}
4->2->2 （√)
2<-4->2 （去重一个）

//HDU 1258
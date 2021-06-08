#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
long long a[200],dp[200][5];
//sta=0 无 sta=1 上一位是5 sta=2 上一位是52 sta=3 是520数
long long dfs(long long pos,long long before,long long doing)//pos：位数，从1开始算个位；before：前一位是否为6  1/0  doing：区间是否完整 0/1
{
    long long ans=0,s,i;//ans符合条件数字的个数和
    if(pos==0)//跑到个位数字时，每个数字符合条件的话算上1个；
        return before==3;
    if((!doing)&&dp[pos][before]!=-1)//区间完整 并且相同状态的区间已经求过了；
        return dp[pos][before];
    s=doing?a[pos]:9;//区间判断
    for(i=0; i<=s; i++)
    {
        long long nowsta;
        if(before==3)
            nowsta=3;
        else if(i==5)
            nowsta=1;
        else if(before==1&&i==2)
            nowsta=2;
        else if(before==2&&i==0)
            nowsta=3;
        else
            nowsta=0;
        ans+=dfs(pos-1,nowsta,doing&&i==s);
    }
    if(!doing)//如果区间完整，进行记忆。
        dp[pos][before]=ans;//每个区间分成两类，一类是前面为6的，另一类为前面不为6的。例：1~100，个位区间0~9分为两种，一种前面为6的为dp[pos][before]=8（个各位区间不含2也不含4，所以10-2=8）,另一种为正常区间为9个（不含4）；
    return ans;
}
long long solve(long long n)
{
    long long len=0;
    memset(a,0,sizeof(a));
    while(n)
    {
        a[++len]=n%10;
        n/=10;
    }//计算输入数字的位数，从第一位开始保存，100->a[1]=0,a[2]=0,a[3]=1;
    return dfs(len,0,1);
}
int main()
{
    long long t;
    scanf("%lld",&t);
    memset(dp,-1,sizeof(dp));
    while(t--)
    {
        long long n;
        scanf("%lld",&n);
        printf("%lld\n",solve(n)-solve(1));
    }
}
//湖南大学第十四届ACM F题Find the AFei Numbers；
//牛客：https://ac.nowcoder.com/acm/contest/338#question；

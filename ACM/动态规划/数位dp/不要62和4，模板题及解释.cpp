#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int a[20],dp[20][2];
int dfs(int pos,int before,int doing)//pos：位数，从1开始算个位；before：前一位是否为6  1/0  doing：区间是否完整 0/1
{
    int ans=0,s,i;//ans符合条件数字的个数和
    if(pos==0)//跑到个位数字时，每个数字符合条件的话算上1个；
        return 1;
    if((!doing)&&dp[pos][before]!=-1)//区间完整 并且相同状态的区间已经求过了；
        return dp[pos][before];
    s=doing?a[pos]:9;//区间判断
    for(i=0; i<=s; i++)
    {
        if(i==4||i==2&&before)//如果本位等于4，或者上一位为6并且本位为2，也就是4和62，跳过，不再进行向下的搜索。
            continue ;
        ans+=dfs(pos-1,i==6,doing&&i==s);//搜索。
    }
    if(!doing)//如果区间完整，进行记忆。
            dp[pos][before]=ans;//每个区间分成两类，一类是前面为6的，另一类为前面不为6的。例：1~100，个位区间0~9分为两种，一种前面为6的为dp[pos][before]=8（个各位区间不含2也不含4，所以10-2=8）,另一种为正常区间为9个（不含4）；
    return ans;
}
int solve(int n)
{
    int len=0;
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
    int n,m;
    while(~scanf("%d%d",&n,&m)&&n&&m)
    {
        memset(dp,-1,sizeof(dp));
        printf("%d\n",solve(m)-solve(n-1));//返回对应区间有效数字个数；
    }
    return 0;
}
//HDU 2089
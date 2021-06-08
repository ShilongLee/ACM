#include<iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
#include<string>
using namespace std;
int n;
string s[10];
int maxlen=0;
int flag=0;
char dir[4]= {'A','C','G','T'};
int pos[15];
int will()//预估
{
    int ans=0;
    for(int i=0; i<n; i++)
    {
        int k=s[i].length()-pos[i];
        ans=max(ans,k);
    }
    return ans;
}
void dfs(int step)
{
    if(flag)
        return;
    if(step+will()>maxlen)//当前+预估超过限制层数返回
        return;
    if(will()==0)
    {
        flag=1;
        cout<<step<<endl;
        return;
    }
    int pre[15];
    for(int i=0; i<4; i++)
    {
        int f=0;
        for(int j=0; j<n; j++)
        {
            pre[j]=pos[j];
            if(s[j][pos[j]]==dir[i])
            {
                f=1;
                pos[j]++;
            }
        }
        if(f)
        {
            dfs(step+1);
            for(int j=0; j<n; j++)
                pos[j]=pre[j];
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        maxlen=0;
        flag=0;
        memset(pos,0,sizeof(pos));
        cin>>n;
        for(int i=0; i<n; i++)
        {
            cin>>s[i];
            int len=s[i].length();
            maxlen=max(maxlen,len);
        }
        while(1)
        {
            dfs(0);
            maxlen++;
            if(flag)
                break;
        }
    }
}

//HUD 1560
//IDA*算法在DFS的搜索里面，可能会面临一个答案的层数很低，但是DFS搜到了另为一个层数很深的分支里面导致时间很慢，但是又卡BFS的空间，这个时候，可以限制DFS的搜索层数，一次又一次放宽搜索的层数，知道搜索到答案就退出，时间可观，结合了BFS和DFS的优点于一身。
//IDA*在搜索时剪枝掉不可能有结果的解空间，当前+预估超过限制层数时就可返回，（意味着不可完成）没必要继续搜索剩余的层数浪费时间。比如已经搜索完了三位，要解出答案至少还要四位，但是控制层数为6位，所以这层可以直接返回了，没必要搜索。控制层数初始为人为预估最小的层数，然后每次加一，逐渐放宽长度，这样解出来的一定是最小解，因为层数由小到大。
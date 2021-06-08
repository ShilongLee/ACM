#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;
const int N=1005;
const int inf=0x3f3f3f3f;
int disp[N];
int disn[N];
int visp[N];
int visn[N];
struct node
{
    int pos,weight;
    node(int a,int b)
    {
        pos=a;
        weight=b;
    }
    bool operator<(const node& a)const
    {
        return weight>a.weight;
    }
};
vector<node>positive[N];
vector<node>negative[N];
void dij1(int st)
{
    memset(disp,inf,sizeof(disp));
    priority_queue<node>qu;
    //int pre[N]; pre[st]=st;//路径记录
    disp[st]=0;
    qu.push(node(st,0));
    while(!qu.empty())
    {
        node f=qu.top();
        qu.pop();
        int p=f.pos;
        if(visp[p])
            continue;
        visp[p]=1;
        for(int i=0; i<positive[p].size(); ++i)
        {
            int pos=positive[p][i].pos;
            if(!visp[pos]&&disp[p]+positive[p][i].weight<disp[pos])
            {
                disp[pos]=disp[p]+positive[p][i].weight;
                //pre[pos]=p;//路径记录
                qu.push(node(pos,disp[pos]));
            }
        }
    }
}
void dij2(int st)
{
    memset(disn,inf,sizeof(disn));
    priority_queue<node>qu;
    //int pre[N]; pre[st]=st;//路径记录
    disn[st]=0;
    qu.push(node(st,0));
    while(!qu.empty())
    {
        node f=qu.top();
        qu.pop();
        int p=f.pos;
        if(visn[p])
            continue;
        visn[p]=1;
        for(int i=0; i<negative[p].size(); ++i)
        {
            int pos=negative[p][i].pos;
            if(!visn[pos]&&disn[p]+negative[p][i].weight<disn[pos])
            {
                disn[pos]=disn[p]+negative[p][i].weight;
                //pre[pos]=p;//路径记录
                qu.push(node(pos,disn[pos]));
            }
        }
    }
}
int main()
{
    int n,m,ed;
    cin>>n>>m>>ed;
    int x,y,z;
    for(int i=0; i<m; ++i)
    {
        cin>>x>>y>>z;
        positive[x].push_back(node(y,z));
        negative[y].push_back(node(x,z));
    }
    dij1(ed);
    dij2(ed);
    int ans=0;
    for(int i=1; i<=n; ++i)
        if(i!=ed)
            ans=max(ans,disp[i]+disn[i]);
    cout<<ans<<endl;
}

//poj 3268
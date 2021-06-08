#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
const int N = 1005;
const int M = 250005;
//n个点,m条边,最多ans对匹配,从x-->y有一条无向边,like为对象(匹配点),col每次搜索进行黑白染色,pre记录前驱节点,rt为祖先(所点后的花根),给每个花的染颜色(++cnt),vis为每个点染的花色(属于哪个花)
int n, m, ans, x, y, like[N], v[M], first[M], ext[M], num, col[N], pre[N], rt[N], cnt, vis[N];
void init()
{
    memset(like, 0, sizeof(like));
    memset(vis, 0, sizeof(vis));
    memset(first, -1, sizeof(first));
    ans = cnt = 0;
    num = 1;
}
void add(int x, int y)
{
    v[++num] = y;
    ext[num] = first[x];
    first[x] = num;
}
int fin(int x) //
{
    if (rt[x] == x)
        return x;
    return rt[x] = fin(rt[x]);
}
int LCA(int x, int y)
{
    ++cnt; //每朵花染不一样的颜色
    x = fin(x);
    y = fin(y);
    while (vis[x] != cnt) //某一点同时两次被染色，即为总花根
    {
        vis[x] = cnt;
        x = fin(pre[like[x]]);
        if (y)
            swap(x, y);
    }
    return x;
}
void shrink(int x, int y, int lca, queue<int> &q)
{
    while (fin(x) != lca) //从这两个点一直缩到花根(每次只缩一边)
    {
        pre[x] = y;  //非匹配点记录前驱 1==2--3==4 pre[2]=3 pre[3]=2
        y = like[x]; //缩x这边的点
        if (col[y] == 2)
            col[y] = 1, q.push(y);
        if (fin(x) == x)
            rt[x] = lca;
        if (fin(y) == y)
            rt[y] = lca;
        x = pre[y];
    }
}
void aug(int v) //从v往前增广
{
    /*
    (实现过程 ==为匹配边  --为未匹配边) 
    增广前:1--2==3--4==5--6(v)    
    增广后:1==2--3==4--5==6(v)    
    从6(v)依次往前更改增广路的匹配
    */
    int t;
    while (v)
    {
        t = like[pre[v]]; //令t=like[5] 增广前like[5]也就是4
        like[v] = pre[v]; //然后把5、6匹配上 like[6]=5
        like[pre[v]] = v; //like[5]=6
        v = t;            //v=4
    }
}
bool bfs(int st)
{
    queue<int> q;
    q.push(st);
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (int i = first[f]; ~i; i = ext[i])
        {
            int p = v[i];
            if (!col[p]) //如果没被染过色(搜过)
            {
                pre[p] = f;   //记录前驱
                if (!like[p]) //找到増广路终点，进行増广
                {
                    aug(p);      //增广
                    return true; //增广成功
                }
                else //被匹配了
                {
                    col[p] = 2;       //染成白色
                    col[like[p]] = 1; //和f匹配，不要这个点之前的匹配，让他再找一个
                    q.push(like[p]);  //让她之前的匹配再找一个
                }
            }
            else //被染色(搜过)
            {
                if (fin(f) == fin(p)) //已经是一朵花就不用缩点
                    continue;
                if (col[p] == 1) //是个奇环,缩成一个点对外进行匹配
                {
                    int lca = LCA(f, p);  //找到这两个点的lca并且把所有的点染成黑色(黑色可以进行增广)
                    shrink(f, p, lca, q); //缩点
                    shrink(p, f, lca, q); //缩点
                }
            }
        }
    }
    return false;
}
bool blossom(int st)
{
    //每次进行初始化，因为要对每个点求增广路径，类似匈牙利算法的memset(vei,false,sizeof(vis));
    memset(col, 0, sizeof(col)); //每个点的颜色，黑or白
    memset(pre, 0, sizeof(pre)); //每个点的前驱节点
    for (int i = 1; i <= n; ++i) //重置每个点的祖先(花根)
        rt[i] = i;
    col[st] = 1; //初始颜色为黑色
    if (bfs(st)) //bfs就是进行增广路径的搜索,类似于匈牙利的match();
        return true;
    else
        return false;
}
int main()
{
    init();
    cin >> n >> m; //n个点m条边
    for (int i = 1; i <= m; ++i)
    {
        cin >> x >> y;            //x-->y有一条无向边
        if (!like[x] && !like[y]) //两个点都没匹配过就进行匹配，最后建完图得到的ans就是初始的简单的匹配（就是能匹配就匹配不管对不对）
        {
            like[x] = y;
            like[y] = x;
            ans++;
        }          //配对两个点，答案加一对
        add(x, y); //建立无向边
        add(y, x); //建立无向边
    }
    for (int i = 1; i <= n; ++i)    //对每个没有匹配过的点进行增广
        if (!like[i] && blossom(i)) //这个点没有进行匹配过并且增广成功，结果加一，代表多了一对
            ans++;
    cout << ans << endl;         //输出最后匹配的对数
    for (int i = 1; i <= n; ++i) //输出匹配情况
        cout << like[i] << ' ';
    cout << endl;
    return 0;
}
//uoj79
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int inf = 0x3f3f3f3f; //无穷
struct platform             //平台结构体
{
    int l, r, h;
    platform() {}
    platform(int a, int b, int c)
    {
        l = a, r = b, h = c;
    }
    bool operator<(const platform &tmp) const //重载函数按照高度从大到小排序
    {
        return h > tmp.h;
    }
} a[N];              //平台
int n, sx, sh, maxh; //n个平台  起始点坐标 sx  sh  最大高度maxh
int dp[N][2];        //dp[i][0]从左边缘走的最小时间   从右边缘走的最小时间
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        cin >> n >> sx >> sh >> maxh;
        for (int i = 1; i <= n; ++i)
            cin >> a[i].l >> a[i].r >> a[i].h;
        a[n + 1] = platform(-20000, 20000, 0); //添加一个地面
        a[n + 2] = platform(sx, sx, sh);       //添加一个起始点
        sort(a + 1, a + 3 + n);                //按照高度从大到小排序
        for (int i = n + 1; i >= 1; --i)       //从底向上进行dp
        {
            /*因为是从底向上的dp，所以高度低于当前的平台都已经计算完，*/
            /*当前平台从左面走*/
            bool flag = false;
            for (int j = i + 1; j <= n + 1; ++j)
            {
                if (a[i].h - a[j].h <= maxh && a[i].l >= a[j].l && a[i].l <= a[j].r)
                {
                    dp[i][0] = a[i].h - a[j].h + min(dp[j][0] + a[i].l - a[j].l, dp[j][1] + a[j].r - a[i].l); //因为从底向上，要掉落平台的左右都算完了，当前平台高度-要掉落的平台高度+min(从要掉落的平台左边走，从要掉落的平台右边走)
                    flag = true;
                    break;
                }
            }
            if (!flag)
                dp[i][0] = a[i].h > maxh ? inf : a[i].h;

            /*当前平台从右面走*/
            flag = false;
            for (int j = i + 1; j <= n + 1; ++j)
            {
                if (a[i].h - a[j].h <= maxh && a[i].r >= a[j].l && a[i].r <= a[j].r)
                {
                    dp[i][1] = a[i].h - a[j].h + min(dp[j][0] + a[i].r - a[j].l, dp[j][1] + a[j].r - a[i].r); //因为从底向上，要掉落平台的左右都算完了，当前平台高度-要掉落的平台高度+min(从要掉落的平台左边走，从要掉落的平台右边走)
                    flag = true;
                    break;
                }
            }
            if (!flag)
                dp[i][1] = a[i].h > maxh ? inf : a[i].h;
        }
        cout << dp[1][0] << endl; //走到起始点就得出结果了
    }
    return 0;
}
//poj 1661
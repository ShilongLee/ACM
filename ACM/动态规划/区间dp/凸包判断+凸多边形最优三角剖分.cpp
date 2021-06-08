#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 305;
const int inf = 0x3f3f3f3f;
int n, mod, dp[N][N];
struct Point
{
    double x, y;
    Point() {}
    Point(double xx, double yy) : x(xx), y(yy) {}
    bool operator<(const Point &a) const
    {
        if (x == a.x)
            return y < a.y;
        return x < a.x;
    }
    Point operator-(const Point a) const
    {
        return Point(x - a.x, y - a.y);
    }
    friend ostream &operator<<(ostream &output, const Point &a)
    {
        output << a.x << ' ' << a.y << endl;
        return output;
    }
} p[N], st[N];

bool check(Point a, Point b)
{
    return a.x * b.y <= b.x * a.y;
}

bool judge()
{
    sort(p + 1, p + n + 1);
    int head = 0;
    //凸包下半边
    for (int i = 1; i <= n; ++i)
    {
        while (head > 1 && check(st[head] - st[head - 1], p[i] - st[head]))
            head--;
        st[++head] = p[i];
    }
    int tmp = head;
    //凸包上半边
    for (int i = n - 1; i >= 1; --i) //起点一定要加进去，为了把栈里面不符合的点除去，然后最后结果减1即可
    {
        while (head > tmp && check(st[head] - st[head - 1], p[i] - st[head]))
            head--;
        st[++head] = p[i];
    }
    return head - 1 == n;
}

int cost(Point a, Point b)
{
    return ((int)(abs(a.x + b.x) * abs(a.y + b.y))) % mod;
}
int main()
{
    while (cin >> n >> mod)
    {
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 1; i <= n; ++i)
            cin >> p[i].x >> p[i].y;
        if (n <= 3)
        {
            puts("0");
            continue;
        }
        else if (!judge())
        {
            cout << "I can't cut." << endl;
            continue;
        }
        for (int r = 2; r <= n - 1; ++r)
            for (int i = 1; i <= n - r; ++i)
            {
                int j = i + r;
                for (int k = i + 1; k <= j - 1; ++k)
                    dp[i][j] = min(dp[i][j], (abs(i - k) > 1 ? dp[i][k] : 0) + (abs(k - j) > 1 ? dp[k][j] : 0) + (abs(i - k) > 1 ? cost(st[i], st[k]) : 0) + (abs(k - j) > 1 ? cost(st[k], st[j]) : 0));
            }
        cout << dp[1][n] << endl;
    }
    return 0;
}
//zoj3537
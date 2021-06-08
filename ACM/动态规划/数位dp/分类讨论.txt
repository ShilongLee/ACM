#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int f[N][N], k, b, x, y;
void init()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= i; ++j)
            if (!j)
                f[i][j] = 1;
            else
                f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
}
int solve(int n)
{
    if (!n)
        return 0;
    vector<int> ve;
    while (n)
        ve.push_back(n % b), n /= b;
    int res = 0;
    int last = 0;
    for (int i = ve.size() - 1; i >= 0; --i)
    {
        int x = ve[i];
        if (x)
        {
            res += f[i][k - last];
            if (x > 1)
            {
                if (k - last - 1 >= 0)
                    res += f[i][k - last - 1];
                break;
            }
            else
            {
                last++;
                if (last > k)
                    break;
            }
        }
        if (!i && last == k)
            res++;
    }
    return res;
}
int main()
{
    init();
    cin >> x >> y >> k >> b;
    cout << solve(y) - solve(x - 1) << endl;
    return 0;
}
//ACwing 1081
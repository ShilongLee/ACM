#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
typedef long long ll;
const ll N = 105;
const ll mod = 1e9 + 7;
ll A[N][N], n, k;
ll result[N][N];
void multi(ll a[][N], ll b[][N], ll n)
{
    ll tmp[N][N];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j] % mod) % mod;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = (tmp[i][j] + mod) % mod;
}
void Matrix_pow(ll A[][N], ll k, ll n)
{
    memset(result, 0, sizeof(result));
    for (int i = 1; i <= n; ++i)
        result[i][i] = 1;
    while (k)
    {
        if (k & 1)
            multi(result, A, n);
        multi(A, A, n);
        k >>= 1;
    }
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> A[i][j];
    Matrix_pow(A, k, n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << result[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
//洛谷3390
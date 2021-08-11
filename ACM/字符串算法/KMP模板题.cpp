#include <iostream>
#include <string.h>
#include <algorithm>
#include <string>
using namespace std;
const int N = 1e6 + 5;
int n, m;
int a[N];
int b[N];
int ext[N];
void get_ext()
{
    int j = 0, k = -1;
    ext[0] = -1;
    while (j < m)
    {
        if (k == -1 || b[j] == b[k])
        {
            if (b[++j] == b[++k])
                ext[j] = ext[k];
            else
                ext[j] = k;
        }
        else
            k = ext[k];
    }
}
int KMP()
{
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (j == -1 || a[i] == b[j])
            ++i, ++j;
        else
            j = ext[j];
    }
    if (j == m)
        return i - j + 1;
    else
        return -1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int j = 0; j < m; ++j)
            cin >> b[j];
        get_ext();
        cout << KMP() << endl;
    }
    return 0;
}
//hdu1711
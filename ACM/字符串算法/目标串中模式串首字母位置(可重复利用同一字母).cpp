#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
string s1, s2;
int len1, len2;
int ext[N];
set<int> s;

void get_ext()
{
    int j = 0, k = -1;
    ext[0] = -1;
    while (j <= len2)
    {
        if (k == -1 || s2[j] == s2[k])
            ext[++j] = ++k;
        else
            k = ext[k];
    }
}

void KMP()
{
    int i = 0, j = 0;
    while (i < len1)
    {
        if (j == -1 || s1[i] == s2[j])
            ++i, ++j;
        else
            j = ext[j];
        if (j == len2)
        {
            s.insert(i - j + 1);
            j = ext[j];      
        }
    }
}

int main()
{
    s.clear();
    cin >> s1 >> s2;
    len1 = s1.length();
    len2 = s2.length();
    s1.push_back('a');
    s2.push_back('a');
    get_ext();
    KMP();
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << endl;
    for (int i = 1; i <= len2; ++i)
        cout << ext[i] << ' ';
    cout << endl;
    return 0;
}
//洛谷3375
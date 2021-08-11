#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;

const int LEN = 105;
int ext[LEN];      //ext����
char target[LEN];  //Ŀ�괮
char pattern[LEN]; //ģʽ��
int len_target, len_pattern;

void get_ext()
{
    int j = 0, k = -1;
    ext[0] = -1;
    while (j < len_pattern)
    {
        if (k == -1 || pattern[j] == pattern[k])
        {
            //比如，如果用之前的next 数组方法求模式串“abab”的next 数组，可得其next 数组为-1 0 0 1（0 0 1 2整体右移一位，初值赋为-1），当它跟下图中的文本串去匹配的时候，发现b跟c失配，于是模式串右移j - next[j] = 3 - 1 =2位。
            //右移2位后，b又跟c失配。事实上，因为在上一步的匹配中，已经得知p[3] = b，与s[3] = c失配，而右移两位之后，让p[ next[3] ] = p[1] = b 再跟s[3]匹配时，必然失配。问题出在哪呢？
            ++j, ++k;
            if (pattern[j] == pattern[k])
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
    while (i < len_target && j < len_pattern)
    {
        if (j == -1 || target[i] == pattern[j])
            ++i, ++j;
        else
            j = ext[j];
    }
    if (j == len_pattern)
        return i - j;
    else
        return -1;
}

int main()
{
    cin >> target;
    cin >> pattern;
    len_target = strlen(target);
    len_pattern = strlen(pattern);
    get_ext();
    int ans = KMP();
    cout << ans << endl;
}
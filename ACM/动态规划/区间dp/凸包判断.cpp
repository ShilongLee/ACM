Andrew算法是Graham算法的变种。
其主要思想为把凸包上的点依次放入栈中，
如果发现形成了凹多边形（叉积为负值）
就删除一些点，使得又能够维持凸的形态。

这时就会发现，处理各个点需要按照x从左往右的顺序，排序即可
当然，这只是处理了下凸的一个凸壳，倒过来再刷一次，就得到了整个凸包

处理壳的方向为
 <-<-<-<-<-
\                  /
  ->->->->

1、先把点排序 x从小到大，x相等y从小到大

2、先把第一个点和第二个点加入栈中，然后从第三个开始一直到第N个点进行下半凸壳判断

3、当处理下半凸壳（逆时针从左到右）的时候:

            b
          /   \
x --- a     c --- y

这个a->b->c 凹进去了，数学上可以表示为a,b的斜率大于b,c的斜率，所以遇到这种情况，就把凹进去的点b去掉就行了

4、先把第N-1个点加入栈中，然后从第N-2个点开始进行上半凸壳判断

5、处理上半凸壳（逆时针从右到左）的时候:

x --- a      c --- y
          \   /
            b

这个c->b->a 凹进去了，数学上可以表示为c,b的斜率大于b,a的斜率，所以遇到这种情况，就把凹进去的点b去掉就行了

6、最后看一下加进去点的个数，如果全部点都加进去了说明没有凹点，是凸包

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
} p[N], st[N];//p是点,st是栈

bool check(Point a, Point b)
{
    return a.x * b.y <= b.x * a.y;
}//检查斜率

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
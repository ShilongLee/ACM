/*
leetcode 11 双指针常考想法题
题目
给你 n 个非负整数 a1，a2，…，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器。

思路
两个指针i,j，开始时指向第一个和最后一个。
假设height[i]<=height[j]
那么可以看出，i固定，无论怎么移动，所得到的值都比i、j之间的面积小，因为面积只决定于两端之间最短的一端，以及两端的距离，而当前的距离最远，因为i、j分别为第一个和最后一个。
所以，短的i可以直接丢掉了，因为以它为一端的最大值已经算完了。
直接把i往右移就可以了。
height[i]>=height[j] 同理把j往左移。
用maxs取以每一个垂直线的最大值，最后返回maxs就可以了。

代码
*/
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int i = 0, j = height.size() - 1;
        int maxs = 0;
        while (i < j)
        {
            int s = min(height[i], height[j]) * (j - i);
            maxs = max(maxs, s);
            if (height[i] <= height[j])
                ++i;
            else
                --j;
        }
        return maxs;
    }
};
//leetcode 11
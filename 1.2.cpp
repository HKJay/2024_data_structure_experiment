/*#include <iostream>
using namespace std;

class Solution
{
public:
    int solve(int lens , int* num)
    {
        n = lens;
        nums = num;
        dfs(0);
        return ans;
    }
private:
    int ans = 0;
    int n;
    int* nums;//排列
    void dfs(int idx)//递归
    {
        if (idx == n)//终止条件
        {
            int val = 0;
            for(int inx = 0; inx < n; ++inx)
            {
                val += nums[inx] ^ (inx + 1);
            }
            ans |= val;
            return;
        }
        int mid;
        for (int i = idx; i < n; i++)
        {
            mid = nums[idx];    //依次交换位置
            nums[idx] = nums[i];
            nums[i] = mid;
            dfs(idx + 1);
            nums[i] = nums[idx];
            nums[idx] = mid;
        }
    }
};

int main() {
    int n;
    int res = 0;
    cin >> n;
    int *nums = new int[n];
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> nums[i];
    }
    Solution solution;
    cout << solution.solve(n , nums) << endl;
    return 0;
}*/
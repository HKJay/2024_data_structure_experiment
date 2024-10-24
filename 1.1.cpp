/*#include <iostream>
using namespace std;

class Solution {
public:
    int subsetXORSum(int* nums , int lens)
    {
        n = lens;
        son = new int[n];
        dfs(0, nums);
        return ans;
    }
private:
    int n;
    int *son;//子集
    int p = 0;//子集中末尾元素位置
    int ans = 0;
    void dfs(int idx, int* nums){ //递归
        if (idx == n){ //终止条件
            int val = 0;
            for (int i = 0 ; i < p ; ++i)
            {
                val += son[i] * (i + 1);
            }
            ans ^= val;
            return;
        }
        son[p] = nums[idx];
        ++p;
        dfs(idx + 1, nums);//将nums[idx]加入子集
        --p;
        dfs(idx + 1, nums);//不加入子集
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
    cout << solution.subsetXORSum(nums , n) << endl;
    return 0;
}*/
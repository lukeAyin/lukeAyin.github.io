#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int> nums, int k, int t) {
        int n=nums.size();
        set<int> has;
        for(int i=0;i<n;i++){
            int x=nums[i];
            // auto it=lower_bound(has.begin(),has.end(),max(x,INT_MIN+t)-t);
            auto it=has.lower_bound(max(x,INT_MIN+t)-t);//set的lower_bound不一样
            if(it!=has.end()&&*it<=min(nums[i],INT_MAX-t)+t){
                return true;
            }
            has.insert(x);
            if(i>=k){
                has.erase(nums[i-k]);
            }

        }
        return false;
    }
};
int main(){
    Solution s;
    // s.containsNearbyAlmostDuplicate({1,2,3,1},3,0);
    s.containsNearbyAlmostDuplicate({1,5,9,1,5,9},2,3);

}
/*
给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。

如果存在则返回 true，不存在返回 false。

示例 1：

输入：nums = [1,2,3,1], k = 3, t = 0
输出：true
0 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1
0 <= k <= 104
0 <= t <= 231 - 1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/7WqeDu/
*/
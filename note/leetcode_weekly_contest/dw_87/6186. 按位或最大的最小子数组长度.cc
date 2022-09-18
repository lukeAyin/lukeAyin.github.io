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
    vector<int> smallestSubarrays(vector<int> nums) {
        int n=nums.size();
        vector<int> cnt(32,0);
        auto addN=[&](int x){
            int i=0;
            while(x!=0){
                if(x&1){
                    cnt[i]++;
                }
                x>>=1;
                i++;
            }
        };
        auto checkN=[&](int x){
            int i=0;
            while(x!=0){
                if(x&1){
                    if(cnt[i]==1){
                        return false;
                    }
                }
                x>>=1;
                i++;
            }
            return true;
        };
        auto removeN=[&](int x){
            int i=0;
            while(x!=0){
                if(x&1){
                    cnt[i]--;
                }
                x>>=1;
                i++;
            }
        };
        vector<int> res(n,0);
        int r=n-1;
        for(int i=r;i>=0;i--){
            addN(nums[i]);
            while(r>i&&checkN(nums[r])){
                removeN(nums[r]);
                r--;
            }   
            res[i]=(r-i+1);
        }
        return res;
    }
};
int main(){
    Solution s;
    auto pf=[&](auto &V){
        for(auto v:V){
            cout<<v<<" ";
        }
    };
    auto vec=s.smallestSubarrays({1,0,2,1,3});//[3,3,2,2,1]
    pf(vec);
    vec=s.smallestSubarrays({0});
    pf(vec);
    vec=s.smallestSubarrays({1,0});
    pf(vec);
}
/*

给你一个长度为 n 下标从 0 开始的数组 nums ，数组中所有数字均为非负整数。对于 0 到 n - 1 之间的每一个下标 i ，你需要找出 nums 中一个 最小 非空子数组，它的起始位置为 i （包含这个位置），同时有 最大 的 按位或运算值 。

换言之，令 Bij 表示子数组 nums[i...j] 的按位或运算的结果，你需要找到一个起始位置为 i 的最小子数组，这个子数组的按位或运算的结果等于 max(Bik) ，其中 i <= k <= n - 1 。
一个数组的按位或运算值是这个数组里所有数字按位或运算的结果。

请你返回一个大小为 n 的整数数组 answer，其中 answer[i]是开始位置为 i ，按位或运算结果最大，且 最短 子数组的长度。

子数组 是数组里一段连续非空元素组成的序列。

 n == nums.length
1 <= n <= 105
0 <= nums[i] <= 109
*/
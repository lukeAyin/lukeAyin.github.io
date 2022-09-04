#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long 
using namespace std;
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n=nums.size();
        vector<ll> sum(n+1,0);
        for(int i=0;i<n;++i){
            sum[i+1]=sum[i]+nums[i];
        }
        int l=0;
        int r=0;
        ll ans=0;
        int let=0;
        while(r<n){
            ans|=nums[r];
            if(l>=r||ans==(sum[r+1]-sum[l])){
                r++;
                let=max(r-l,let);
            }else{
                while(l<r&&ans!=(sum[r+1]-sum[l])){
                    ans&=(~nums[l]);
                    ans|=nums[r];
                    l++;
                }
            }
        }
        return let;
    }
};
int main(){
    Solution s;
    FILE *fp=fopen("data.txt","r");
    vector<int> nums;
    int n;
    fscanf(fp,"%d",&n);
    while(n--){
        int t;
        fscanf(fp,"%d",&t);
        nums.emplace_back(t);
    }
    printf("%d\n",s.longestNiceSubarray(nums));
}
/*
给你一个由 正 整数组成的数组 nums 。

如果 nums 的子数组中位于 不同 位置的每对元素按位 与（AND）运算的结果等于 0 ，则称该子数组为 优雅 子数组。

返回 最长 的优雅子数组的长度。

子数组 是数组中的一个 连续 部分。

注意：长度为 1 的子数组始终视作优雅子数组。
1 <= nums.length <= 105
1 <= nums[i] <= 109
*/
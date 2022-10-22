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
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res;
        multiset<int> st;
        for(auto x:nums1){
            st.insert(x);
        }
        int n=nums2.size();
        auto it=st.begin();
        for(int i=0;i<n;i++){
            it=st.upper_bound(nums2[i]);
            if(it!=st.end()){
                res.emplace_back(*it);
                st.erase(it);
            }else{
                res.emplace_back(*st.begin());
                st.erase(st.begin());
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> a1={2,0,4,1,2};
    vector<int> a2={1,3,0,0,2};
    s.advantageCount(a1,a2);
}
/*
给定两个大小相等的数组 nums1 和 nums2，nums1 相对于 nums2 的优势可以用满足 nums1[i] > nums2[i] 的索引 i 的数目来描述。

返回 nums1 的任意排列，使其相对于 nums2 的优势最大化。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/advantage-shuffle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
示例 1：

输入：nums1 = [2,7,11,15], nums2 = [1,10,4,11]
输出：[2,11,7,15]
*/
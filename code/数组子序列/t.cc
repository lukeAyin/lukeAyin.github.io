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
    int minMoves(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> g;
        vector<int> s(1,0);
        for(int i=0;i<n;i++){
            if(nums[i]){
                g.emplace_back(i-g.size());
                s.emplace_back(s.back()+g.back());
            }
        }
        int m=g.size();
        int ans=INT_MAX;
        for(int left=0;left<=m-k;left++){
            int right=left+k;
            int mid=left+(k>>1);
            ans=min(ans,(1-k%2)*g[mid]+(s[right]-s[mid+1])-(s[mid]-s[left]));
        }
        return ans;
    }
};
int main(){
    Solution s;
}
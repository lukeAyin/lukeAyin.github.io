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
    int find(vector<int> &nums,int k,vector<int> &g){//kmp算法
        int m=g.size(),n=nums.size();
        if(k+m>n){
            return -1;
        }
        vector<int> pi(m);//转移矩阵
        for(int i=1,j=0;i<m;i++){
            while(j>0&&g[i]!=g[j]){
                j=pi[j-1];
            }
            if(g[i]==g[j]){
                j++;
            }
            pi[i]=j;
        }
        for(int i=k,j=0;i<n;i++){
            while(j>0&&nums[i]!=g[j]){
                j=pi[j-1];
            }
            if(nums[i]==g[j]){
                j++;
            }
            if(j==m){
                return i-m+1;
            }
        }
        return -1;
    }
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int n=nums.size();
        int m=groups.size();
        int k=0;
        for(int i=0;i<m;i++){
            k=find(nums,k,groups[i]);
            if(k==-1){
                return false;
            }
            k+=groups[i].size();
        }
        return true;
    }
};
int main(){
    Solution s;
}
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
    int largestIsland(vector<vector<int>> grid) {
        int n=grid.size();
        vector<int> parent(n*n,0);
        iota(parent.begin(),parent.end(),0);
        vector<int> cnt(n*n,0);
        function<int(int)> find=[&](int x)->int{
            if(parent[x]==x){
                return x;
            }
            return parent[x]=find(parent[x]);
        };
        auto union_set=[&](int x,int y){
            int fx=find(x);
            int fy=find(y);
            if(fx==fy){
                return false;
            }
            parent[fx]=fy;
            cnt[fy]+=cnt[fx];
            return true;
        };
        int move[4][2]={1,0,0,1,0,-1,-1,0};
        auto check=[&](int x,int y){
            return x>=0&&x<n&&y>=0&&y<n;
        };
        int res=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    cnt[i*n+j]=1;
                    for(int k=2;k<4;k++){
                        int ni=move[k][0]+i;
                        int nj=move[k][1]+j;
                        if(check(ni,nj)&&grid[ni][nj]==1){
                            union_set(i*n+j,ni*n+nj);
                            res=max(res,cnt[find(ni*n+nj)]);
                        }
                    }
                }
            }
        }
        set<int> has;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int val=1;
                if(grid[i][j]==0){
                    has.clear();
                    for(int k=0;k<4;k++){
                        int ni=move[k][0]+i;
                        int nj=move[k][1]+j;
                        if(check(ni,nj)&&grid[ni][nj]==1&&!has.count(find(ni*n+nj))){
                            val+=cnt[find(ni*n+nj)];
                            has.insert(find(ni*n+nj));
                        }
                        
                    }
                }
                res=max(res,val);
            }
        }
        return res;
        
    }
};

int main(){
    Solution s;
    cout<<s.largestIsland({{1,0},{0,1}});
    cout<<s.largestIsland({{1,1},{1,0}});
}
/*
给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。

返回执行此操作后，grid 中最大的岛屿面积是多少？

岛屿 由一组上、下、左、右四个方向相连的 1 形成。

n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] 为 0 或 1
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/making-a-large-island
*/
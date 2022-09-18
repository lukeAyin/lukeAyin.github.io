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
    int longestIncreasingPath(vector<vector<int>> matrix) {
        int m=matrix.size();
        int n=matrix[0].size();
        vector<vector<int>> vis(m,vector<int>(n,0));
        int move[4][2]={-1,0,1,0,0,-1,0,1};
        auto check=[&m,&n](int x,int y){
            return x>=0&&x<m&&y>=0&&y<n;
        };
        function<int(int,int)> dfs=[&](int x,int y)->int{
            if(vis[x][y]!=0){
                return vis[x][y];
            }
            int res=0;
            for(int i=0;i<4;i++){
                int nx=x+move[i][0];
                int ny=y+move[i][1];
                if(check(nx,ny)&&matrix[nx][ny]>matrix[x][y]){
                    res=max(res,dfs(nx,ny));
                }
            }
            res++;
            vis[x][y]=res;
            return res;
        };
        int res=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                res=max(res,dfs(i,j));
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    cout<<s.longestIncreasingPath({{9,9,4},{6,6,8},{2,1,1}});
}
/*
给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1

*/
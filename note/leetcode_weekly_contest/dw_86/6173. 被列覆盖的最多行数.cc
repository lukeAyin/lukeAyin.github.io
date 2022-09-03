#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
using namespace std;
class Solution {
public:
    bool check(int x,int y){
        return (x|y)==y;
    }
    static const int M=20;
    int mp[M];
    int m,n;
    int vis[M];
    int let;
    void init(){
        memset(mp,0,sizeof(mp));
        memset(vis,0,sizeof(vis));
        let=0;
    }
    void dfs(int cols,int ans,int k){
        if(cols<=0){
            int cnt=0;
            for(int i=0;i<m;++i){
                if(check(mp[i],ans)){
                    cnt++;
                }
            }
            let=max(let,cnt);
            // cout<<cnt<<" "<<ans<<endl;
            return;
        }
        for(int i=k;i<n;++i){
            if(!vis[i]){
                vis[i]=1;
                dfs(cols-1,ans|(1<<i),i+1);
                vis[i]=0;
            }
        }
    };
    int maximumRows(vector<vector<int>>& mat, int cols) {
        m=mat.size();
        n=mat[0].size();
        init();
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(mat[i][j])
                mp[i]|=(1<<j);
            }
            cout<<mp[i]<<" ";
        }
        dfs(cols,0,0);   
        return let;
    }
};
int main(){
    
}
/*
给你一个下标从 0 开始的 m x n 二进制矩阵 mat 和一个整数 cols ，表示你需要选出的列数。

如果一行中，所有的 1 都被你选中的列所覆盖，那么我们称这一行 被覆盖 了。

请你返回在选择 cols 列的情况下，被覆盖 的行数 最大 为多少。
*/
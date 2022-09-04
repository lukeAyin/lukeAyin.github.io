#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
using namespace std;

class Solution {
public:
    static const int M=3010;
    static const int MOD=1e9+7;
    int dp[2][M];
    int numberOfWays(int startPos, int endPos, int k) {
        startPos+=1005;
        endPos+=1005;
        memset(dp,0,sizeof(dp));
        dp[0][startPos]=1;
        for(int i=1;i<=k;++i){
            int idx=i%2;
            for(int j=1;j<M-1;++j){
                dp[idx][j]+=dp[1-idx][j-1];
                dp[idx][j]%=MOD;
                dp[idx][j]+=dp[1-idx][j+1];
                dp[idx][j]%=MOD;
            }
            memset(dp[1-idx],0,sizeof(dp[1-idx]));
        }
        return dp[k%2][endPos];
    }
};
int main(){
    
}

/*
给你两个 正 整数 startPos 和 endPos 。最初，你站在 无限 数轴上位置 startPos 处。在一步移动中，你可以向左或者向右移动一个位置。

给你一个正整数 k ，返回从 startPos 出发、恰好 移动 k 步并到达 endPos 的 不同 方法数目。由于答案可能会很大，返回对 109 + 7 取余 的结果。

如果所执行移动的顺序不完全相同，则认为两种方法不同。

注意：数轴包含负整数。
1 <= startPos, endPos, k <= 1000
*/
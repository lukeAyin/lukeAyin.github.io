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
    int maxProfit(int k, vector<int> prices) {
        int buy[k];
        int sell[k];
        int n=prices.size();
        memset(buy,128,sizeof buy);

        memset(sell,0,sizeof sell);
        for(int i=0;i<n;i++){
            buy[0]=max(buy[0],-prices[i]);
            sell[0]=max(sell[0],prices[i]+buy[0]);
            for(int j=1;j<k;j++){
                buy[j]=max(buy[j],sell[j-1]-prices[i]);
                sell[j]=max(sell[j],buy[j]+prices[i]);
            }
        }
        return sell[k-1];
    }
};
int main(){
    Solution s;
    cout<<s.maxProfit(2,{3,2,6,5,0,3});
}
/*
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1：

输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。

0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/
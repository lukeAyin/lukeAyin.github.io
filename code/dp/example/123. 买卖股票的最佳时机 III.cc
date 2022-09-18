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
    int maxProfit(vector<int> prices) {
        int buy[2];
        int sell[2];
        memset(sell,0,sizeof sell);
        int n=prices.size();
        buy[0]=-prices[0];
        buy[1]=-prices[0];
        for(int i=0;i<n;i++){
            buy[0]=max(buy[0],-prices[i]);
            sell[0]=max(sell[0],prices[i]+buy[0]);
            buy[1]=max(sell[0]-prices[i],buy[1]);
            sell[1]=max(sell[1],buy[1]+prices[i]);
        }
        return sell[1];
    }
};
int main(){
    Solution s;
    cout<<s.maxProfit({3,3,5,0,0,3,1,4});//output 6
}
/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1:

输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

1 <= prices.length <= 105
0 <= prices[i] <= 105
*/
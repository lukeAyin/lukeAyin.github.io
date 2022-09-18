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
    long long minimumMoney(vector<vector<int>> transactions) {
        int n=transactions.size();
        ll res=0;
        int max_cost=0;
        set<int> idx_has;
        for(int i=0;i<n;i++){
            int t1=transactions[i][0];
            int t2=transactions[i][1];
            if(t2-t1<0){
                res+=(t1-t2);
                max_cost=max(max_cost,t2);
            }else{
                max_cost=max(max_cost,t1);
            }
        }
        return res+max_cost;

    }   
};

int main(){
    Solution s;
    cout<<s.minimumMoney({{2,1},{5,0},{4,2}});
}
/*
给你一个下标从 0 开始的二维整数数组 transactions，其中transactions[i] = [costi, cashbacki] 。

数组描述了若干笔交易。其中每笔交易必须以 某种顺序 恰好完成一次。在任意一个时刻，你有一定数目的钱 money ，为了完成交易 i ，money >= costi 这个条件必须为真。执行交易后，你的钱数 money 变成 money - costi + cashbacki 。

请你返回 任意一种 交易顺序下，你都能完成所有交易的最少钱数 money 是多少。
1 <= transactions.length <= 105
transactions[i].length == 2
0 <= costi, cashbacki <= 109
*/
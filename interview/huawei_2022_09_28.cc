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
    vector<int> dailyTemperatures(vector<int> temperatures) {
        stack<int> stk;
        int n=temperatures.size();
        vector<int> res(n,0);
        for(int i=0;i<n;i++){
            while(!stk.empty()&&temperatures[stk.top()]<temperatures[i]){
                int idx=stk.top();
                stk.pop();
                res[idx]=i-idx;
            }
            stk.push(i);
        }
        return res;
    }
};
int main(){
    Solution s;
    auto pf=[](auto  A){
        for(auto x:A){
            cout<<x<<" ";
        }
    };
    pf(s.dailyTemperatures({73,74,75,71,69,72,76,73}));

}

/*
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天
，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
示例 2:

输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
示例 3:

输入: temperatures = [30,60,90]
输出: [1,1,0]

提示：

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100*/
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
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(),players.end());
        sort(trainers.begin(),trainers.end());
        int l1=0,l2=0;
        int n1=players.size();
        int n2=trainers.size();
        int res=0;
        while(l1<n1&&l2<n2){
            while(l2<n2&&players[l1]>trainers[l2]){
                l2++;
            }
            if(l2>=n2){
                return res;
            }
            l1++;
            l2++;
            res++;
        }
        return res;
    }
};
int main(){
    Solution s;
}
/*
给你一个下标从 0 开始的整数数组 players ，其中 players[i] 表示第 i 名运动员的 能力 值，同时给你一个下标从 0 开始的整数数组 trainers ，其中 trainers[j] 表示第 j 名训练师的 训练能力值 。

如果第 i 名运动员的能力值 小于等于 第 j 名训练师的能力值，那么第 i 名运动员可以 匹配 第 j 名训练师。除此以外，每名运动员至多可以匹配一位训练师，每位训练师最多可以匹配一位运动员。

请你返回满足上述要求 players 和 trainers 的 最大 匹配数。
1 <= players.length, trainers.length <= 105
1 <= players[i], trainers[j] <= 109
*/
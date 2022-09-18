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
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int a1,a2,b1,b2;
        vector<int> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        vector<int> sums(13,0);
        for(int i=0;i<12;i++){
            sums[i+1]=sums[i]+days[i];
        }
        auto getDays=[&](const string &str){
            return sums[stoi(str.substr(0,2))-1]+stoi(str.substr(3));
        };
        a1=getDays(arriveAlice);
        a2=getDays(leaveAlice);
        b1=getDays(arriveBob);
        b2=getDays(leaveBob);
        int res=max(min(b2,a2)-max(a1,b1)+1,0);
        return res;
    }
};

int main(){
    Solution s;
    // cout<<s.countDaysTogether("08-15","08-18","08-16","08-19");//3
    // cout<<s.countDaysTogether("10-01","10-31","11-01","12-31");//0
    cout<<s.countDaysTogether("01-20","04-18","01-01","08-30");//89
}
/*
Alice 和 Bob 计划分别去罗马开会。

给你四个字符串 arriveAlice ，leaveAlice ，arriveBob 和 leaveBob 。Alice 会在日期 arriveAlice 到 leaveAlice 之间在城市里（日期为闭区间），而 Bob 在日期 arriveBob 到 leaveBob 之间在城市里（日期为闭区间）。每个字符串都包含 5 个字符，格式为 "MM-DD" ，对应着一个日期的月和日。

请你返回 Alice和 Bob 同时在罗马的天数。

你可以假设所有日期都在 同一个 自然年，而且 不是 闰年。每个月份的天数分别为：[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31] 。
*/
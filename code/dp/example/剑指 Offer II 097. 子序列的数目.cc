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
    int numDistinct(string s, string t) {
        int m=s.size();
        int n=t.size();
        vector<int> dp(n+1,0);
        dp[0]=1;
        for(int i=1;i<=m;i++){
            for(int j=n;j>0;j--){
                if(s[i-1]==t[j-1]){
                    if(dp[j-1]<INT_MAX-dp[j])
                    dp[j]+=dp[j-1];
                }
            }
        }
        return dp[n];
    }
};

int main(){
    Solution s;
    cout<<s.numDistinct("rabbbit","rabbit");
    cout<<s.numDistinct("babgbag","bag");
}
/*
给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。
0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/21dk04
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
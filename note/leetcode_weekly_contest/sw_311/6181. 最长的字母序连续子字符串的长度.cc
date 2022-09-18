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
    int longestContinuousSubstring(string s) {
        int res=0;
        int n=s.size();
        for(int i=0;i<n;i++){
            int r=i+1;
            while(r<n&&s[r]==(s[r-1]+1)){
                r++;
            }
            res=max(res,r-i);
        }
        return res;
    }
};
int main(){
    Solution s;
}   

/*
字母序连续字符串 是由字母表中连续字母组成的字符串。换句话说，字符串 "abcdefghijklmnopqrstuvwxyz" 的任意子字符串都是 字母序连续字符串 。

例如，"abc" 是一个字母序连续字符串，而 "acb" 和 "za" 不是。
给你一个仅由小写英文字母组成的字符串 s ，返回其 最长 的 字母序连续子字符串 的长度。
*/
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
    string smallestSubsequence(string s) {
        int n=s.size();
        string res;
        int cnt[256];
        memset(cnt,0,sizeof(cnt));
        for(auto ch:s){
            cnt[ch]++;
        }
        deque<char> stk;
        bool ins[256];
        memset(ins,false,sizeof(ins));
        for(int i=0;i<n;++i){
            while(!stk.empty()&&stk.back()>s[i]&&cnt[stk.back()]>0){
                ins[stk.back()]=false;
                stk.pop_back();
            }
            cnt[s[i]]--;
            if(ins[s[i]]){
                continue;
            }
            ins[s[i]]=true;
            stk.push_back(s[i]);
        }
        return res.assign(stk.begin(),stk.end());
    }
};
int main(){
    
}
/*
返回 s 字典序最小的子序列，该子序列包含 s 的所有不同字符，且只包含一次。

注意：该题与 316 https://leetcode.com/problems/remove-duplicate-letters/ 相同
1 <= s.length <= 1000
s 由小写英文字母组成
*/
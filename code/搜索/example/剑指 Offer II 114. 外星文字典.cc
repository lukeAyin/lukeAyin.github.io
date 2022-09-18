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
    string alienOrder(vector<string>& words) {
        int n=words.size();
        const int M=26;
        set<char> has;
        vector<int> in(M,0);
        vector<vector<int>> g(M,vector<int>());
        auto addLine=[&](string& A,string &B){
            int len=min(A.size(),B.size());
            for(int i=0;i<len;i++){
                if(A[i]==B[i]){
                    continue;
                }
                g[A[i]-'a'].emplace_back(B[i]-'a'); 
                in[B[i]-'a']++;
                break;
            }
            if(A.size()<B.size()){
                return false;
            }
        };
        for(int i=0;i<n;i++){
            for(auto ch:words[i]){
                has.insert(ch);
            }
            for(int j=i+1;j<n;j++){
                if(!addLine(words[i],words[j])){
                    return "";
                }
            }
        }
        queue<int> q;
        for(int i=0;i<M;i++){
            if(has.count('a'+i)&&in[i]==0){
                q.push(i);
            }
        }
        string path;
        while(!q.empty()){
            auto cur=q.front();
            has.erase('a'+cur);
            path+=('a'+cur);
            q.pop();
            for(auto e:g[cur]){
                in[e]--;
                if(in[e]==0){
                    q.push(e);
                }
            }
        }
        for(auto it=has.begin();it!=has.end();it++){
            path+=(*it);
        }
        for(int i=0;i<M;i++){
            if(in[i]>0){
                return "";
            }
        }
        return path;
    }
};
int main(){
    Solution s;
    vector<string> words{"wrt","wrf","er","ett","rftt"};
    cout<<s.alienOrder(words)<<endl;
}
/*
现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。

给定一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序 。

请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，返回 "" 。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。

字符串 s 字典顺序小于 字符串 t 有两种情况：

在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t 。
如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。
 

示例 1：

输入：words = ["wrt","wrf","er","ett","rftt"]
输出："wertf"
示例 2：

输入：words = ["z","x"]
输出："zx"

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] 仅由小写英文字母组成
*/
#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
struct Node{
    Node* child[26];
    int cnt;
    Node(){
        for(int i=0;i<26;i++){
            child[i]=nullptr;
        }
        cnt=0;
    }
};
class Trie{
    public:
    Node *root;
    Trie(){
        root=new Node();
    }
    void insert(string &str){
        Node* node=root;
        for(auto ch:str){
            int id=ch-'a';
            if(node->child[id]==nullptr){
                node->child[id]=new Node();
            }
            node=node->child[id];
            node->cnt++;
        }
    }
    int getCnt(string &str){
        Node* node=root;
        int val=0;
        for(auto ch:str){
            int id=ch-'a';
            node=node->child[id];
            val+=node->cnt;
        }
        return val;
    }
};
class Solution {
public:
    vector<int> sumPrefixScores(vector<string> words) {
        Trie t;
        for(auto &w:words){
            t.insert(w);
        }
        int n=words.size();
        vector<int> res(n,0);
        for(int i=0;i<n;i++){
            res[i]=t.getCnt(words[i]);
        }
        return res;
    }
};

int main(){
    Solution s;
    auto pf=[](auto &vec){
        for(auto v:vec){
            cout<<v<<" ";
        }
    };
    auto vec=s.sumPrefixScores({"abc","ab","bc","b"});
    pf(vec);
}
/*
给你一个长度为 n 的数组 words ，该数组由 非空 字符串组成。

定义字符串 word 的 分数 等于以 word 作为 前缀 的 words[i] 的数目。

例如，如果 words = ["a", "ab", "abc", "cab"] ，那么 "ab" 的分数是 2 ，因为 "ab" 是 "ab" 和 "abc" 的一个前缀。
返回一个长度为 n 的数组 answer ，其中 answer[i] 是 words[i] 的每个非空前缀的分数 总和 。

注意：字符串视作它自身的一个前缀。
1 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] 由小写英文字母组成
*/
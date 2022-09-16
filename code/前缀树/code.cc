#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
struct Node{
    public:
    Node* child[26];
    bool end;
    Node(){
        for(int i=0;i<26;i++){
            child[i]=nullptr;
        }
        end=false;
    }
};

class Trie {
public:
    /** Initialize your data structure here. */
    Node* root;
    Trie() {
        root=new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* node=root;
        for(auto x:word){
            if(node->child[x-'a']==nullptr){
                node->child[x-'a']=new Node();
            }
            node=node->child[x-'a'];
        }
        node->end=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* node=root;
        for(auto x:word){
            if(node->child[x-'a']==nullptr){
                return false;
            }
            node=node->child[x-'a'];
        }
        return node->end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* node=root;
        for(auto x:prefix){
            if(node->child[x-'a']==nullptr){
                return false;
            }
            node=node->child[x-'a'];
        }
        return true;
    }
};
int main(){
    
}


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
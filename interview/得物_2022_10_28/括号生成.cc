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
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return string字符串vector
     */
    vector<string> res;
    vector<string> generateParenthesis(int n) {
        // write code here
        dfs(0,0,"",n);
        return res;
    }
    string getX(int x){
        string res;
        while(x--){
            res+=')';
        }
        return res;
    }
    inline void getL(string& ans){
        ans+='(';
    }
    void dfs(int p,int re,string ans,int n){
        if(p==n-1){
            if(re!=n){
                getL(ans);
                ans+=getX(n-re);
            }
            res.emplace_back(ans);
            return ;
        }
        getL(ans);
        for(int i=0;i<=(p-re+1);i++){
            dfs(p+1,re+i,ans+getX(i),n);
        }
    }
};

int main(){
    Solution s;
    auto res=s.generateParenthesis(3);
    auto printF=[](auto r){
        for(auto x:r){
            cout<<x<<" \n";
        }
    };
    printF(res);
}
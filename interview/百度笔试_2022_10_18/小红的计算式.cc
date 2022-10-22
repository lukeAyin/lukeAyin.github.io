#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
string func(string& str){
    int n=str.size();
    stack<int> stk;
    for(int i=2;i<n;i++){
        while(!stk.empty()&&str[i]>stk.top()){
            stk.pop();
        }
        stk.push(str[i]);
    }
    string res;
    while(!stk.empty()){
        res+=stk.top();
        stk.pop();
    }
    res+=".0";
    reverse(res.begin(),res.end());
    return res;
}
int main(){
    string str;
    cin>>str;
    cout<<func(str)<<endl;
}
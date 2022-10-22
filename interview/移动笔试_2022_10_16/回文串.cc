#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
ll getCost(string &str,vector<int>& w){
    int n=str.size();
    int l=0,r=n-1;
    ll res=0;
    while(l<r){
        if(str[l]!=str[r]){
            res+=(min(w[l],w[r]));
        }
        l++;
        r--;
    }
    return res;
}
int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    vector<int> w(n);
    for(int i=0;i<n;i++){
        cin>>w[i];
    }
    cout<<getCost(str,w)<<endl;
}
#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const ll mod=1e9+7;
ll getM(ll n,int k){
    ll res=1;
    for(ll i=k+1;i<=n;i++){
        res*=i;
        res%=mod;
    }
    return res;
}
int func(ll n,ll k){
    if(k==1){
        return (n*25)%mod;
    }
    ll t=1;
    for(int i=0;i<n;i++){
        t*=26;
        t%=mod;
    }
    // /sum_{i=1}^{k}C_n^i(25)
    return (t*getM(n,k))%mod;
}
int main(){
    ll n,k;
    cin>>n>>k;

    cout<<func(n,k)<<endl;
}
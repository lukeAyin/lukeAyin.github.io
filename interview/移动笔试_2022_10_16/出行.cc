#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
ll getMoney(ll m,ll a,ll b,ll c){
    if(m<=b){
        return a;
    }
    return a+(m-b)*c;
}
int main(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n),b(n),c(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    for(int i=0;i<n;i++){
        cin>>c[i];
    }
    ll res=LLONG_MAX;
    for(int i=0;i<n;i++){
        res=min(res,getMoney(m,a[i],b[i],c[i]));
    }
    cout<<res<<endl;
}
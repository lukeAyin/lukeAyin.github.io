#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const ll mod=1e9+7;
int func(vector<int>& nums,string& s){
    int n=nums.size();
    ll a=0;
    ll b=0;
    for(int i=0;i<n;i++){
        if(s[i]=='R'){
            a+=(nums[i]);
            a%=mod;
        }else{
            b+=nums[i];
            b%=mod;
        }
    }
    return a*b%mod;
}
int main(){
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    string colors;
    cin>>colors;
    cout<<func(nums,colors)<<endl;
}
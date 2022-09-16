#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
int n;
const int maxn=1e5+5;
vector<int> nums(maxn,0);
int A[maxn];
int B[maxn];
int getS(int A[],int B[]){
    for(int i=0;i<n;i++){
        nums[i]=B[i]-A[i];
    }
    sort(nums.begin(),nums.begin()+n);
    int l=0,r=n-1;
    int res=0;
    while(l<r){
        if(nums[l]+nums[r]<0){
            l++;
        }else{
            r--;
            l++;
            res++;
        }
    }
    return res;
}
int main(){
    int t;
    // ifstream cin("data.txt");
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;++i){
            cin>>A[i];
        }
        for(int i=0;i<n;++i){
            cin>>B[i];
        }
        cout<<getS(A,B)<<endl;
    }
}
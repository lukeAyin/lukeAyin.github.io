#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
void func(int x,int v,int t){
    int min_r=t;
    int max_r=0;
    t-=3;
    t-=(x*v);
    int a,b;
    // cout<<x<<" "<<t<<endl;
    if(x==1){
        a=2;
        b=3;
    }else if(x==2){
        a=1;
        b=3;
    }else{
        a=1;
        b=2;
    }

    for(int i=0;i*b<=t;i++){
        int z=t-(i*b);
        if((z%a)==0||z==0){
            int tmp=v+i+z/a;
            min_r=min(min_r,tmp);
            max_r=max(max_r,tmp);
            // cout<<min_r<<" "<<max_r<<" "<<i<<" "<<tmp<<endl; 
        }
    }
    cout<<max_r<<" "<<min_r;
}
int main(){
    char x;
    int v,t;
    cin>>x>>v>>t;
    func(x-'a'+1,v,t);
}
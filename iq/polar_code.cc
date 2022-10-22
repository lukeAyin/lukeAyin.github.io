#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
vector<vector<int>> F1={{1,0},{1,1}};
vector<int> getIdx(int len){
    vector<int> idx(len,0);
    for(int i=0;i<len;i++){
        idx[i]=idx[i>>1]>>1;
        if(i&1){
            idx[i]|=len>>1;
        }
    }
    for(auto x:idx){
        cout<<x<<" ";
    }
    cout<<endl;
    return idx;
}
void printM(vector<vector<int>>& res,vector<int> &idx){
    int m=res.size();
    int n=res[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<res[i][idx[j]]<<" ";
        }
        cout<<endl;
    }
}
void func(int n,vector<vector<int>>& res){
    int len=res.size();
    int x=2;
    while(x<len){
        int nx=2*x;
        for(int i=x;i<nx;i++){
            for(int j=x;j<nx;j++){
                res[i][j]=res[i-x][j-x];
            }
        }
        for(int i=x;i<nx;i++){
            for(int j=0;j<x;j++){
                res[i][j]=res[i-x][j];
            }
        }
        x=nx;
    }
}
int main(){
    int n;
    cin>>n;
    int len=pow(2,n);
    vector<vector<int>> let(len,vector<int>(len,0));
    let[0][0]=let[1][0]=let[1][1]=1;
    func(n,let);
    auto idx=getIdx(len);
    printM(let,idx);
}
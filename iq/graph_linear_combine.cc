#include<bits/stdc++.h>
using namespace std;
int M,N;
void func(vector<vector<int>> &a,vector<vector<int>> &b){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            int t=a[i][j]+(2*b[i][j])-255;
            t=min(t,255);
            t=max(t,0);
            cout<<t<<" ";
        }
        cout<<endl;
    }
}
int main(){
    cin>>M>>N;
    vector<vector<int>> a(M,vector<int>(N,0));
    vector<vector<int>> b(M,vector<int>(N,0));
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>a[i][j];
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>b[i][j];
        }
    }
    func(a,b);
}
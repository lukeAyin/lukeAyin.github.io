// #include<bits/stdc++.h>
#include<memory.h>
#include<map>
#include<iostream>
//#define int long long
using namespace std;
const int N=210,inf=0x3f3f3f3f;
int n,t,s,e,cnt,g[N][N],a[N][N];
map<int,int> mp;
void mul(int a[][N],int b[][N]){
    int p[N][N];
    memset(p,inf,sizeof(p));
    for(int i=1;i<=cnt;++i){
        for(int j=1;j<=cnt;++j){
            for(int k=1;k<=cnt;++k){
                if(p[i][j]>a[i][k]+b[k][j]){
                    p[i][j]=a[i][k]+b[k][j];
                }
            }
        }
    }
    for(int i=1;i<=cnt;++i){
        for(int j=1;j<=cnt;++j){
            a[i][j]=p[i][j];
        }
    }
}
void qmi(int b){
	for(int i=1;i<=cnt;i++)	for(int j=1;j<=cnt;j++)	a[i][j]=g[i][j];
	while(b){
		if(b&1)	mul(g,a); b>>=1; mul(a,a);
	}
}
int main(){
    // ifstream cin("data.txt");
	cin>>n>>t>>s>>e;	
    memset(g,inf,sizeof g);
	while(t--){
		int u,v,w;	cin>>w>>u>>v;
		if(!mp[u])	mp[u]=++cnt;
		if(!mp[v])	mp[v]=++cnt;
		g[mp[u]][mp[v]]=g[mp[v]][mp[u]]=min(g[mp[u]][mp[v]],w);
	}
	qmi(n-1);
	cout<<g[mp[s]][mp[e]]<<endl;
	return 0;
}

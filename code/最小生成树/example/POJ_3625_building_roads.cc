#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const int MAXN=1010;
int n,m;//n个节点，m条边
int vis[MAXN];//记录结点是否遍历过
double lowcost[MAXN];
double G[MAXN][MAXN];
struct point{
    int x,y;
}p[MAXN];
void init(){
    memset(vis,0,sizeof(vis));
    memset(G,inf,sizeof(G));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            double tmp_x=1.0*(p[i].x-p[j].x)*(p[i].x-p[j].x);
            double tmp_y=1.0*(p[i].y-p[j].y)*(p[i].y-p[j].y);
            G[i][j]=sqrt(tmp_x+tmp_y);
            G[j][i]=sqrt(tmp_x+tmp_y);
        }   
    }   
}
void prim(){
    int pos;
    double ans=0;
    for(int i=1;i<=n;i++){
        lowcost[i]=G[1][i];
    }   
    for(int i=1;i<=n;i++){
        pos=-1;
        for(int j=1;j<=n;++j){
            if(!vis[j]&&(pos==-1||lowcost[pos]>lowcost[j])){
                pos=j;
            }
        }
        if(pos==-1){
            break;
        }
        vis[pos]=1;
        ans+=lowcost[pos];
        for(int j=1;j<=n;j++){
            if(!vis[j]&&lowcost[j]>G[pos][j]){
                lowcost[j]=G[pos][j];
            }
        }
    }
    printf("%.2lf\n",ans);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        p[i].x=x;
        p[i].y=y;
    }
    init();
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        G[x][y]=G[y][x]=0;
    }
    prim();
}
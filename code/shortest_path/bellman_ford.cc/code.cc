#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
using namespace std;
const int N=1e4+10;
const int M=510;
int m,n,dis[M],backup[M];
//m条边，n个点，找到1号点到其他所有点之间的最短路
//dis：各点到源点的距离，backup：备份 
struct edge{
    int x,y,v;
}e[M];
void bellman_ford(){
    memset(dis,inf,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;++i){
        memcpy(backup,dis,sizeof dis);
        for(int j=0;j<m;++j){
            int u=e[j].x;
            int v=e[j].y;
            dis[v]=min(dis[v],backup[u]+e[j].v);
        }
    }
    for(int j=0;j<m;++j){
        int u=e[j].x;
        int v=e[j].y;
        if(dis[v]>(dis[u]+e[j].v)){
            printf("has negative circle\n");
        }
    }    
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i){
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        e[i].x=u;
        e[i].y=v;
        e[i].v=x;
    }
    bellman_ford();

}
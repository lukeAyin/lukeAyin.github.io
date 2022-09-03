#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
using namespace std;
const int N=1005;
const int M=105;
int n,k,s,t;//n个节点，k是边数，s是起始点，t是终点
int dis[N][N];
// struct edge{
//     int v,next,len;
// }e[M];
// int head[N];
// int tot;
// inline void add(int u,int v,int len){
//     e[tot].v=v;
//     e[tot].len=len;
//     e[tot].next=head[u];
//     head[u]=tot++;
// }
void floyd(){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j){
                dis[i][j]=0;
            }
        }
    }
    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}
void init(){
    memset(dis,inf,sizeof(dis));
}
int main(){
    FILE *fp=fopen("data.txt","r");
    fscanf(fp,"%d%d%d%d",&n,&k,&s,&t);
    init();
    for(int i=0;i<t;++i){
        int len,u,v;
        fscanf(fp,"%d%d%d",&len,&u,&v);
        dis[u][v]=len;
        dis[v][u]=len;
    }
    floyd();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            printf("%d ",dis[i][j]);
        }
        printf("\n");
    }
}
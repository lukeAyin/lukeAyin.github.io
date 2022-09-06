// #include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const int N=505;
const int M=250050;
int n,m;
struct edge{
    int v,next,len;
}e[M];
int tot;
int head[N];
inline void add(int u,int v,int len){
    e[tot].v=v;
    e[tot].len=len;
    e[tot].next=head[u];
    head[u]=tot++;
}
int idx[N];
int DFN[N];
int LOW[N];
int dcnt;
int bcnt;//强连通图的个数
int ins[N];//记录点是否在栈里
stack<int> stk;
void tarjan(int u){
    DFN[u]=LOW[u]=++dcnt;
    stk.push(u);
    ins[u]=1;
    for(int k=head[u];k!=-1;k=e[k].next){//遍历与u有关的边
        int v=e[k].v;
        if(!DFN[v]){
            tarjan(v);
            LOW[u]=min(LOW[u],LOW[v]);
        }else if(ins[v]){
            LOW[u]=min(LOW[u],DFN[v]);
        }
    }
    if(DFN[u]==LOW[u]){
        bcnt++;
        while(1){
            int x=stk.top();
            ins[stk.top()]=0;
            idx[stk.top()]=bcnt;
            stk.pop();
            if(x==u){
                break;
            }
        }
    }
}
void Tarjan(){
    memset(DFN,0,sizeof(DFN));
    memset(LOW,0,sizeof(LOW));
    memset(ins,0,sizeof(ins));
    memset(idx,0,sizeof(idx));
    bcnt=0;
    dcnt=0;
    for(int i=1;i<=n;i++){
        if(!DFN[i]){
            tarjan(i);
        }
    }   
}

edge ee[M];
int etot;
int ehead[N];
inline void eadd(int u,int v,int len){
    ee[etot].v=v;
    ee[etot].len=len;
    ee[etot].next=ehead[u];
    ehead[u]=etot++;
}

void trans(){
    memset(ehead,-1,sizeof(ehead));
    etot=1;
    for(int i=1;i<=n;i++){
        for(int k=head[i];k!=-1;k=e[k].next){
            int j=e[k].v;
            if(idx[i]!=idx[j]){
                eadd(idx[i],idx[j],e[k].len);
            }
        }
    }   
}

int dijkstra(int s,int t)
{
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push(make_pair(0,s));
    int vis[N];
    int dis[N];
    memset(dis,inf,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    while(!pq.empty()){
        int u=pq.top().second;
        int len=pq.top().first;
        pq.pop();
        if(u==t){
            return len;
        }
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int k=ehead[u];k!=-1;k=ee[k].next){
            int v=ee[k].v;
            int len=ee[k].len;
            if(!vis[v]&&dis[v]>(dis[u]+len)){
                dis[v]=dis[u]+len;
                pq.push(make_pair(dis[v],v));
            }
        }
    }
    return -1;
}

// void floyd(){
//     for(int k=1;k<=bcnt;k++){
//         for(int i=1;i<=bcnt;i++){
//             for(int j=1;j<=bcnt;j++){
//                 dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
//             }
//         }   
//     }
// }


void init(){
    tot=1;
    memset(head,-1,sizeof(head));
}
int main(){
    // FILE *fp=fopen("data.txt","r");
    while(scanf("%d%d",&n,&m)){
        if(n==0&&m==0){
            return 0;
        }
        init();
        for(int i=1;i<=m;i++){
            int x,y,h;
            scanf("%d%d%d",&x,&y,&h);
            add(x,y,h);
        }

        Tarjan();
        trans();
        int k;
        scanf("%d",&k);
        for(int i=1;i<=k;i++){
            int s,t;
            scanf("%d%d",&s,&t);
            int len=dijkstra(idx[s],idx[t]);
            if(len==-1){
                printf("Nao e possivel entregar a carta\n");
            }else{
                printf("%d\n",len);
            }
            // if(dis[idx[s]][idx[t]]!=inf){
            //     printf("%d\n",dis[idx[s]][idx[t]]);
            // }else{
            //     printf("Nao e possivel entregar a carta\n");
            // }
        }
    }
}

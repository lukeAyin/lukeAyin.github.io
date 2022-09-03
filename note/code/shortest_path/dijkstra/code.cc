#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
using namespace std;
#define inf 0x3f3f3f3f
using namespace std;
const int M=1e4+10;
const int N=510;
int m,n;
//m条边，n个点，找到1号点到其他所有点之间的最短路
//dis：各点到源点的距离，backup：备份 
int head[N];
struct edge{
    int v,next,val;
}e[N];
int tot;
int dis[N];
int vis[N];
inline void add(int u,int v,int val){//u->v,val为权重
    e[tot].v=v;
    e[tot].next=head[u];
    e[tot].val=val;
    head[u]=tot++;
}
void init(){
    memset(dis,inf,sizeof(dis));
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}
typedef pair<int,int> pii;
void dijkstra(int st){
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dis[st]=0;
    pq.push(make_pair(0,st));
    while(!pq.empty()){
        int val=pq.top().first;
        int u=pq.top().second;
        pq.pop();
        if(vis[u]){//访问过就跳过
            continue;
        }
        vis[u]=1;
        for(auto k=head[u];k!=-1;k=e[k].next){//邻接表遍历u的下一节点
            int v=e[k].v;
            int w=e[k].val;
            if(dis[v]>(val+w)){
                dis[v]=val+w;
                pq.push(make_pair(dis[v],v));
            }
        }
    }
    for(int i=1;i<=n;++i){
        printf("%d ",dis[i]);
    }
    printf("\n");
}
int main(){
    FILE *fp=fopen("data.txt","r");
    int t;
    fscanf(fp,"%d",&t);
    while(t--){
        init();
        fscanf(fp,"%d%d",&n,&m);
        for(int i=0;i<m;++i){
            int u,v,val;
            fscanf(fp,"%d%d%d",&u,&v,&val);
            add(u,v,val);
        }
        dijkstra(1);
    }
}
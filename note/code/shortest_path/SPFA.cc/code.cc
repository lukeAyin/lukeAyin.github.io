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
int inQ[N];
int lnt[N];//判断负环，记录下从源点到i点经过了几个点，当超过n个点时，根据抽屉定理可知，一定有负环
void init(){
    memset(head,-1,sizeof(head));
    memset(dis,inf,sizeof(dis));
    memset(inQ,0,sizeof(inQ));
    memset(lnt,0,sizeof(lnt));
    tot=0;

}
inline void add(int u,int v,int val){//u->v,val为权重
    e[tot].v=v;
    e[tot].next=head[u];
    e[tot].val=val;
    head[u]=tot++;
}
void spfa(int s){//s为源顶点
    memset(dis,inf,sizeof(dis));
    dis[1]=0;
    queue<int> q;
    q.push(s);
    inQ[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inQ[u]=false;
        for(int k=head[u];k!=-1;k=e[k].next){
            int v=e[k].v;
            int val=e[k].val;
            if(dis[v]>dis[u]+val){
                dis[v]=dis[u]+val;
                lnt[v]=lnt[u]+1;
                if(lnt[v]>n){
                    printf("has negative circle! break!\n");
                    return;
                }
                if(!inQ[v]){
                    inQ[v]=true;
                    q.push(v);//队列插入规则可以优化
                }
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
        fscanf(fp,"%d%d",&n,&m);
        init();
        for(int i=0;i<m;++i){
            int u,v,val;
            fscanf(fp,"%d%d%d",&u,&v,&val);
            add(u,v,val);
        }
        spfa(1);
    }

}

// int main(){
//     scanf("%d%d",&n,&m);
//     for(int i=0;i<m;++i){
//         int u,v,val;
//         scanf("%d%d%d",&u,&v,&val);
//         add(u,v,val);
//     }
//     spfa();
//     for(int i=1;i<=n;++i){
//         printf("%d ",dis[i]);
//     }
// }
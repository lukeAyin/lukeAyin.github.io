#include<bits/stdc++.h>
using namespace std;
#define pb puch_back
#define eb emplace_back

const int M=5005;

vector<int> ver[M];
int vis[M];
int p[M];
int n,m,k,len;

const int N=5005;
int DFN[N];
int LOW[N];
int gccsb_index=0;

struct edge{
    int v;
    int next;
}e[10005];

int tot,head[N];

inline void add(int u,int v){
    e[tot].v=v;
    e[tot].next=head[u];
    head[u]=tot++;
}

stack<int> stk;
bool InStack[N];                
int idx[N];
void tarjan(int cur){
    DFN[cur]=LOW[cur]=(++gccsb_index);
    stk.push(cur);
    InStack[cur]=true;
    for(int i=head[cur];i!=-1;i=e[i].next){
        int u=cur;
        int v=e[i].v;
            if(DFN[v]==-1){
                tarjan(v);
                LOW[u]=min(LOW[u],LOW[v]);
            }else if(InStack[i]){
                LOW[u]=min(LOW[u],DFN[v]);
            }

    }
    if(DFN[cur]==LOW[cur]){
        int j=-1;
        while(cur!=j){
            j=stk.top();
            stk.pop();
            InStack[j]=false;
            idx[j]=len;
        }
        len++;
    }
}
void Tarjan(){
    for(int i=0;i<n;++i){
        if(DFN[i]==-1){
            tarjan(i);
        }
    }
}

void init(){
    memset(vis,0,sizeof(vis));
    memset(p,-1,sizeof(p));
    memset(DFN,-1,sizeof(DFN));
    memset(LOW,-1,sizeof(LOW));
    gccsb_index=0;
    // memset(nGraph,0,sizeof(nGraph));
    memset(InStack,false,sizeof(InStack));
    memset(idx,-1,sizeof(idx));
    memset(head,-1,sizeof(head));
    tot=0;
    len=0;
}
bool match(int i){
    for(int x=0;x<ver[i].size();++x){
        int j=ver[i][x];
        if(!vis[j]){
            vis[j]=1;
            if(p[j]==-1||match(p[j])){
                p[j]=i;
                return true;
            }
        }
    }
    return false;
}

int Hungarian(){
    int cnt=0;
    for(int i=0;i<len;++i){
        memset(vis,0,sizeof(vis));
        if(match(i)){
            cnt++;
        }
    }
    return cnt;
}

int main(){
    scanf("%d",&k);
    while(k--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            u--;
            v--;
            add(u,v);
        }
        Tarjan(); 
        for(int i=0;i<len;++i){
            ver[i].clear();
        }   
        for(int i=0;i<n;++i){
            for(int k=head[i];k!=-1;k=e[k].next){
                int u=idx[i];
                int v=idx[e[k].v];
                if(u==v){
                    continue;
                }
                // nGraph[u][v]=1;
                ver[u].emplace_back(v);
            }
        }
        printf("%d\n",len-Hungarian());
    }
}
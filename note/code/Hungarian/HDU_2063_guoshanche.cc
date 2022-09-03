#include<bits/stdc++.h>
using namespace std;
const int M=505;
int graph[M][M];
int vis[M];
int p[M];
int n,m,k;
void init(){
    memset(graph,0,sizeof(graph));
    memset(vis,0,sizeof(vis));
    memset(p,-1,sizeof(p));   
}
bool match(int i){
    for(int j=0;j<m;++j){
        if(graph[i][j]!=0&&!vis[j]){
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
    for(int i=0;i<n;++i){
        memset(vis,0,sizeof(vis));
        if(match(i)){
            cnt++;
        }
    }
    return cnt;
}
int main(){
        while(1){
        init();
        scanf("%d",&k);
        if(k==0){
            return 0;
        }
        scanf("%d %d",&n,&m);
        int u,v;
        for(int i=0;i<k;++i){
            scanf("%d %d",&u,&v);
            graph[u-1][v-1]=1;
        }
        printf("%d\n",Hungarian());
    }
}
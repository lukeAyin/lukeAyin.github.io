#include<iostream>
#include<cstdio>
#include<cstring>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 1005;
int graph[N][N];
bool vis[N];
int linker[N],n;
bool dfs(int u){
    for(int i=0;i<n;i++){
        if(graph[u][i]&&!vis[i]){
            vis[i] = true;
            if(linker[i]==-1||dfs(linker[i])){
                linker[i] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                graph[i][j] = 0;
        }
        for(int i=0;i<n;i++){
            int u,v,num;
            scanf("%d: (%d)",&u,&num);
            for(int j=0;j<num;j++){
                scanf("%d",&v);
                graph[u][v] = 1;
            }
        }
        int ans = 0;
        memset(linker,-1,sizeof(linker));
        for(int i=0;i<n;i++){
            memset(vis,false,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans/2);
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int M=505;
int graph[M][M];
int vis[M];
int p[M];
int n,m,k;
bool match(int i){
    for(int j=0;j<m;++j){
        if(graph[i][j]&&!vis[j])){
            vis[j]=1;
            if(p[j]==-1||match(p[j])){
                p[j]=-1;
                return true;
            }
        }
        return false;
    }
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


int sove()

int main(){
    scanf("%d",k);
    while(k--){
        scanf("%d %d",&n,&m);
    }
}
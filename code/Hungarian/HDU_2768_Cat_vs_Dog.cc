#include<bits/stdc++.h>
using namespace std;
const int M=505;
int graph[M][M];
int vis[M];
int p[M];
int n,m,k;
char a[M][10];
char b[M][10];
bool match(int i){
    for(int j=0;j<m;++j){
        if(graph[i][j]&&!vis[j]){
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

void init(){
    memset(graph,0,sizeof(graph));
    memset(vis,0,sizeof(vis));
    memset(p,-1,sizeof(p));
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));   
}

int main(){
    scanf("%d",&k);
    while(k--){
        int c,d,v;
        scanf("%d%d%d",&c,&d,&v);
        n=v;
        m=v;
        // cout<<n<<" "<<m<<" "<<v<<endl;
        init();
        for(int i=0;i<v;++i){
            scanf("%s%s",a[i],b[i]);
        }
        for(int i=0;i<v;++i){
            for(int j=i;j<v;++j){
                if(strcmp(a[i],b[j])==0||strcmp(a[j],b[i])==0){
                    graph[i][j]=graph[j][i]=1;
                }
            }
        }
        printf("%d\n",v-(Hungarian()/2));
    }
    return 0;
}
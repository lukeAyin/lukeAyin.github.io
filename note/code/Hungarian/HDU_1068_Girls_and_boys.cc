#include<iostream>
#include<cstdio>
#include<cstring>
#include <algorithm>
#include <math.h>
using namespace std;
const int M=1005;
int graph[M][M];
int visited[M];
int p[M];
int N;
bool match(int i){
    for(int j=0;j<N;++j){
        if(graph[i][j]&&visited[j]==0){
            visited[j]=1;
            if(p[j]==0||match(p[j])){
                p[j]=i;
                return true;
            }
        }
    }
    return false;
}

int Hungarian(){
    int cnt=0;
    for (int i=0;i<N;++i){
        memset(visited,0,sizeof(visited));
        if(match(i)){
            cnt++;
        }
    }
    return cnt;
}
void init(){
    memset(graph,0,sizeof(graph));
    memset(visited,0,sizeof(visited));
    memset(p,0,sizeof(p));
}
int main(){
    // ifstream cin("data.txt");
    while(scanf("%d",&N)!=EOF){
        init();
        for(int i=0;i<N;++i){
            int u,num;
            scanf("%d: (%d)",&u,&num);
            for(int j=0;j<num;++j){
                int t;
                scanf("%d",&t);
                graph[u][t]=1;
            }
        }
        int cnt=Hungarian();
        printf("out:%d\n",N-cnt/2);
        // ofstream out("output.txt",);
        // out<<(N-cnt)<<endl;
        // out.close()
    }
    return 0;
}
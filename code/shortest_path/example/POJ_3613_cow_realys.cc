#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
using namespace std;
const int N=1005;
const int M=105;
int n,t,s,e;
int dis[N];
struct edge{
    int v,next,len;
}e[M];
int tot;
inline add(int u,int v,int len){
    e[tot].v=v;
    e[tot].len=len;
    e[tot].next=head[u];
    head[u]=tot++;
}
void floyd(){
    
}

int main(){
    scanf("%d%d%d%d",&n,&t,&s,&e);
    for(int i=0;i<t;++i){
        int len,u,v;
        scanf("%d%d%d",&len,&u,&v);

    }
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 5010
#define M 100010
#define cl memset
#define pb push_back

int n,tot,head[N];
struct edge{
	int v,next;
}e[M];//idx代表边的序号，v代表边的下一个点，head[u]代表u的起始边，next代表下一条边
int dfn[N],low[N],belong[N],stack[N],ins[N],dcnt,bcnt,top;
vector<int>ver[N];
int mat[N],vis[N],ans;

inline void add(int u,int v){
	e[tot].v = v; e[tot].next = head[u]; head[u] = tot++;
}

void tarjan(int u){
	dfn[u] = low[u] = ++dcnt;
	stack[++top] = u; ins[u] = 1;
	for(int k = head[u]; k != -1; k = e[k].next){//遍历以u为起点的边
		int v = e[k].v;
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if(ins[v])
			low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u]){
		++bcnt;
		while(true){
			int x = stack[top--];
			ins[x] = 0;
			belong[x] = bcnt;
			if(x == u) break;
		}
	}
}

void scc(){
	dcnt = bcnt = top = 0;
	cl(dfn,0,sizeof(dfn));
	cl(ins,0,sizeof(ins));
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			tarjan(i);
}
void rebuild(){
	for(int i = 1; i <= bcnt; i++) 
		ver[i].clear();
	for(int i = 1; i <= n; i++)
		for(int j = head[i]; j != -1; j = e[j].next){
			int u = belong[i];
			int v = belong[e[j].v];
			if(u == v) continue;
			ver[u].pb(v);
		}
}
int dfs(int u){
	for(int i = 0; i < ver[u].size(); i++){
		int v = ver[u][i];
		if(!vis[v]){
			vis[v] = 1;
			if(mat[v] == -1 || dfs(mat[v])){
				mat[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
void MaxMatch(){
	ans = 0;
	cl(mat,-1,sizeof(mat));
	for(int u = 1; u <= bcnt; u++){
		cl(vis,0,sizeof(vis));
		ans += dfs(u);
	}
}

int main(){
	int m,cas;
	scanf("%d",&cas);
	while(cas--){
		tot = 0;
		cl(head,-1,sizeof(head));
		scanf("%d%d",&n,&m);
		while(m--){
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v);
		}
		scc();
		rebuild();
		MaxMatch();
		printf("%d\n",bcnt - ans);
	}
	return 0;
}
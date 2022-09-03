#include<iostream>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1e4+10;
const int M=510;
int m,n,k,dis[M],backup[M];
//m条边，n个点，在1号点到n号点之间找到一条经过小于等于k条边的通路
//dis：各点到源点的距离，backup：备份 
struct Node
{
	int x,y,v;
}edge[N];//可以直接用结构体存边 
int Bellman_Ford()
{
  dis[1]=0;
	memset(dis,0x3f,sizeof dis);
	for(int i=1;i<=k;i++)
	{
		memcpy(backup,dis,sizeof dis);
		for(int j=1;j<=m;j++)
		{
			Node t=edge[j];
			dis[t.y]=min(dis[t.y],backup[t.x]+t.v);
		}
	}
	if(dis[n]>inf/2)	return -1; 
	return dis[n];
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		edge[i]={a,b,c};
	}
	int ans=Bellman_Ford();
	if(ans==-1)		cout<<"impossible";
	else			cout<<ans;
	return 0;
}
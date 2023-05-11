#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
const int MAXM=300;
int m,n;
int board[MAXM][MAXM];
int dis[MAXM][MAXM];
vector<pii> warehouse;
int step[4][2]={-1,0,0,-1,1,0,0,1};//上，左，下，右

inline bool IsBoard(int i,int j){
    return i>=0&&i<m&&j>=0&&j<n;
}

void CountDis(int x,int y){//从x,y出发，广搜
    queue<pii> q;
    set<pii> visited;
    q.push(make_pair(x,y));
    int d=0;
    while(!q.empty()){
        int len=q.size();
        while(len--){
            int i=q.front().first;
            int j=q.front().second;
            if(board[i][j]==1){
                dis[i][j]=min(dis[i][j],d);
            }
            q.pop();
            for(int k=0;k<4;k++){
                int ni=i+step[k][0];
                int nj=j+step[k][1];
                if(IsBoard(ni,nj)&&!visited.count(make_pair(ni,nj))&&board[ni][nj]!=-1){
                    visited.insert(make_pair(ni,nj));
                    q.push(make_pair(ni,nj));
                }
            }
        }
        d++;
    }
}
int GetMinDistance(){
    memset(dis,inf,sizeof(dis));
    for(auto [i,j]:warehouse){
        CountDis(i,j);
    }
    int res=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(dis[i][j]!=inf){
                res+=dis[i][j];
            }
        }
    }
    return res;
}
int main(){
    fstream input("1.min_retail.txt");
    input>>m>>n;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            input>>board[i][j];
            if(board[i][j]==0){
                warehouse.emplace_back(i,j);
            }
        }
    }
    printf("%d",GetMinDistance());
}
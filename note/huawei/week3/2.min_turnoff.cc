#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
const int MAXL=50;//最大边长
int timeLimit,L;//限制时间,实际边长
int board[MAXL][MAXL];
int x,y;//小狮工位
int nx,ny;//办公室出口
int step[4][2]={-1,0,0,-1,1,0,0,1};//下，左，上，右
unordered_map<int,int> id_map;//给灯泡标号，方便判断是否已经访问这个灯
//灯的下标可以使用int来存，用位运算来判断是否有这个灯

inline bool InBoard(int i,int j){
    return i>=0&&i<L&&j>=0&&j<L;
}

inline int CountNum(int x){//根据灯泡状态得到关灯数量
    int res=0;
    while(x){
        x&=(x-1);
        res++;
    }
    return res;
}

int GetMaxLight(){
    queue<pii> q;//bfs存状态
    q.push(make_pair(x*L+y,0));
    set<pii> visited;//存储下标+灯泡状态作为搜索剪枝条件
    visited.insert(make_pair(x*L+y,0));
    int let=0;//记录步数
    int res=-1;
    while (!q.empty()&&let<timeLimit)//
    {
        int len=q.size();
        while(len--){
            int i=q.front().first/L;
            int j=q.front().first%L;
            int status=q.front().second;
            q.pop();
            for(int k=0;k<4;k++){
                int ni=i+step[k][0];
                int nj=j+step[k][1];
                int nstatus=status;
                if(!InBoard(ni,nj)||board[ni][nj]==1){//下标越界或不可通过
                    continue;
                }
                if(board[ni][nj]==2){//当前位置是灯泡
                    int nid=id_map[ni*L+nj];
                    nstatus|=(1<<nid);//记录灯泡状态
                }
                pii np=make_pair(ni*L+nj,nstatus);
                if(visited.count(np)){//当前状态已经访问过
                    continue;
                }
                if(ni==nx&&nj==ny){
                    res=max(res,CountNum(nstatus));//更新返回值
                }
                visited.insert(np);
                q.push(np);
            }
        }
        let++;
    }
    return res;
}


int main(){
    fstream input("2.min_turnoff.txt");
    input>>timeLimit>>L;
    int id=0;
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            input>>board[i][j];
            if(board[i][j]==3){
                x=i;
                y=j;
            }
            if(board[i][j]==4){
                nx=i;
                ny=j;
            }
            if(board[i][j]==2){
                id_map[i*L+j]=id++;
            }
        }
    }
    printf("%d",GetMaxLight());
}
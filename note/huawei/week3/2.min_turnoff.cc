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
map<int,int> path[MAXL][MAXL][2];//存储下标的已访问灯下标，走的步数
unordered_map<int,int> id_map;//给灯泡标号，方便判断是否已经访问这个灯
//灯的下标可以使用int来存，用位运算来判断是否有这个灯

inline bool CheckBoard(int i,int j){
    return i>=0&&i<L&&j>=0&&j<L;
}

int GetMaxLight(){
    queue<pii> q1,q2;
    q1.push(make_pair(x*L+y,0));
    set<pii> visited1;//存储下标+状态
    set<pii> visited2;//
    q2.push(make_pair(nx*L+ny,0));
    int let=0;//
    int res=0;
    while (!q1.empty()&&q2.empty())//有一个为空都代表两点无法连通
    {
        if(let>timeLimit){

        }
        int len=q1.size();
        while(len--){
            int i=q1.front().first/L;
            int j=q1.front().first%L;
            int status=q1.front().second;
            q1.pop();
            for(int k=0;k<4;k++){
                int ni=i+step[k][0];
                int nj=j+step[k][1];
                int nstatus=status;
                if(!CheckBoard(ni,nj)||board[ni][nj]==1){//下标越界或不可通过
                    continue;
                }
                if(board[ni][nj]==2){
                    int nid=id_map[ni*L+nj];
                    if(nstatus&(!(1<<nid))){//已经访问过这个灯
                        continue;
                    }else{
                        nstatus|=(1<<nid);
                    }
                }
                pii np=make_pair(ni*L+nj,nstatus);
                if(visited1.count(np)){
                    continue;
                }
                
                visited1.insert(np);
                q1.push(np);
            }
            len=q2.size();
            while(len--){
                int i=q2.front().first/L;
                int j=q2.front().second%L;
                int status =q2.front().second;
                q2.pop();
                for(int k=0;k<4;k++){
                    int ni=i+step[k][0];
                    int nj=j+step[k][1];
                    int nstatus=status;
                    if(!CheckBoard(ni,nj)||board[ni][nj]==1){
                        continue;
                    }
                    if(board[ni][nj]==2){
                        int nid=id_map[ni*L+nj];
                        if(nstatus&(1<<nid)){
                            continue;
                        }else{
                            nstatus|=(1<<nid);
                        }
                    }
                    pii np=make_pair(ni*L+nj,nstatus);
                    if(visited2.count(np)){
                        continue;
                    }
                    visited2.insert(np);
                    q2.push(np);
                }
            }
        }
        let++;
    }

    return -1;  
    
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
}
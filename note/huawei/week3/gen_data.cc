#include<bits/stdc++.h>
using namespace std;
int main(){
fstream output("2.min_turnoff.txt");
    output<<20000<<endl;
    output<<50<<endl;
    vector<vector<int>> board(50,vector<int>(50,0));
    uniform_int_distribution<unsigned> u(0,49);
    default_random_engine e;
    for(int i=0;i<100;i++){
        int x=u(e);
        int y=u(e);
        board[x][y]=1;
    }
    for(int i=0;i<11;i++)
    {
        int x=u(e);
        int y=u(e);
        board[x][y]=2;
    }
    board[u(e)][u(e)]=3;
    board[u(e)][u(e)]=4;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            output<<board[i][j]<<" ";
        }
        output<<endl;
    }
}
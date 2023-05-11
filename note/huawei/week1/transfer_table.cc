#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

inline bool IsDigit(char x){
    return x>='0'&&x<='9';
}

char board[105][105];
int getNumber(string& tmp,int& st){
    int let=0;
    while(st<tmp.size()){
        if(!IsDigit(tmp[st])){
            if(let!=0){
                return let;
            }
            st++;
            continue;
        }
        let*=10;
        let+=(tmp[st]-'0');
        st++;
    }
    return let;
}


void drawBoard(int maxL,int maxC){
    for(int i=0;i<maxL+2;i++){
        if(i==0||i==(maxL+1)){
            printf("+");
        }else{
            printf("|");
        }
        for(int j=1;j<=maxC;j++){
            if(i==0||i==(maxL+1)){
                printf("---+");
            }else{
                printf(" %c |",board[i][j]);
            }
        }
        printf("\r\n");
    }

}

int main(){
    memset(board,' ',sizeof(board));
    int m=0;
    int n=0;
    fstream input("data_transfer_table.txt");
    string tmp;
    int maxL=0;
    int maxC=0;
    while(getline(input,tmp)){ 
        int st=4;
        int x=getNumber(tmp,st);
        int y=getNumber(tmp,st);
        char last=tmp[tmp.size()-1];
        maxL=max(maxL,x);
        maxC=max(maxC,y);
        if(last>='A'&&last<='Z'){
            board[x][y]=last;
        }
    }
    drawBoard(maxL,maxC);
}
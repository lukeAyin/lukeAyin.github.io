#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
class Solution {
public:
using pis=pair<int,string>;
    inline bool isBoard(int nx, int ny){
        return nx>=0&&ny>=0&&nx<=5&&ny<5&&nx*5+ny<26;
    }
    string alphabetBoardPath(string target) {
        vector<string> board={"abcde","fghij","klmno","pqrst","uvwxy","z"};
        vector<vector<string>> path(26,vector<string>(26,""));
        int step[4][2]={-1,0,0,-1,1,0,0,1};
        char opst[4]={'U','L','D','R'};
        auto bfs=[&](int idx){
            queue<pis> q;
            vector<int> visited(26,0);
            q.push(make_pair(idx,""));
            visited[idx]=1;
            while (!q.empty())
            {
                int id=q.front().first;
                string prev_path=q.front().second;
                path[idx][id]=prev_path;
                q.pop();
                for(int i=0;i<4;i++){
                    int x=id/5;
                    int y=id%5;
                    int nx=x+step[i][0];
                    int ny=y+step[i][1];
                    if(isBoard(nx,ny)&&!visited[nx*5+ny]){
                        q.push(make_pair(nx*5+ny,prev_path+opst[i]));
                        visited[nx*5+ny]=1;
                    }
                }
            }
        };
        for(int i=0;i<26;i++){
            bfs(i);
        }
        int n=target.size();
        int prev_loc=0;
        string res;
        for(int i=0;i<n;i++){
            int next_loc=target[i]-'a';
            res+=path[prev_loc][next_loc];
            res+="!";
            prev_loc=next_loc;
        }
        return res;
    }
};
int main(){
    string target="leet";
    Solution s;
    cout<<s.alphabetBoardPath(target);
}
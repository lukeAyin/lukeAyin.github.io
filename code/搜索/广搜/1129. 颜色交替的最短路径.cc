#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
class Solution {
public:


    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<int> redRes(n,inf),blueRes(n,inf);
        vector<vector<int>> redPath(n,vector<int>()),bluePath(n,vector<int>());
        for(auto &e:redEdges){
            redPath[e[0]].emplace_back(e[1]);
        }
        for(auto &e:blueEdges){
            bluePath[e[0]].emplace_back(e[1]);
        }
        queue<pii> q;
        function<void(int,int,int)> bfs=[&](int id,int dis,int flag){
            if(flag){
                for(auto des:redPath[id]){
                    if(redRes[des]>dis+1){
                        redRes[des]=dis+1;
                        q.push(make_pair(des,1-flag));
                    }
                }
            }else{
                for(auto des:bluePath[id]){
                    if(blueRes[des]>dis+1){
                        blueRes[des]=dis+1;
                        q.push(make_pair(des,1-flag));
                    }
                }
            }
        };
        q.push(make_pair(0,0));
        redRes[0]=blueRes[0]=0;
        q.push(make_pair(0,1));
        while(!q.empty()){
            int id=q.front().first;
            int flag=q.front().second;
            q.pop();
            if(flag){
                bfs(id,blueRes[id],flag);
            }else{
                bfs(id,redRes[id],flag);
            }
        }
        vector<int> res(n,0);
        for(int i=0;i<n;i++){
            res[i]=min(redRes[i],blueRes[i]);
            if(res[i]==inf){
                res[i]=-1;
            }
        }
        return res;
    }
};
int main(){
    
}
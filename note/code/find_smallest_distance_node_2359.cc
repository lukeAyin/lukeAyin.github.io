#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n=edges.size();
        int time[n];
        memset(time,0,sizeof(time));
        auto calc_dis=[&](int x)->vector<int>{
            vector<int> dis(n,n);
            for(int d=0;x>=0&&dis[x]==n;x=edges[x]){
                dis[x]=d++;
            }
            return dis;
        };
        auto d1=calc_dis(node1);
        auto d2=calc_dis(node2);
        int res=-1;
        int min_dis=n;
        for(int i=0;i<n;++i){
            int d=max(d1[i],d2[i]);
            if(min_dis>d){
                min_dis=d;
                res=i;
            }
        }
        return res;
    }
};
int main(){
    
}

//https://leetcode.cn/problems/find-closest-node-to-given-two-nodes/
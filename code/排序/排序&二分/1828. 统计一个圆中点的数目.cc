#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
//排序+二分缩小搜索范围，然后模拟计算...............
class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        int n=queries.size();
        vector<int> res(n,0);
        vector<pii> vp;
        for(auto &p:points){
            vp.emplace_back(make_pair(p[0],p[1]));
        }
        sort(vp.begin(),vp.end());
        auto dis=[](int x,int y,int r,int i,int j){
            return pow((x-i),2)+pow((y-j),2)<=r*r;
        };
        for(int i=0;i<n;i++){
            int x=queries[i][0];
            int y=queries[i][1];
            int r=queries[i][2];
            auto l_p=lower_bound(vp.begin(),vp.end(),make_pair(x-r,y-r));
            auto r_p=upper_bound(vp.begin(),vp.end(),make_pair(x+r,y+r));//二分确定范围
            int count=0;
            for(auto it=l_p;it!=r_p;it++){
                if(dis(x,y,r,it->first,it->second)){
                    count++;
                }
            }
            res[i]=count;
        }
        return res;
    }
};

int main(){
    
}
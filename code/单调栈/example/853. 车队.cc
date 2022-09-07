#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        map<int,double> mp;
        int n=position.size();
        for(int i=0;i<n;i++){
            mp[position[i]]=(1.0*(target-position[i]))/speed[i];
        }
        stack<double> stk;
        int cnt=0;
        for(auto it=mp.rbegin();it!=mp.rend();++it){
            int pos=it->first;
            // cout<<pos<<" "<<it->second<<endl;
            if(!stk.empty()&&stk.top()>=mp[pos]){
                continue;
            }
            stk.push(mp[pos]);
        }
        return stk.size();
    }
};
int main(){
    
}
/*
在一条单行道上，有 n 辆车开往同一目的地。目的地是几英里以外的 target 。

给定两个整数数组 position 和 speed ，长度都是 n ，其中 position[i] 是第 i 辆车的位置， speed[i] 是第 i 辆车的速度(单位是英里/小时)。

一辆车永远不会超过前面的另一辆车，但它可以追上去，并与前车 以相同的速度 紧接着行驶。此时，我们会忽略这两辆车之间的距离，也就是说，它们被假定处于相同的位置。

车队 是一些由行驶在相同位置、具有相同速度的车组成的非空集合。注意，一辆车也可以是一个车队。

即便一辆车在目的地才赶上了一个车队，它们仍然会被视作是同一个车队。

返回到达目的地的 车队数量 。
n == position.length == speed.length
1 <= n <= 105
0 < target <= 106
0 <= position[i] < target
position 中每个值都 不同
0 < speed[i] <= 106

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/car-fleet
*/
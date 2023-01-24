#include "bits/stdc++.h"
using namespace std;
#define inf=0x3f3f3f3f;
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n=obstacles.size();
        vector<int> dp(3,0);
        dp[2]=dp[0]=inf;

        int idx=0;
        for(int i=0;i<obstacles.size();i++){
            if(obstacles[i]>0){
            dp[obstacles[i]-1]=inf;
          }
            for(int j=0;j<3;j++){
                if(dp[j]<dp[idx]){
                  idx=j;
                }
                // cout<<dp[j]<<" ";
            }
          for(int j=1;j<=3;j++){
            dp[j-1]=min(dp[j-1],dp[idx]+1);
          }
          if(obstacles[i]>0){
            dp[obstacles[i]-1]=inf;
          }
        //   cout<<endl;

        }
        return dp[idx];
    }
};
int main (int argc, char *argv[])
{

  return 0;
}
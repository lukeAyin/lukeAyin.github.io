#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

int GetMinStep(vector<vector<int>>& planks){
    int m=planks.size();
    int n=planks[0].size();
    vector<vector<int>> left(m,vector<int>(n,0));//存储下标i到左边第一个为1的距离。
    vector<vector<int>> right(m,vector<int>(n,0));//同上,可优化?直接比较大小后存到left矩阵中
    for(int i=0;i<m;i++){
        int step=n;
        for(int j=0;j<n;j++){
            if(planks[i][j]){
                left[i][j]=0;
                step=0;
            }else{
                left[i][j]=step;
            }
            step++;
        }
        step=n;
        for(int j=n-1;j>=0;j--){
            if(planks[i][j]){
                right[i][j]=0;
                step=0;
            }else{
                right[i][j]=step;
            }
            step++;
        }
    }
    int res=INT_MAX;
    for(int j=0;j<n;j++){
        int tmp=0;
        for(int i=0;i<m;i++){
            tmp+=min(left[i][j],right[i][j]);
        }
        res=min(res,tmp);
    }
    return res;
}

int main(){
    fstream input("data3.txt");
    string str_planks;
    vector<vector<int>> planks;
    getline(input,str_planks);
    int st=str_planks.find('[');
    st++;
    int i=0;
    while(st<str_planks.size()){
        planks.emplace_back(vector<int>());
        while(str_planks[st]!=']'){
            if(str_planks[st]=='0'||str_planks[st]=='1'){
                planks[i].emplace_back(str_planks[st]-'0');
            }
            st++;
        }
        st=str_planks.find('[',st);
        i++;
    }    
    printf("%d",GetMinStep(planks));
}
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
class Solution {
public:
    const static int LIM=512;
    int parents[LIM*2];
    int find(int x){
        if(parents[x]==x)
            return x;
        return parents[x]=find(parents[x]);
    }
    bool union_set(int x,int y){
        int fx=find(x);
        int fy=find(y);
        if(fx==fy){
            return false;
        }
        parents[fx]=fy;
        return true;
    }
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int M=matrix.size();
        int N=matrix[0].size();
        vector<vector<int>> res(M,vector<int>(N,0));
        int countM[M],countN[N];
        memset(countM,0,sizeof(countM));
        memset(countN,0,sizeof(countN));

        map<int,vector<int>> ls,pool;
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                ls[matrix[i][j]].emplace_back(i*LIM+j);
            }
        }
        //init union_set
        for(int i=0;i<LIM*2;i++){
            parents[i]=i;
        }
        //traverse in ascending order;
        for(auto [val,_]:ls){
            //merge elements in the same column or row;
            for(int pt:ls[val]){
                union_set(pt/LIM,pt%LIM+LIM);
            }
            pool.clear();
            for(int pt:ls[val]){
                pool[find(pt/LIM)].push_back(pt);
            }
            //share the same rank if value is equal in the same column or row;
            for(auto group:pool){
                int rank=0;
                for(int pt:group.second){
                    rank=max(rank,max(countM[pt/LIM],countN[pt%LIM]));
                }
                rank++;
                for(int pt:group.second){
                    int m=pt/LIM;
                    int n=pt%LIM;
                    countM[m]=countN[n]=res[m][n]=rank;
                    //reset union_set
                    parents[m]=m;
                    parents[n+LIM]=n+LIM;
                }
            }
        }
        return res;
    }
};
int main(){
    
}
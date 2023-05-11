#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue
class Solution {
public:
    int m,n;
    inline int GetDis(int x,int y){
        return abs(y/n-x/n)+abs(y%n-x%n);
    }
    int extractMantra(vector<string>& matrix, string mantra) {
        m=matrix.size();
        n=matrix[0].size();
        int Len=mantra.size();
        vector<vector<int>> ID_Matrix(26,vector<int>());
        vector<vector<int>> Dis(26,vector<int>());
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                ID_Matrix[matrix[i][j]-'a'].emplace_back(i*n+j);
                Dis[matrix[i][j]-'a'].emplace_bakc(i+j);
            }
        }
        for(int i=1;i<Len;i++){ 
            int y=mantra[i]-'a';
            int x=mantra[i-1]-'a';
            if(x==y) continue;
            if(ID_Matrix[x].size()==0||ID_Matrix[y].size()==0){
                return -1;
            }
            for(int jj=0;jj<ID_Matrix[y].size();jj++){
                Dis[y][jj]=INT_MAX;
            }
            for(int ii=0;ii<ID_Matrix[x].size();ii++){
                for(int jj=0;jj<ID_Matrix[y].size();jj++){
                    Dis[y][jj]=min(Dis[y][jj],Dis[x][ii]+GetDis(ID_Matrix[x][ii],ID_Matrix[y][jj]));
                }
            }
        }
        int res=INT_MAX;
        for(auto dis:Dis[mantra[Len-1]-'a']){
            res=min(res,dis);
        }
        return res;
    }
};
int main(){
    
}
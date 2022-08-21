#include<bits/stdc++.h>
using namespace std;
int main(){
    
}
class Solution {
public:
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int>& energy, vector<int>& experience) {
        int n=energy.size();
        int res=0;
        int en=initialEnergy;
        int ex=initialExperience;
        for(int i=0;i<n;++i){
            if(en<=energy[i]){
                res+=(energy[i]-en+1);
                en=energy[i]+1;
            }
            if(ex<=experience[i]){
                res+=(experience[i]-ex+1);
                ex=experience[i]+1;
            }
            en=en-energy[i];
            ex=ex+experience[i];
        }
        return res;
    }
};
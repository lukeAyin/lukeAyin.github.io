#include<bits/stdc++.h>
using namespace std;
int main(){
    
}
class Solution {
public:
    string largestPalindromic(string num) {
        vector<int> count(10,0);
        for(auto ch:num){
            count[ch-'0']++;
        }
        int res=0;
        bool hasOdd=false;
        for(int i=1;i<10;++i){
            res+=func(count[i],hasOdd);
        }
        if(res>1){
            res+=func(count[0],hasOdd);
        }
        if(hasOdd){
            res++;
        }
        return res;
    }
    int func(int x,bool &hasOdd){
        int res=0;
        if(x%2==0){
            res+=x;
        }else{
            hasOdd=true;
            res+=(x-1)
        }
        return res;
    }
};
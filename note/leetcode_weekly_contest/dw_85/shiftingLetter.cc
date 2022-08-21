#include<iostream>
#include<cstring>
#include<vector>
#include<bits/stdc++.h>
using string=std::string;
#define vector std::vector
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
       int n=s.size();
       vector<int> let(n+1);
       for(auto& vec:shifts){
          int x=vec[2]?1:-1;
          let[vec[0]]+=x;
          let[vec[1]+1]-=x;
       }
       vector<int> sum(n+1,0);
       for(int i=1;i<=n;++i){
          sum[i]=(sum[i-1]+let[i-1]);
          //cout<<sum[i]<<" ";
          s[i-1]=circleChar(s[i-1],sum[i]);
       }
       return s;
    }
    char circleChar(char ch,int x){
      return ((ch-'a'+x)%26+26)%26+'a';
    }
};

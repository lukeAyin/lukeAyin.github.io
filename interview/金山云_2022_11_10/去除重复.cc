#include<bits/stdc++.h>
using namespace std;
char lowerCH(char ch){
    if(ch<='Z'&&ch>='A'){
        return ch+'a'-'A';
    }
    return ch;
}
bool isDup(string &a,string &b){
  if(a.size()!=b.size()){
    return false;
  }
  for(int i=0;i<a.size();i++){
    if(lowerCH(a[i])==lowerCH(b[i])){
        continue;
    }
    return false;
  }
  return true;
}
int main(){
  string input;
  getline(cin,input);
  istringstream iss(input);
  string ans;
  string res;
  string tmp;
  while(iss>>tmp){
    if(isDup(ans,tmp)){
      continue;
    }
    ans=tmp;
    res+=tmp;
    res+=" ";
  }
  res.pop_back();
  cout<<res;
}
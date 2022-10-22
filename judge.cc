#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;

bool isOk(string str){
    stack<char> stk;
    int n=str.size();
    map<char,int> id;
    id['(']=1;
    id['{']=2;
    id['[']=3;
    id[']']=4;
    id['}']=5;
    id[')']=6;
    for(int i=0;i<n;i++){
        if(id[str[i]]<=3){
            stk.push(str[i]);
        }else{
            if(stk.empty()){
                return false;
            }
            if((id[stk.top()]+id[str[i]])!=7){
                return false;
            }else{
                stk.pop();
            }
        }
    }
    return stk.empty();
}

int main(){
    bool flag=isOk("(){}[]");
    if(flag){
        cout<<"true\n";
    }else{
        cout<<"false\n";
    }
}
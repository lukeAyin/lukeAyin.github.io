#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

const int UNIT=6;//货轮中的集装箱个数

inline bool IsDigit(char x){
    return x>='0'&&x<='9';
}
int getNumber(string& tmp,int& st){
    int let=0;
    while(st<tmp.size()){
        if(!IsDigit(tmp[st])){
            if(let!=0){
                return let;
            }
            st++;
            continue;
        }
        let*=10;
        let+=(tmp[st]-'0');
        st++;
    }
    return let;
}

int CountShip(int num,vector<int>& times,int limit){
    int curUnit = 0;
    int res = 0;
    for(int i=0;i<times.size();i++){
        int curTime=times[i]-1;
        curUnit=max(curUnit,curTime*num);
        if(curUnit+UNIT<=(curTime+limit)*num){
            curUnit+=UNIT;
        }else{
            res++;
        }
    }
    return res;
}

int main(){
    fstream input("data_port_upload.txt");
    string str_num;
    getline(input,str_num);
    int num=stoi(str_num.substr(str_num.find('=')+1));
    string str_time;
    getline(input,str_time);
    vector<int> times;
    int st=str_time.find('[')+1;
    while(st<str_time.size()){
        int t=getNumber(str_time,st);
        if(t!=0){
            times.emplace_back(t);
        }
    }
    string str_limit;
    getline(input,str_limit);
    int id=0;
    int limit=getNumber(str_limit,id);
    printf("%d",CountShip(num,times,limit));
}
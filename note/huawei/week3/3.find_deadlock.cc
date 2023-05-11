#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const int MAXID=105;
const int MAXRES=305;
int num;
vector<vector<int>> occupied(MAXID,vector<int>());//进程占用的资源列表
vector<vector<int>> waited(MAXID,vector<int>());//进程等待的资源列表
map<int,int> res_map;//资源被占用的进程ID
vector<vector<int>> need(MAXRES,vector<int>());//需要该资源的进程ID列表
set<int> deadlock;
void GetByRes(set<int>& res_occupied){//从占用的资源来找到需要所有这些资源的进程ID
    for(auto it=res_occupied.begin();it!=res_occupied.end();it++){
        deadlock.insert(need[*it].begin(),need[*it].end());
    }
}
void GetDeadLockList(){
    queue<int> q;
    set<int> id_visited;//存储已经访问过的进程ID
    for(int i=0;i<MAXID;i++){
        if(id_visited.count(i)){
            continue;
        }
        set<int> res_occupied;//被占用的资源
        while (!q.empty())
        {
            int id=q.front();
            q.pop();
            for(auto k:occupied[id]){
                res_occupied.insert(k);
                if(id_visited.count(res_map[k])){
                    continue;
                }
                id_visited.insert(res_map[k]);
                q.push(res_map[k]);
            }
            for(auto k:waited[id]){
                if(res_occupied.count(k)){//说明有环
                    GetByRes(res_occupied);
                }
            }
        }
    }
    for(auto it=deadlock.begin();it!=deadlock.end();it++){
        printf("%d",*it);
    }
    
}
int main(){
    fstream input("3.find_deadlock.txt");
    string str;
    getline(input,str);
    num=stoi(str);
    for(int i=0;i<num;i++){
        str;
        getline(input,str);
        int st1=str.find('(')+1;
        int ed1=str.find(')');
        int st2=str.find('(',ed1)+1;
        int ed2=str.find(')',st2);
        // cout<<str.substr(0,st1-1)<<endl;
        int id=stoi(str.substr(0,st1-1));
        // cout<<str.substr(st1,ed1-st1)<<" "<<str.substr(st2,ed2-st2)<<endl;
        istringstream iss1(str.substr(st1,ed1-st1));
        string tmp;
        while (iss1>>tmp)
        {
            occupied[id].emplace_back(stoi(tmp));
            res_map[stoi(tmp)]=id;
        }
        istringstream iss2(str.substr(st2,ed2-st2));
        while (iss2>>tmp)
        {
            waited[id].emplace_back(stoi(tmp));
            need[stoi(tmp)].emplace_back(id);
        }    
    }
    GetDeadLockList();
}
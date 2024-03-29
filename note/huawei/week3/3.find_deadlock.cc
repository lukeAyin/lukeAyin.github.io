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
int id_visited[MAXID];//记录进程状态
void GetDeadLockList(){
    memset(id_visited,0,sizeof(id_visited));
    for(int i=0;i<MAXID;i++){
        if(id_visited[i]>1||waited[i].size()==0){//已经访问过了or不可能死锁
            continue;
        }
        queue<int> q;
        q.push(i);
        id_visited[i]=1;
        while (!q.empty())
        {
            int id=q.front();
            q.pop();
            for(auto k:waited[id]){
                if(res_map.find(k)!=res_map.end()){//有占用该资源的
                    int nid=res_map[k];
                    if(id_visited[nid]==3||id_visited[nid]==1){//死锁
                        for(int j=0;j<MAXID;j++){
                            if(id_visited[j]==1){
                                id_visited[j]=3;
                            }
                        }
                    }else if(id_visited[nid]==0){
                        id_visited[nid]=1;
                        q.push(nid);
                    }
                }
            }
        }
        for(int j=0;j<MAXID;j++){
            if(id_visited[j]==1){
                id_visited[j]=2;
            }
        }
    }
    for(int j=0;j<MAXID;j++){
        if(id_visited[j]==3){
            printf("%d ",j);
        }
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
        cout<<str.substr(0,st1-1)<<endl;
        int id=stoi(str.substr(0,st1-1));
        cout<<str.substr(st1,ed1-st1)<<" "<<str.substr(st2,ed2-st2)<<endl;
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
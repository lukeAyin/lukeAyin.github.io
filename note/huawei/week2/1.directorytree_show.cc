#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

map<string,int> id_map;//将目录名字与id对应起来
vector<vector<int>> tree(305);//存储id对应的子节点集合
int res=0;

void dfs(int id,int t){
    if(t==1){
        res++;
        return ;
    }
    for(auto child:tree[id]){
        if(tree[id].size()>1){
            dfs(child,t-1);
        }else{
            dfs(child,t);
        }
    }
}

int CountNodeInDepthT(int t){
    dfs(0,t);
    return res;
}

int main(){
    int N;
    fstream input("data_directorytree_show.txt");
    input>>N;
    int i=0;
    while(N--){
        string parent,child;
        input>>parent>>child;
        if(id_map.find(parent)==id_map.end()){
            id_map[parent]=i++;
        }
        if(id_map.find(child)==id_map.end()){
            id_map[child]=i++;
        }
        tree[id_map[parent]].emplace_back(id_map[child]);
    } 
    int t;
    input>>t;
    CountNodeInDepthT(t);
    printf("%d",res);
}
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

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
map<int,vector<int>> id_map;
const int MAXN=10000;
int isRoot[MAXN];
int depth[MAXN];

void dfs(int id,int dep){
    depth[id]=dep;
    for(auto it:id_map[id]){
        dfs(it,dep+1);
    }
}

int CountNodeOfDepth(int t){
    int res=0;
    for(auto &it:id_map){
        if(isRoot[it.first]!=0){
            dfs(it.first,1);
        }
    }
    for(int i=0;i<MAXN;i++){
        if(depth[i]==t){
            res++;
        }
    }
    return res;
}

bool CheckValidSubId(int id){
    
}

int main(){
    memset(isRoot,-1,sizeof(isRoot));
    memset(depth,0,sizeof(depth));
    int N=0;
    fstream input("data_log_grooming.txt");
    input>>N;
    string tmp;
    getline(input,tmp);
    while(N--){
        getline(input,tmp);
        int st=tmp.find_first_of("|",0);
        st=tmp.find_first_of("|",st+1);
        int p_id=getNumber(tmp,st);
        if((st=tmp.find_first_of("|",st))!=string::npos){
            if((st+6)<tmp.size()){
                string op=tmp.substr(st+1,5);
                transform(op.begin(),op.end(),op.begin(),::tolower);
                if(op=="start"){
                    int sub_id=getNumber(tmp,st);
                    isRoot[sub_id]=0;
                    id_map[p_id].emplace_back(sub_id);
                }
            }else{
                continue;
            }
        }
    }
    int t=0;
    input>>t;
    printf("%d\r\n",CountNodeOfDepth(t));
}
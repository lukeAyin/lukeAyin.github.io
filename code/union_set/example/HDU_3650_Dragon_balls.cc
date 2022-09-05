#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
const int N=10001;
int n,q;
int city[N];//各龙珠所在城市
int times[N];//各龙珠移动次数
int cnt[N];//各城市含有龙珠数
void init(){
    for(int i=1;i<=n;++i){
        city[i]=i;
        times[i]=0;
        cnt[i]=1;
    }
}

int find(int i){
    if(city[i]==i){
        return i;
    }
    int root=find(city[i]);
    times[i]+=times[city[i]];
    city[i]=root;
    return root;
}

void union_set(int x,int y){
    int fx=find(x);
    int fy=find(y);
    city[fx]=fy;
    times[fx]++;
    cnt[fy]+=cnt[fx];
    cnt[fx]=0;
}

int main(){
    int t;
    // FILE *fp=fopen("data.txt","r");
    // auto scan=bind(fscanf,fp);
    scanf("%d",&t);
    for(int j=1;j<=t;++j){
        scanf("%d%d",&n,&q);
        init();
        printf("Case %d:\n",j);
        for(int i=0;i<q;++i){
            char flag;
            int A,B;
            getchar();
            scanf("%c",&flag);
            // printf("flag:%c\n",flag);
            if(flag=='T'){
                scanf("%d%d",&A,&B);
                union_set(A,B);
            }else{
                scanf("%d",&A);
                int root=find(A);
                printf("%d %d %d\n",root,cnt[root],times[A]);
            }
        }
    }


}
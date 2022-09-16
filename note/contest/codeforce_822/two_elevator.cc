#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
int check(int a,int b,int c){
    int l=(abs(b-c)+c);
    if(l==a){
        return 3;
    }else if(l<a){
        return 2;
    }else{
        return 1;
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        printf("%d\n",check(a,b,c));
    }
}
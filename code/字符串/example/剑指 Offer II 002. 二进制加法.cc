#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
class Solution {
public:
    static const int M=1e4;
    string addBinary(string a, string b) {
        bitset<M> A(a);
        bitset<M> B(b);
        bitset<M> res;
        while(1){
            res=A^B;
            B=A&B;
            A=res;
            B<<=1;
            if(B==0){
                break;
            }
        }
        string r=res.to_string();
        int pos=r.find_first_of('1');
        if(pos==-1){
            
            return "0";
        }
        return r.substr(pos);
    }
};
int main(){
    Solution s;
    printf("%s",s.addBinary("0","0"));
}
#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
void getPath(string str){
    int m;
    char st=str[0];
    char ed=str.back();
    int move=1;
    vector<vector<int>> mp(26,vector<int>());
    for(int i=0;i<str.size();i++){
        mp[str[i]-'a'].emplace_back(i+1);
    }
    if(ed<st){
        move=-1;
    } 
    int res=abs(ed-st);
    vector<int> path;
    for(;st!=(ed+move);st+=move){
        int id=st-'a';
        int len=mp[id].size();
        path.insert(path.end(),mp[id].begin(),mp[id].end());
    }
    cout<<res<<" "<<path.size()<<endl;
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<" ";
    }
    cout<<endl;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        string str;
        cin>>str;
        getPath(str);
    }
}
/*
Polycarp was given a row of tiles. Each tile contains one lowercase letter of the Latin alphabet. The entire sequence of tiles forms the string s.

In other words, you are given a string s consisting of lowercase Latin letters.

Initially, Polycarp is on the first tile of the row and wants to get to the last tile by jumping on the tiles. Jumping from i-th tile to j-th tile has a cost equal to |index(si)−index(sj)|, where index(c) is the index of the letter c in the alphabet (for example, index('a')=1, index('b')=2, ..., index('z')=26) .

Polycarp wants to get to the n-th tile for the minimum total cost, but at the same time make maximum number of jumps.

In other words, among all possible ways to get to the last tile for the minimum total cost, he will choose the one with the maximum number of jumps.

Polycarp can visit each tile at most once.

Polycarp asks you to help — print the sequence of indices of string s on which he should jump.

Input
The first line of the input contains an integer t (1≤t≤104) — the number of test cases in the test.

Each test case is given by the string s (2≤|s|≤2⋅105), where |s| — is the length of string s. The string s consists of lowercase Latin letters.

It is guaranteed that the sum of string lengths s over all test cases does not exceed 2⋅105.

Output
The answer to each test case consists of two lines.

In the first line print two integers cost, m, where cost is the minimum total cost of the path, and m is the maximum number of visited tiles Polycarp can make to get to n-th tiles for the minimum total cost cost (i.e. the number of jumps is m−1).

In the next line print m different numbers j1,j2,…,jm (1≤ji≤|s|) — the sequence of indices of the tiles Polycarp will jump on. The first number in the sequence must be 1 (that is, j1=1) and the last number must be the value of |s| (that is, jm=|s|).

If there are multiple answers, print any of them.
*/
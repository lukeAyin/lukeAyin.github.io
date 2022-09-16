#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;
string decode(string& str){
    string res;
    int n=str.size();
    for(int i=n-1;i>=0;i--){
        if(str[i]=='0'){
            int val=((str[i-2]-'0')*10);
            val+=(str[i-1]-'1');
            res+=('a'+val);
            i-=2;
        }else{
            res+=(str[i]-'1'+'a');
        }
    }
    reverse(res.begin(),res.end());
    return res;
}
int main(){
    int q;
    scanf("%d",&q);
    while(q--){
        int t;
        cin>>t;
        string str;
        cin>>str;
        cout<<decode(str)<<endl;
    }
}
/*
Polycarp has a string s consisting of lowercase Latin letters.

He encodes it using the following algorithm.

He goes through the letters of the string s from left to right and for each letter Polycarp considers its number in the alphabet:

if the letter number is single-digit number (less than 10), then just writes it out;
if the letter number is a two-digit number (greater than or equal to 10), then it writes it out and adds the number 0 after.
For example, if the string s is code, then Polycarp will encode this string as follows:

'c' — is the 3-rd letter of the alphabet. Consequently, Polycarp adds 3 to the code (the code becomes equal to 3);
'o' — is the 15-th letter of the alphabet. Consequently, Polycarp adds 15 to the code and also 0 (the code becomes 3150);
'd' — is the 4-th letter of the alphabet. Consequently, Polycarp adds 4 to the code (the code becomes 31504);
'e' — is the 5-th letter of the alphabet. Therefore, Polycarp adds 5 to the code (the code becomes 315045).
Thus, code of string code is 315045.

You are given a string t resulting from encoding the string s. Your task is to decode it (get the original string s by t).

Input
The first line of the input contains an integer q (1≤q≤104) — the number of test cases in the input.

The descriptions of the test cases follow.

The first line of description of each test case contains one integer n (1≤n≤50) — the length of the given code.

The second line of the description of each test case contains a string t of length n — the given code. It is guaranteed that there exists such a string of lowercase Latin letters, as a result of encoding which the string t is obtained.

Output
For each test case output the required string s — the string that gives string t as the result of encoding. It is guaranteed that such a string always exists. It can be shown that such a string is always unique.
*/
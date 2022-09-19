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
    bool isInterleave(string s1, string s2, string s3) {
        int n1=s1.size();
        int n2=s2.size();
        int m=s3.size();
        if(m!=(n1+n2)){
            return false;
        }
        vector<vector<int>> dp(n1+1,vector<int>(n2+1,0));
        dp[0][0]=1;
        for(int i=0;i<=n1;i++){
            for(int j=0;j<=n2;j++){
                int p=i+j-1;
                if(i>0){
                    dp[i][j]|=(dp[i-1][j]&&s1[i-1]==s3[p]);
                }
                if(j>0){
                    dp[i][j]|=(dp[i][j-1]&&s2[j-1]==s3[p]);
                }
            }
        }
        return dp[n1][n2];
    }
};

int main(){
    Solution s;
    cout<<s.isInterleave("aabcc","dbbca","aadbbcbcac");
}
/*
给定三个字符串 s1、s2、s3，请判断 s3 能不能由 s1 和 s2 交织（交错） 组成。

两个字符串 s 和 t 交织 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交织 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
提示：a + b 意味着字符串 a 和 b 连接。

0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1、s2、和 s3 都由小写英文字母组成
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/IY6buf
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
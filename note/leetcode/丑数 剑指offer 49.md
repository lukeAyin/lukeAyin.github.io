丑数 剑指offer 49

# question
我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

 

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  

1 是丑数。
n 不超过1690。

链接：https://leetcode-cn.com/problems/chou-shu-lcof

~~~
#define REP(i,a) for(int i=1;i<a;++i)
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        int two=0;
        int tri=0;
        int panty=0;
        dp[0]=1;
        REP(i,n){
            int t1=dp[two]*2;
            int t2=dp[tri]*3;
            int t3=dp[panty]*5;
            int m=INT_MAX;
            m=min(t1,min(t2,t3));
            if(m==t1)two++;
            if(m==t2)tri++;
            if(m==t3)panty++;
            dp[i]=m;
            //cout<<dp[i]<<" ";
        }
        return dp[n-1];
    }
};
~~~
# quesiton2
## 超级丑数
编写一段程序来查找第 n 个超级丑数。

超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。

示例:

输入: n = 12, primes = [2,7,13,19]
输出: 32 
解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
说明:

1 是任何给定 primes 的超级丑数。
 给定 primes 中的数字以升序排列。
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
第 n 个超级丑数确保在 32 位有符整数范围内。

链接：https://leetcode-cn.com/problems/super-ugly-number

~~~
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> dp(n);
        int m=primes.size();
        vector<int> points(primes.size(),0);
        dp[0]=1;
        for(int i=1;i<n;++i){
            int ans=dp[points[0]]*primes[0];
            int nextj=0;
            for(int j=1;j<m;++j){
                int sum=dp[points[j]]*primes[j];
                if(ans>sum){
                    ans=sum;
                    nextj=j;
                }else if(sum==ans){//只要相等就说明有重复的存在就可以去掉重复的数了。
                    points[j]++;
                }
            }
            points[nextj]++;
            //cout<<ans<<" ";
            dp[i]=ans;
        }
        return dp[n-1];
    }
};
~~~
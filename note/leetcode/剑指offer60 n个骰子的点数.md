剑指offer60 n个骰子的点数

# question
把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。

示例 1:
输入: 1
输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
示例 2:
输入: 2
输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]
链接：https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof
## 动态规划
~~~
class Solution {
public:
    double P=1;
    vector<double> dicesProbability(int n) {
        vector<double> ans((n)*5+1,0);
        for(int i=0;i<6;++i){
            ans[i]=1;
        }
        for(int i=2;i<=n;++i){
            for(int j=(i)*5;j>=0;--j){
                double temp=0;
                for(int k=0;k<6;++k){
                    if(j-k>=0)
                    temp+=(ans[j-k]);
                }
                ans[j]=(temp);
            }
        }
        double all=pow(6,n);
        for(int i=0;i<ans.size();++i){
            ans[i]/=all;
        }
        return ans;
    }
};
~~~
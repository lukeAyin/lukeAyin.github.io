剑指offer 56-I 数组中数字出现的次数

# question
一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
示例 1：
输入：nums = [4,1,4,6]
输出：[1,6] 或 [6,1]
示例 2：
输入：nums = [1,2,10,4,1,4,3,3]
输出：[2,10] 或 [10,2]
限制：
2 <= nums.length <= 10000
链接：https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof
## 分组位运算
先对所有数字进行一次异或，得到两个出现一次的数字的异或值。
在异或结果中找到任意为 11 的位。
根据这一位对所有的数字进行分组。
在每个组内进行异或操作，得到两个数字。

~~~
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret=0;
        for(auto num:nums){
            ret=ret^num;
        }
        int div=1;
        while((div&ret)==0){
            div<<=1;
        }
        int a=0,b=0;
        for(auto num:nums){
            if(num&div){
                a=a^num;
            }else{
                b=b^num;
            }
        }
        return vector<int>{a,b};
    }
};
~~~
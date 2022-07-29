剑指offer 48 最长不含重复字符的子字符串

# question
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
链接：https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof
## 双指针滑动窗口
~~~
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans=0;
        vector<int> count(128,0);
        int left=0;
        int right=0;
        while(right<s.size()){
            if(count[s[right]]==0){
                count[s[right++]]++;
            }else{
                count[s[left++]]--;
            }
            ans=max(ans,right-left);
        }
        return ans;
    }
};
~~~
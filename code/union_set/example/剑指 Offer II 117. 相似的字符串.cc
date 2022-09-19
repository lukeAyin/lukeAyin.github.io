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
    int numSimilarGroups(vector<string>& strs) {
        auto check=[&](const string& s1,const string& s2){
            int n=s1.size();
            int cnt=0;
            for(int i=0;i<n;i++){
                if(s1[i]!=s2[i]){
                    cnt++;
                    if(cnt>2){
                        return false;
                    }
                }
            }
            return true;
        };
        int n=strs.size();
        vector<int> parents(n,0);
        iota(parents.begin(),parents.end(),0);
        function<int(int)> find=[&](int x){
            if(parents[x]==x){
                return x;
            }
            return parents[x]=find(parents[x]);
        };
        auto union_set=[&](int x,int y){
            int fx=find(x);
            int fy=find(y);
            if(fx==fy){
                return false;
            }
            parents[fx]=fy;
            return true;
        };
        int cnt=n;
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(check(strs[i],strs[j])){
                    if(union_set(i,j)){
                        cnt--;
                    }
                }
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    vector<string> vec={"tars","rats","arts","star"};
    cout<<s.numSimilarGroups(vec);//2

}
/*
如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

给定一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个 字母异位词 。请问 strs 中有多少个相似字符串组？

字母异位词（anagram），一种把某个字符串的字母的位置（顺序）加以改换所形成的新词。
1 <= strs.length <= 300
1 <= strs[i].length <= 300
strs[i] 只包含小写字母。
strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。
来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/H6lPxb
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
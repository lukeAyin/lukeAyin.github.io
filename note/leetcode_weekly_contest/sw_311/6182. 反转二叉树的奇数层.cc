#include<bits/stdc++.h>
#define pb puch_back
#define eb emplace_back
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        vector<int> vec;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            auto node=q.front();
            q.pop();
            vec.emplace_back(node->val);
            if(node->left){
                q.push(node->left);
                q.push(node->right);
            }
        }
        int n=vec.size();
        int base=1;
        int l=pow(2,base)-1;
        int r=pow(2,base+1)-1;
        while(l<n){
            reverse(vec.begin()+l,vec.begin()+r);
            base+=2;
            l=pow(2,base)-1;
            r=pow(2,base+1)-1;
        }
        TreeNode *nroot=new TreeNode(vec[0]);
        q.push(nroot);
        int i=1;
        while(i<n){
            auto node=q.front();
            q.pop();
            node->left=new TreeNode(vec[i++]);
            node->right=new TreeNode(vec[i++]);
            q.push(node->left);
            q.push(node->right);
        }
        return nroot;
    }
};
int main(){
    Solution s;
}
/*
给你一棵 完美 二叉树的根节点 root ，请你反转这棵树中每个 奇数 层的节点值。

例如，假设第 3 层的节点值是 [2,1,3,4,7,11,29,18] ，那么反转后它应该变成 [18,29,11,7,4,3,1,2] 。
反转后，返回树的根节点。

完美 二叉树需满足：二叉树的所有父节点都有两个子节点，且所有叶子节点都在同一层。

节点的 层数 等于该节点到根节点之间的边数。
树中的节点数目在范围 [1, 2^14] 内
0 <= Node.val <= 105
root 是一棵 完美 二叉树
*/
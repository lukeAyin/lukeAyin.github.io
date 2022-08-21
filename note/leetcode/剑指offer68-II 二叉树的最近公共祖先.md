剑指offer68-II 二叉树的最近公共祖先

# question
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]
链接：https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof

## 1. 递归
~~~
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* ans;
    bool hasNode(TreeNode* root,TreeNode* p,TreeNode* q){
        if(root==nullptr){
            return false;
        }
        //cout<<root->val<<" ";
        bool flag_left=hasNode(root->left,p,q);
        bool flag_right=hasNode(root->right,p,q);
        if((root==p||root==q)){
            if(flag_left||flag_right){
                ans=root;
            }
            return true;
        }
        if(flag_left&&flag_right){
            ans=root;
        }
        return flag_left||flag_right;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        hasNode(root,p,q);
        return ans;
    }
};
~~~
## 2.递归
- l、r非空时，说明p、q分居root的两侧，root就是LCA
- l、r任一为空，说明LCA位于另一子树或其祖先中
~~~
class Solution {
    public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || p == root || q == root) {
            return root;
        }

        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
    
        return l == nullptr ? r : (r == nullptr ? l : root);
    }
};
~~~
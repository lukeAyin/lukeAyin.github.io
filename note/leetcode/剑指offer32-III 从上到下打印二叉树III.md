剑指offer32-III 从上到下打印二叉树III

# question
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
例如:
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [20,9],
  [15,7]
]
提示：
节点总数 <= 1000
链接：https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof
## 双栈
***
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root){
            return ans;
        }
        stack<TreeNode*> s1,s2;
        s1.push(root);
        while(!s1.empty()){
            vector<int> v1;
            while(!s1.empty()){
                TreeNode* temp=s1.top();
                s1.pop();
                v1.emplace_back(temp->val);
                if(temp->left){
                    s2.push(temp->left);
                }
                if(temp->right)s2.push(temp->right);
            }
            vector<int> v2;
            while(!s2.empty()){
                TreeNode* temp=s2.top();
                s2.pop();
                v2.emplace_back(temp->val);
                if(temp->right)s1.push(temp->right);
                if(temp->left)s1.push(temp->left);

            }
            ans.emplace_back(v1);
            if(v2.size())ans.emplace_back(v2);
        }
        return ans;
    }
};
~~~
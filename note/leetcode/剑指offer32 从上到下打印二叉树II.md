剑指offer32 从上到下打印二叉树II

# question
剑指 Offer 32 - II. 从上到下打印二叉树 II
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。

例如:
给定二叉树: [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]

## 双栈层序遍历
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
        queue<TreeNode*> q1;
        q1.push(root);
        queue<TreeNode*> q2;
        while(!q1.empty()||!q2.empty()){
            vector<int> v1;
            while(!q1.empty()){
               TreeNode* temp=q1.front();
               q1.pop();
               v1.push_back(temp->val);
               if(temp->left){
                   q2.push(temp->left);
               }
               if(temp->right){
                   q2.push(temp->right);
               }
            }
            vector<int> v2;
            while(!q2.empty()){
                TreeNode* temp=q2.front();
                q2.pop();
                v2.push_back(temp->val);
                if(temp->left){
                    q1.push(temp->left);
                }
                if(temp->right){
                    q1.push(temp->right);
                }
            }
            // if(v1.size()){
            //     ans.push_back(v1);
            // }
            ans.push_back(v1);
            if(v2.size()){
                ans.push_back(v2);
            }
        }
        return ans;

    }
};
~~~
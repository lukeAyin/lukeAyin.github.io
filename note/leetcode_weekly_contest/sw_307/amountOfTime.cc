#include<bits/stdc++.h>
using namespace std;
int main(){

}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    map<TreeNode*,TreeNode*> parent;
    void dfs(TreeNode* root,map<int,TreeNode*>& mt){
        mt[root->val]=root;
        if(root->left!=nullptr){
            parent[root->left]=root;
            dfs(root->left,mt);
        }
        if(root->right!=nullptr){
                    parent[root->right]=root;
                    dfs(root->right,mt);
        }

    }
    int getDepth(TreeNode* root,map<TreeNode*,int> &depth){
        if(root==nullptr){
            return 0;
        }
        int res=max(getDepth(root->left,depth),getDepth(root->right,depth))+1;
        depth[root]=res;
        return res;
    }

    int amountOfTime(TreeNode* root, int start) {
        map<int,TreeNode*> mt;  
        dfs(root,mt);
        map<TreeNode*,int> depth;
        getDepth(root,depth);
        TreeNode* node=mt[start];
        int res=max(depth[node->left],depth[node->right]);
        int let=0;
        while(parent.find(node)!=parent.end()){
            auto pt=parent[node];
            auto x=pt->left;
            if(x!=nullptr&&x!=node){
                res=max(res,let+depth[x]+1);
            }
            x=pt->right;
            if(x!=nullptr&&x!=node){
                res=max(res,let+depth[x]+1);
            }
            res=max(res,let+1);
            node=pt;
            let++;
        }
        return res;
    }
};
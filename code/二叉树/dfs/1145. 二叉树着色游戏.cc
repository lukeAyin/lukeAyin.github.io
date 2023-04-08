#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int,int>
#define PQ priority_queue

//Definition for a binary tree node.
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
    vector<int> count;
    //flag为0代表x节点以上的节点数目
    // flag为1代表x节点的左子树数目
    // flag为2代表y节点的右子树数目
    void dfs(TreeNode* root,int x,int flag){
        if(root==nullptr){
            return;
        }
        if(root->val==x){
            dfs(root->left,x,1);
            dfs(root->right,x,2);
            return ;
        }
        count[flag]++;
        dfs(root->left,x,flag);
        dfs(root->right,x,flag);
    }
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        count.resize(3,0);
        dfs(root,x,0);
        sort(count.begin(),count.end());
        return count[0]+count[1]<count[2];
    }
};
int main(){
    
}
剑指offer 07 重建二叉树

输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

 

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7

链接：https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof
## 1.递归
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
    map<int,int> hm;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n=preorder.size();
        for(int i=0;i<n;++i){
            hm[inorder[i]]=i;
        }
        return bT(preorder,inorder,0,n-1,0,n-1);
    }
    TreeNode* bT(vector<int>& preorder,vector<int>& inorder,int p_left,int p_right,int i_left,int i_right){
        if(p_left<=p_right){
            TreeNode* node=new TreeNode(preorder[p_left]);
            int index=hm[preorder[p_left]];
            int left_length=index-i_left;
            node->left=bT(preorder,inorder,p_left+1,p_left+left_length,i_left,index-1);
            node->right=bT(preorder,inorder,p_left+left_length+1,p_right,index+1,i_right);
            return node;
        }
        return nullptr;
    }
};
~~~
## 2.迭代
- v 是u的左儿子。这是因为在遍历到 u之后，下一个遍历的节点就是 u 的左儿子，即 v；
- u 没有左儿子，并且 v是 u的某个祖先节点（或者 u本身）的右儿子。如果 u没有左儿子，那么下一个遍历的节点就是 u 的右儿子。如果 u没有右儿子，我们就会向上回溯，直到遇到第一个有右儿子（且u不在它的右儿子的子树中）的节点$u_a$,那么v就是$u_a$的右儿子。

我们用一个栈 stack 来维护「当前节点的所有还没有考虑过右儿子的祖先节点」，栈顶就是当前节点。也就是说，只有在栈中的节点才可能连接一个新的右儿子。同时，我们用一个指针 index 指向中序遍历的某个位置，初始值为 0。index 对应的节点是「当前节点不断往左走达到的最终节点」，这也是符合中序遍历的，它的作用在下面的过程中会有所体现。

首先我们将根节点 3 入栈，再初始化 index 所指向的节点为 4，随后对于前序遍历中的每个节点，我们依次判断它是栈顶节点的左儿子，还是栈中某个节点的右儿子。

我们遍历 9。9 一定是栈顶节点 3 的左儿子。我们使用反证法，假设 9 是 3 的右儿子，那么 3 没有左儿子，index 应该恰好指向 3，但实际上为 4，因此产生了矛盾。所以我们将 9 作为 3 的左儿子，并将 9 入栈。

stack = [3, 9]
index -> inorder[0] = 4
我们遍历 8，5 和 4。同理可得它们都是上一个节点（栈顶节点）的左儿子，所以它们会依次入栈。

stack = [3, 9, 8, 5, 4]
index -> inorder[0] = 4
我们遍历 10，这时情况就不一样了。我们发现 index 恰好指向当前的栈顶节点 4，也就是说 4 没有左儿子，那么 10 必须为栈中某个节点的右儿子。那么如何找到这个节点呢？栈中的节点的顺序和它们在前序遍历中出现的顺序是一致的，而且每一个节点的右儿子都还没有被遍历过，那么这些节点的顺序和它们在中序遍历中出现的顺序一定是相反的。

这是因为栈中的任意两个相邻的节点，前者都是后者的某个祖先。并且我们知道，栈中的任意一个节点的右儿子还没有被遍历过，说明后者一定是前者左儿子的子树中的节点，那么后者就先于前者出现在中序遍历中。

因此我们可以把 index 不断向右移动，并与栈顶节点进行比较。如果 index 对应的元素恰好等于栈顶节点，那么说明我们在中序遍历中找到了栈顶节点，所以将 index 增加 1 并弹出栈顶节点，直到 index 对应的元素不等于栈顶节点。按照这样的过程，我们弹出的最后一个节点 x 就是 10 的双亲节点，这是因为 10 出现在了 x 与 x 在栈中的下一个节点的中序遍历之间，因此 10 就是 x 的右儿子。

回到我们的例子，我们会依次从栈顶弹出 4，5 和 8，并且将 index 向右移动了三次。我们将 10 作为最后弹出的节点 8 的右儿子，并将 10 入栈。

stack = [3, 9, 10]
index -> inorder[3] = 10
我们遍历 20。同理，index 恰好指向当前栈顶节点 10，那么我们会依次从栈顶弹出 10，9 和 3，并且将 index 向右移动了三次。我们将 20 作为最后弹出的节点 3 的右儿子，并将 20 入栈。

stack = [20]
index -> inorder[6] = 15
我们遍历 15，将 15 作为栈顶节点 20 的左儿子，并将 15 入栈。

stack = [20, 15]
index -> inorder[6] = 15
我们遍历 7。index 恰好指向当前栈顶节点 15，那么我们会依次从栈顶弹出 15 和 20，并且将 index 向右移动了两次。我们将 7 作为最后弹出的节点 20 的右儿子，并将 7 入栈。

stack = [7]
index -> inorder[8] = 7
此时遍历结束，我们就构造出了正确的二叉树。

算法

我们归纳出上述例子中的算法流程：

我们用一个栈和一个指针辅助进行二叉树的构造。初始时栈中存放了根节点（前序遍历的第一个节点），指针指向中序遍历的第一个节点；

我们依次枚举前序遍历中除了第一个节点以外的每个节点。如果 index 恰好指向栈顶节点，那么我们不断地弹出栈顶节点并向右移动 index，并将当前节点作为最后一个弹出的节点的右儿子；如果 index 和栈顶节点不同，我们将当前节点作为栈顶节点的左儿子；

无论是哪一种情况，我们最后都将当前的节点入栈。

最后得到的二叉树即为答案。
~~~
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
~~~

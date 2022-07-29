剑指offer 36 二叉搜索树与双向链表

# question
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
为了让您更好地理解问题，以下面的二叉搜索树为例：
 ![8e4f20b0f92b2015627d4a4e2f7f5c69.png](../_resources/33b281ff959d4d1789b3c3f17b29c31e.png)
我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。
 ![bc0ea19e89c1aae1e3d0125e776fd34e.png](../_resources/a2ef326b8cb94e6185ff8d234498c271.png)
链接：https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof

## 辅助栈中序遍历修改指针
~~~
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(!root){
            return root;
        }
        Node* pre;
        pre=root;
        stack<Node*> s;
        while(pre){
            s.push(pre);
            pre=pre->left;
        }
        pre=s.top();
        Node* curr;
        while(!s.empty()){
            curr=s.top();
            //cout<<temp->val;
            s.pop();
            if(curr->right){
                Node* tt=curr->right;
                while(tt){
                    s.push(tt);
                    tt=tt->left;
                }
            }
            if(s.empty()){
                break;
            }
            if(s.top()->left!=curr){
                s.top()->left=curr;
            }
            curr->right=s.top();
        }
        pre->left=curr;
        curr->right=pre;
        return pre;
    }
};
~~~
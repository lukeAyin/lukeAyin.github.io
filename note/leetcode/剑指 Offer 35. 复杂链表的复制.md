剑指 Offer 35. 复杂链表的复制

# question
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。
- 示例1：
  ![06d86a7b461987baa1ea1ec1ed786a8c.png](../_resources/a56ce4ef21c94991a7ba82e6012998c2.png)
  输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
  输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
- 示例2：
  ![1935165ed51de89343f60d863d7d0c79.png](../_resources/f3d61b6bf8aa4f6eae6a66766eb79684.png)
- 输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
- 示例3：
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。
## 哈希表
~~~
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* node=head;
        Node* dummy=new Node(-1);
        Node* curr=dummy;
        map<Node*,Node*> m;
        while(node){
            Node* t=new Node(node->val);
            curr->next=t;
            curr=curr->next;
            m[node]=curr;
            node=node->next;
        }
        m[nullptr]=nullptr;
        curr=dummy->next;
        node=head;
        while(curr){
            //if(node->random)
            curr->random=m[node->random];
            curr=curr->next;
            node=node->next;
        }
        return dummy->next;
    }
};
~~~
## 拼接+拆分
考虑构建 原节点 1 -> 新节点 1 -> 原节点 2 -> 新节点 2 -> …… 的拼接链表，如此便可在访问原节点的 random 指向节点的同时找到新对应新节点的 random 指向节点。
~~~
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr) return nullptr;
        Node* cur = head;
        // 1. 复制各节点，并构建拼接链表
        while(cur != nullptr) {
            Node* tmp = new Node(cur->val);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }
        // 2. 构建各新节点的 random 指向
        cur = head;
        while(cur != nullptr) {
            if(cur->random != nullptr)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }
        // 3. 拆分两链表
        cur = head->next;
        Node* pre = head, *res = head->next;
        while(cur->next != nullptr) {
            pre->next = pre->next->next;
            cur->next = cur->next->next;
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = nullptr; // 单独处理原链表尾节点
        return res;      // 返回新链表头节点
    }
};
~~~
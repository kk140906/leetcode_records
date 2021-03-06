//Reverse a singly linked list. 
//
// Example: 
//
// 
//Input: 1->2->3->4->5->NULL
//Output: 5->4->3->2->1->NULL
// 
//
// Follow up: 
//
// A linked list can be reversed either iteratively or recursively. Could you im
//plement both? 
// Related Topics Linked List 
// 👍 5634 👎 107
#include <initializer_list>
#include <iostream>
#include "list_node.h"
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#define USING_HEAD_INSERT

class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        if (!head) return nullptr;
#ifdef USING_HEAD_INSERT
        ListNode* move_head = nullptr;
        while (head) {
            auto tail = new ListNode(head->val);
            tail->next = move_head;
            move_head = tail;
            head = head->next;
        }
        auto node = new ListNode;
        return node->next = move_head;
#elif defined(USING_STL)
        std::list<int> il;
        while (head) {
            il.emplace_back(head->val);
            head = head->next;
        }
        auto new_head = new ListNode,tail = new_head;
        while(!il.empty()){
            tail->next = new ListNode(il.back());
            il.pop_back();
            tail = tail->next;
        }
        return new_head->next;
#else
        auto tmp_head = head->next;
        head->next = nullptr;
        while (tmp_head) {
            auto tmp_tail = tmp_head;
            tmp_head = tmp_head->next;
            tmp_tail->next = head;
            head = tmp_tail;
        }
        auto new_head = new ListNode;
        return new_head->next = head;
#endif
    }
};

//leetcode submit region end(Prohibit modification and deletion)
int main() {
    auto head = CreateList<ListNode>({1, 3, 4, 6, 7, 8});
    Solution solution;
    std::cout << solution.reverseList(head->next);
    return 0;
}
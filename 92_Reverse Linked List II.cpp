//Reverse a linked list from position m to n. Do it in one-pass. 
//
// Note: 1 ≤ m ≤ n ≤ length of list. 
//
// Example: 
//
// 
//Input: 1->2->3->4->5->NULL, m = 2, n = 4
//Output: 1->4->3->2->5->NULL
// 
// Related Topics Linked List 
// 👍 3260 👎 169

#include "list_node.h"
#include <iostream>
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

class Solution {
public:
    ListNode *reverseN(ListNode *head, int n) {
        // 判断head->next是为了避免n超过链表长度
        if (n <= 1 || !head->next) {
            stop_node_ = head->next;
            return head;
        }
        ListNode *p = reverseN(head->next, n - 1);
        head->next->next = head;
        head->next = stop_node_;
        return p;
    }


    ListNode *reverseBetween(ListNode *head, int m, int n) {
#define SOLUTION_3

#ifdef SOLUTION_1
        if (m == n) return head;
        ListNode dummy_head(INT_MAX, head);
        ListNode *p1{&dummy_head}, *p2{nullptr}, *p3{nullptr};
        int pos{0};
        // m < length of list，m - 1 定位到要反转结点的前一个位置
        while (pos < m - 1) {
            p1 = p1->next;
            ++pos;
        }
        p2 = p1->next;
        p3 = p2->next;
        while (pos < n - 1  && p3) {
            ListNode *p4{p3->next};
            p3->next = p2;
            p2 = p3;
            p3 = p4;
            ++pos;
        }
        p1->next->next = p3;
        p1->next = p2;
        return dummy_head.next;
#elif defined(SOLUTION_2)
        // SOLUTION_2 递归
        ListNode dummy_head(INT_MAX, head), *p1{&dummy_head};
        for (int i = 0; i < m - 1; ++i) {
            p1 = p1->next;
        }
        ListNode *p2 = reverseN(p1->next,n - m + 1);
        p1->next = p2;
        return dummy_head.next;
#else
        ListNode dummy_head(INT_MAX, head);
        ListNode *p1{&dummy_head};
        for (int i = 0; i < m - 1; ++i)
            p1 = p1->next;
        ListNode *p2 = p1->next;
        for (int i = 0; i < n - m && p2->next; ++i) {
            ListNode *p3 = p1->next;
            p1->next = p2->next;
            p2->next = p2->next->next;
            p1->next->next = p3;
        }
        return dummy_head.next;
#endif
    }

private:
    ListNode *stop_node_{nullptr};
};
//leetcode submit region end(Prohibit modification and deletion)

int main(int argc, char **argv) {
    ListNode *head = CreateList<ListNode>({1, 2, 3, 4, 5, 6});
    std::cout << head << std::endl;
    ListNode *reversed_head = Solution().reverseBetween(head,4,7);
    std::cout << reversed_head << std::endl;

    return 0;
}
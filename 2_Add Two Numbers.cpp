//You are given two non-empty linked lists representing two non-negative integer
//s. The digits are stored in reverse order, and each of their nodes contains a si
//ngle digit. Add the two numbers and return the sum as a linked list. 
//
// You may assume the two numbers do not contain any leading zero, except the nu
//mber 0 itself. 
//
// 
// Example 1: 
//
// 
//Input: l1 = [2,4,3], l2 = [5,6,4]
//Output: [7,0,8]
//Explanation: 342 + 465 = 807.
// 
//
// Example 2: 
//
// 
//Input: l1 = [0], l2 = [0]
//Output: [0]
// 
//
// Example 3: 
//
// 
//Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
//Output: [8,9,9,9,0,0,0,1]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in each linked list is in the range [1, 100]. 
// 0 <= Node.val <= 9 
// It is guaranteed that the list represents a number that does not have leading
// zeros. 
// 
// Related Topics Linked List Math 
// 👍 9774 👎 2452

#include <iostream>
#include <initializer_list>
#include "list_node.h"

using namespace std;

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
#define USING_RECURSIVE

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *head = new ListNode, *tail = head;
#ifndef USING_RECURSIVE
        // 关键点1：每次循环进行两个1位数求和操作，同时必须考虑上一次计算是否存在进位
        // 关键点2：每一次求和操作都可能发生进位，因此循环终止的条件是两个链表中都没有元素且最后一个元素计算完毕后也没有发生进位
        // 关键点3: 只要某个链表的next指针域还指向下一个结点，就必须继续遍历下去
        // 关键点4：通过一个虚拟头结点保证正确获取首结点，而循环操作移动的是尾结点
        int c = 0;
        while (c || l1 || l2) {
            c += (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            tail = tail->next = new ListNode(c % 10);
            c /= 10;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
#else
        // 关键点1：每次递归都会重新设定c的值，所以递归终止的条件中就不能使用c,两个链表都没有元素是递归终止的条件，
        //         但是每次求和都可能发生进位，因此需要将进位的数值加到下一个结点上，
        //         如果下一个结点已经空了那么就创建一个新的结点挂接上去。
        if (!l1 && !l2) return nullptr;
        auto c = (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
        tail = tail->next = new ListNode(c % 10);
        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
        c /= 10;
        if (l1) l1->val += c;
        else if (c) l1 = new ListNode(c);
        tail->next = addTwoNumbers(l1, l2);
#endif
        return head->next;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

int main() {
    auto l1 = CreateList({9});
    auto l2 = CreateList({9});
    Solution solution;
    cout << solution.addTwoNumbers(l1, l2);
    return 0;
}
//Given the head of a linked list, remove the nth node from the end of the list 
//and return its head. 
//
// Follow up: Could you do this in one pass? 
//
// 
// Example 1: 
//
// 
//Input: head = [1,2,3,4,5], n = 2
//Output: [1,2,3,5]
// 
//
// Example 2: 
//
// 
//Input: head = [1], n = 1
//Output: []
// 
//
// Example 3: 
//
// 
//Input: head = [1,2], n = 1
//Output: [1]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the list is sz. 
// 1 <= sz <= 30 
// 0 <= Node.val <= 100 
// 1 <= n <= sz 
// 
// Related Topics Linked List Two Pointers 
// 👍 4678 👎 284

#include <iostream>
#include "list_node.h"
#include <vector>

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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
#define SOLUTION_2
#ifdef SOLUTION_1
        // 顺序容器存储所有结点的地址，并记录结点个数

        ListNode dummy_head(INT_MAX, head), *p1{&dummy_head};
        std::vector<ListNode *> vec;
        int pos{0};
        while (p1) {
            vec.emplace_back(p1);
            p1 = p1->next;
            ++pos;
        }
        // pos - n 是需要被删除的结点
        ListNode *pivot = vec[pos - n - 1];
        ListNode *deleted_node = pivot->next;
        pivot->next = pivot->next->next;
        delete deleted_node;
        return dummy_head.next;
#elif defined(SOLUTION_2)
        // 递归方式：使用cnt_in_记录进入函数的次数，使用cnt_out_记录退出函数的次数
        // 删除结点的位置主要分为两类：
        // 一类是位于首结点之后的结点，另一类是首结点位置

        if (!head) return head;
        ++cnt_in_;
        ListNode *p = removeNthFromEnd(head->next, n);
        // 退出函数的次数从1开始计数
        // 当n == cnt_out_时，说明当前递归的head是要被删除的结点
        // 如果当前要删除的结点是整个链表的首节点，那么就需要特殊处理
        if (n + 1 == cnt_out) {
            head->next = p->next;
            delete p;
        } else if (n == cnt_out && n == cnt_in_) {
            ListNode dummy_head(INT_MAX, head);
            dummy_head.next = head->next;
            delete head;
            return dummy_head.next;
        }
        ++cnt_out;
        return head;
#elif defined(SOLUTION_3)
        // 参考https://leetcode.com/problems/remove-nth-node-from-end-of-list/discuss/9059/0ms-recursive-solution
        // 进入递归递增深度，退出递归递减深度，递归刚开始返回时记录层数
        static int depth = 0, levels = 0;

        if (!head) {
            levels = depth;
            return nullptr;
        }
        depth++;
        // 通过返回不同的子结点链表，直接删除，手法更为巧妙
        head->next = removeNthFromEnd(head->next, n);
        depth--;
        if (levels - depth == n) {
            ListNode *next = head->next;
            delete head;
            return next;
        }
        return head;

#else
        // 前后双指针法

        // 创建一个虚拟头结点以便处理首结点
        ListNode dummy_head(INT_MAX, head), *cur{&dummy_head}, *last{dummy_head.next};
        // cur与last间距至少为1,根据n值推进后指针，保证前后指针间距就是n
        // 这样，当后指针遍历到最后一个结点时，前指针刚好指向要删除的结点的前一个位置
        for (int i = 1; i < n; ++i) last = last->next;
        while (last->next) {
            cur = cur->next;
            last = last->next;
        }
        ListNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        return dummy_head.next;
#endif

    }

private:
    int cnt_in_{0}, cnt_out{1};
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    ListNode *head = CreateList<ListNode>({1,2,3,4,5});
    std::cout << "init: " << head << std::endl;
    ListNode *result = Solution().removeNthFromEnd(head, 2);
    std::cout << "result: " << result << std::endl;
    return 0;
}
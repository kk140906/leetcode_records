//You are given the head of a singly linked-list. The list can be represented as
//:
//
//
//L0 → L1 → … → Ln - 1 → Ln
//
//
// Reorder the list to be on the following form:
//
//
//L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
//
//
// You may not modify the values in the list's nodes. Only nodes themselves may
//be changed.
//
//
// Example 1:
//
//
//Input: head = [1,2,3,4]
//Output: [1,4,2,3]
//
//
// Example 2:
//
//
//Input: head = [1,2,3,4,5]
//Output: [1,5,2,4,3]
//
//
//
// Constraints:
//
//
// The number of nodes in the list is in the range [1, 5 * 104].
// 1 <= Node.val <= 1000
//
// Related Topics 链表
// 👍 527 👎 0


#include<iostream>
#include <vector>
#include <list_node.h>

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
    void reorderList(ListNode *head) {

#define SOLUTION_1

#ifdef SOLUTION_1
        /**
         * 先找中点，然后翻转后半部分，最后归并
         */
        if (!head || !head->next) return;
        auto mid = find_middle_(head);
//        auto reversed = reverse_(mid);
        ListNode *reversed;
        reverse_dfs_(mid, reversed);
        merge_(head, reversed);
#elif defined(SOLUTION_2)
        /**
         * 先遍历所有结点，保存到vector中，然后直接操作vector进行排序
         */
        if (!head || !head->next) return;
        vector<ListNode *> v;
        dfs_(head, v);
        auto begin = v.begin(), end = v.end();
        while (begin < end) {
            auto temp = *begin;
            (*begin++)->next = *--end;
            temp->next->next = *begin;
        }
        (*end)->next = nullptr;
#else
        /**
         * 同方法2,下标实现
         */
        ListNode *p = head;
        std::vector<ListNode *> vec;
        while (p) {
            vec.emplace_back(p);
            p = p->next;
        }
        if (!vec.empty()) {
            int size = vec.size();
            for (int i = 0; i < size / 2; ++i) {
                vec[i]->next = vec[size - i - 1];
                vec[i]->next->next = vec[i + 1];
            }
            vec[size / 2]->next = nullptr;
        }
#endif
    }

private:
    ListNode *find_middle_(ListNode *head) {
        auto slow = head, fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            if (!fast || !fast->next) {
                auto temp = slow;
                slow = slow->next;
                temp->next = nullptr;
            } else { slow = slow->next; }
        }
        return slow;
    }

    ListNode *reverse_(ListNode *head) {
        ListNode *pre = nullptr;
        while (head) {
            auto temp = head->next;
            head->next = pre;
            pre = head;
            head = temp;
        }
        return pre;
    }

    ListNode *reverse_dfs_(ListNode *head, ListNode *&dummy_head) {
        if (!head || !head->next) {
            dummy_head = head;
            return head;
        }
        auto result = reverse_dfs_(head->next, dummy_head);
        result->next = head;
        head->next = nullptr;
        return head;
    }

    void merge_(ListNode *l1, ListNode *l2) {
        ListNode dummy_head{0, l1}, *prev{&dummy_head};
        while (l1 && l2) {
            prev = prev->next = l1;
            l1 = l1->next;
            prev = prev->next = l2;
            l2 = l2->next;
        }
        prev->next = l1 ? l1 : l2;
    }

    void dfs_(ListNode *head, vector<ListNode *> &v) {
        if (!head) return;
        v.emplace_back(head);
        dfs_(head->next, v);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    auto head = CreateList<ListNode>({1, 2, 3, 4});
    std::cout << head << std::endl;
    Solution solution;
    solution.reorderList(head);
    std::cout << head << std::endl;
    return 0;
}

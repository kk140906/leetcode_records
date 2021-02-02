//Merge two sorted linked lists and return it as a new sorted list. The new list
// should be made by splicing together the nodes of the first two lists. 
//
// 
// Example 1: 
//
// 
//Input: l1 = [1,2,4], l2 = [1,3,4]
//Output: [1,1,2,3,4,4]
// 
//
// Example 2: 
//
// 
//Input: l1 = [], l2 = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: l1 = [], l2 = [0]
//Output: [0]
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in both lists is in the range [0, 50]. 
// -100 <= Node.val <= 100 
// Both l1 and l2 are sorted in non-decreasing order. 
// 
// Related Topics Linked List 
// 👍 5349 👎 675
#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
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

    template<typename It_>
    ListNode *CreateList(It_ begin, It_ end) {
        ListNode *head = new ListNode, *tail = head;
        while (begin != end) {
            tail = tail->next = new ListNode(*begin++);
        }
        SetListType(ListType::Forward);
        return head->next;
    }

#define USING_STL

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
#ifdef USING_STL
        vector<int> vi;
        while (l1) {
            vi.emplace_back(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            vi.emplace_back(l2->val);
            l2 = l2->next;
        }
        sort(vi.begin(), vi.end());
        return CreateList(vi.begin(), vi.end());
#else
        ListNode *head = new ListNode();
        auto tail = head;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = new ListNode(l1->val);
                l1 = l1->next;
            } else {
                tail->next = new ListNode(l2->val);
                l2 = l2->next;
            }
            tail = tail->next;
        }
        while(l1) {
            tail->next = new ListNode(l1->val);
            l1 = l1->next;
        }
        while(l2) {
            tail->next = new ListNode(l2->val);
            l2 = l2->next;
        }
        return head->next;
#endif
    }
};
//leetcode submit region end(Prohibit modification and deletion)

int main() {
    auto head1 = CreateList({1, 2, 4, 5, 8, 9});
    auto head2 = CreateList({1, 3, 4});
    Solution solution;
    auto merged = solution.mergeTwoLists(head1, head2);
    cout << merged;
    return 0;
}
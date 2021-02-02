//Given a linked list, return the node where the cycle begins. If there is no cy
//cle, return null. 
//
// There is a cycle in a linked list if there is some node in the list that can 
//be reached again by continuously following the next pointer. Internally, pos is 
//used to denote the index of the node that tail's next pointer is connected to. N
//ote that pos is not passed as a parameter. 
//
// Notice that you should not modify the linked list. 
//
// 
// Example 1: 
//
// 
//Input: head = [3,2,0,-4], pos = 1
//Output: tail connects to node index 1
//Explanation: There is a cycle in the linked list, where tail connects to the s
//econd node.
// 
//
// Example 2: 
//
// 
//Input: head = [1,2], pos = 0
//Output: tail connects to node index 0
//Explanation: There is a cycle in the linked list, where tail connects to the f
//irst node.
// 
//
// Example 3: 
//
// 
//Input: head = [1], pos = -1
//Output: no cycle
//Explanation: There is no cycle in the linked list.
// 
//
// 
// Constraints: 
//
// 
// The number of the nodes in the list is in the range [0, 104]. 
// -105 <= Node.val <= 105 
// pos is -1 or a valid index in the linked-list. 
// 
//
// 
// Follow up: Can you solve it using O(1) (i.e. constant) memory? 
// Related Topics Linked List Two Pointers 
// 👍 3414 👎 261


#include <unordered_set>
#include <string>
#include <iostream>
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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
#ifdef USING_STL
        if (!head || !head->next) { return nullptr; }
        unordered_set<ListNode *> linked_list_set;
        ListNode *tail = head;
        while (tail->next) {
            if (linked_list_set.count(tail->next) == 1) {
                return tail->next;
            }
            linked_list_set.insert(tail);
            tail = tail->next;
        }
        return nullptr;
#else
        if (!head || !head->next) { return nullptr; }
        ListNode *fast, *slow, *entry;
        fast = slow = entry = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                while (slow != entry) {               // found the entry location
                    slow = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return nullptr;
#endif
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main() {
    CycleLinkedList cycle_linked_list({3, 2, 1, 4}, 1);
    auto head = cycle_linked_list.Creat();
    Solution solution;
    if (auto result = solution.detectCycle(head->next)) {
        cout << result->val << endl;
    } else {
        cout << "没有找到环" << endl;
    }
    return 0;
}
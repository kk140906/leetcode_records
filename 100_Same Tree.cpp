//Given the roots of two binary trees p and q, write a function to check if they
// are the same or not. 
//
// Two binary trees are considered the same if they are structurally identical, 
//and the nodes have the same value. 
//
// 
// Example 1: 
//
// 
//Input: p = [1,2,3], q = [1,2,3]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: p = [1,2], q = [1,null,2]
//Output: false
// 
//
// Example 3: 
//
// 
//Input: p = [1,2,1], q = [1,1,2]
//Output: false
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in both trees is in the range [0, 100]. 
// -104 <= Node.val <= 104 
// 
// Related Topics 树 深度优先搜索 
// 👍 576 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <queue>

using namespace std;
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
#ifdef  SOLUTION_1
        // DFS
        if (!p || !q) return p == q;
        if (p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
#else
        // BFS,入队所有结点，包括nullptr
        if (!p || !q) return p == q;
        queue<TreeNode *> Q1, Q2;
        Q1.push(p);
        Q2.push(q);
        while (!Q1.empty() && !Q2.empty()) {
            auto front_p = Q1.front();
            auto front_q = Q2.front();
            // 只有两个队首都是空或者都不空两个结点相同
            if (!front_p ^ !front_q) return false;
            // 如果队首都是空，那么直接出队
            if (!front_p) {
                Q1.pop();
                Q2.pop();
                continue;
            }
            // 如果队首非空，那么比较值是否相同
            if (front_p->val != front_q->val) return false;
            Q1.pop();
            Q1.push(front_p->left);
            Q1.push(front_p->right);
            Q2.pop();
            Q2.push(front_q->left);
            Q2.push(front_q->right);
        }
        return true;
#endif
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    auto tree_p1 = BinaryTree({"1", "2", "3"});
    auto tree_q1 = BinaryTree({"1", "2", "3"});
    auto tree_p2 = BinaryTree({"1", "2"});
    auto tree_q2 = BinaryTree({"1", "null", "3"});
    auto tree_p3 = BinaryTree({"1", "2", "1"});
    auto tree_q3 = BinaryTree({"1", "1", "2"});

    START_TIMESTAMP(tag);
    Solution solution;
    std::cout << std::boolalpha
              << solution.isSameTree(tree_p1.Root(), tree_p1.Root())
              << std::endl
              << solution.isSameTree(tree_p2.Root(), tree_q2.Root())
              << std::endl
              << solution.isSameTree(tree_p3.Root(), tree_q3.Root());
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
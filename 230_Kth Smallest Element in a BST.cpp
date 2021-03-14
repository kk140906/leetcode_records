//Given the root of a binary search tree, and an integer k, return the kth (1-in
//dexed) smallest element in the tree. 
//
// 
// Example 1: 
//
// 
//Input: root = [3,1,4,null,2], k = 1
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: root = [5,3,6,2,4,null,null,1], k = 3
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is n. 
// 1 <= k <= n <= 104 
// 0 <= Node.val <= 104 
// 
//
// 
//Follow up: If the BST is modified often (i.e., we can do insert and delete ope
//rations) and you need to find the kth smallest frequently, how would you optimiz
//e? Related Topics 树 二分查找 
// 👍 364 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>

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
    int kthSmallest(TreeNode *root, int k) {
        /**
         * DFS: 中序遍历就是有序的，直接统计遍历到第 k 个结点，后面的就没必要继续遍历了
         */
#ifdef SOLUTION_1
        int val;
        inorder(root, k, val);
        return val;
#else
        stack<TreeNode *> s;
        int i = 0;
        for (;;) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            if (++i == k) return root->val;
            root = root->right;
        }
#endif
    }

    void inorder(TreeNode *root, int k, int &val) {
        if (!root) return;
        inorder(root->left, k, val);
        if (++index == k) val = root->val; // 找到了就直接退出
        else inorder(root->right, k, val);
    }

private:
    int index{0};
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {

    auto tree = BinaryTree{"3", "1", "4", "null", "2"};

    Solution solution;

    cout << solution.kthSmallest(tree.Root(), 1);

    int running_times = 1000;
    START_TIMESTAMP(tag);
    for (int i = 0; i < running_times; ++i) {
        /** 
         * critical test code
         */

    }
    END_TIMESTAMP(tag);
    cout << "\nprogram running time: "
         << DURATION_TIME(tag, common::microseconds) / running_times
         << " ms\n";
    return 0;
}
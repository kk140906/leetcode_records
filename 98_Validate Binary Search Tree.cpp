//Given the root of a binary tree, determine if it is a valid binary search tree
// (BST). 
//
// A valid BST is defined as follows: 
//
// 
// The left subtree of a node contains only nodes with keys less than the node's
// key. 
// The right subtree of a node contains only nodes with keys greater than the no
//de's key. 
// Both the left and right subtrees must also be binary search trees. 
// 
//
// 
// Example 1: 
//
// 
//Input: root = [2,1,3]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [5,1,4,null,null,3,6]
//Output: false
//Explanation: The root node's value is 5 but its right child's value is 4.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 104]. 
// -231 <= Node.val <= 231 - 1 
// 
// Related Topics 树 深度优先搜索 递归 
// 👍 946 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <algorithm>
#include <queue>
#include <tuple>

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
    bool isValidBST(TreeNode *root) {
#define SOLUTION_1
#ifdef SOLUTION_1
        /**
         * DFS:中序遍历
         * 根据二叉查找树的性质，左子树 < 根结点 < 右子树
         * 从这个比较顺序可以看出，中序遍历的结果就是这个比较顺序
         * 那么如果中序遍历的结果是升序的，则说明二叉树是二叉查找树
         */
        return in_order_(root);
#else
        /**
         * BFS: BFS的关键是如何更新结点允许的上界和下界
         * 创建一个队列，队列内的元素类型是(根结点，最小值，最大值)
         * 每次结点入队的时候都更新结点的范围
         * 根结点入队的时候设定最小值为LLONG_MIN，最大值为LLONG_MAX
         * 设定为long long类型是由于测试案例卡了int类型的边界值
         * 对于根结点的左子树结点，最小值为上一次入队的最小值，最大值则是根结点的值
         * 对于根结点的右子树结点，最小值为根结点的值，最大值为上一次入队的最大值
         */

        queue<tuple<TreeNode *, long long, long long>> Q;
        Q.push({root, LLONG_MIN, LLONG_MAX});
        while (!Q.empty()) {
            auto front = Q.front();
            auto node = get<0>(front);
            auto min = get<1>(front);
            auto max = get<2>(front);
            Q.pop();
            if (node->val <= min || node->val >= max) return false;
            if (node->left) Q.push({node->left, min, node->val});
            if (node->right) Q.push({node->right, node->val, max});
        }
        return true;
#endif
    }

private:
    long long prev{LLONG_MIN};

    bool in_order_(TreeNode *root) {
        if (!root) return true;
        auto left = in_order_(root->left);
        if (root->val <= prev) return false;
        prev = root->val;
        auto right = in_order_(root->right);
        return left && right;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {

    auto tree1 = BinaryTree({"2147483647"});
    auto tree2 = BinaryTree({"-2147483648"});
    Solution solution;
    START_TIMESTAMP(tag);
    std::cout << std::boolalpha
              << solution.isValidBST(tree1.Root())
              << std::endl
              << solution.isValidBST(tree2.Root());
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
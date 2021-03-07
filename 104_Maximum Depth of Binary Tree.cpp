//Given the root of a binary tree, return its maximum depth. 
//
// A binary tree's maximum depth is the number of nodes along the longest path f
//rom the root node down to the farthest leaf node. 
//
// 
// Example 1: 
//
// 
//Input: root = [3,9,20,null,null,15,7]
//Output: 3
// 
//
// Example 2: 
//
// 
//Input: root = [1,null,2]
//Output: 2
// 
//
// Example 3: 
//
// 
//Input: root = []
//Output: 0
// 
//
// Example 4: 
//
// 
//Input: root = [0]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 104]. 
// -100 <= Node.val <= 100 
// Related Topics 树 深度优先搜索 递归 
// 👍 815 👎 0

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
    int maxDepth(TreeNode *root) {
#define SOLUTION_1
#ifdef SOLUTION_1
        /**
         * DFS,递归的时候更新层数，
         * 当递归开始退出的时候就说明当前子树的层数已经更新完毕，把层数返回即可，
         * 最终把左右子树层数的最大值作为层数返回就是最大深度了
         */
        return dfs_(root, 0);
#else
        /**
         * BFS,入队的时候把层数一起入队，每次循环更新depth即可；
         */

        if (!root) return 0;
        queue<pair<TreeNode *, int>> q;
        q.push({root, 1});
        int depth{0};
        while (!q.empty()) {
            auto front = q.front();
            auto node = front.first;
            auto level = front.second;
            q.pop();
            if (!node) continue;
            q.push({node->left, level + 1});
            q.push({node->right, level + 1});
            depth = level;
        }
        return depth;
#endif
    }

private:
    int dfs_(TreeNode *root, int level) {
        if (!root) return level;
        auto left = dfs_(root->left, level + 1);
        auto right = dfs_(root->right, level + 1);
        return max(left, right);
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    auto tree = BinaryTree({"3", "9", "20", "null", "null", "15", "7"});
    Solution solution;
    START_TIMESTAMP(tag);
    std::cout << solution.maxDepth(tree.Root());
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
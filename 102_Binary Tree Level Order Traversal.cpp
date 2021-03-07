//Given the root of a binary tree, return the level order traversal of its nodes
//' values. (i.e., from left to right, level by level). 
//
// 
// Example 1: 
//
// 
//Input: root = [3,9,20,null,null,15,7]
//Output: [[3],[9,20],[15,7]]
// 
//
// Example 2: 
//
// 
//Input: root = [1]
//Output: [[1]]
// 
//
// Example 3: 
//
// 
//Input: root = []
//Output: []
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [0, 2000]. 
// -1000 <= Node.val <= 1000 
// 
// Related Topics 树 广度优先搜索 
// 👍 798 👎 0

#include <iostream>
#include <common.h>
#include <queue>
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
    vector<vector<int>> levelOrder(TreeNode *root) {
#define SOLUTION_1
#ifdef SOLUTION_1
        /**
         * DFS,将容器及层数随着递归进行更新
         * 无论是前序、中序还是后序，我们都是先遍历左子树，后遍历右子树，
         * 因此我们可以采用任何方式对整个二叉树进行遍历
         * 在存储的时候根据层数将数据存储到对应的位置即可
         */
        vector<vector<int>> v;
        dfs_(root, v, 0);
        return v;
#else
        /**
         * BFS 将结点和所属层数一起入队，这样层数就是vector的索引
         * 需要注意的是每一行第一个结点需要先通过push_back创建一个空的对象
         * 这样可以保证通过索引访问vector的方法是合法的。
         */
        if (!root) return {};

        queue<pair<TreeNode *, int>> q;
        q.push({root, 0});
        vector<vector<int>> v;

        while (!q.empty()) {
            auto front = q.front();
            auto node = front.first;
            auto level = front.second;
            q.pop();
            if (!node) continue;
            q.push({node->left, level + 1});
            q.push({node->right, level + 1});
            if (v.size() < level + 1) v.emplace_back();
            v[level].emplace_back(node->val);
        }
        return v;
#endif
    }

private:
    void dfs_(TreeNode *root, vector<vector<int>> &v, int level) {
        if (!root) return;
        if (v.size() < level + 1) v.emplace_back();
        v[level].emplace_back(root->val);
        dfs_(root->left, v, level + 1);
        dfs_(root->right, v, level + 1);
    }
};

//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {

    auto tree = BinaryTree({});
    START_TIMESTAMP(tag);
    Solution().levelOrder(tree.Root());
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
//Given the root of a binary tree, check whether it is a mirror of itself (i.e.,
// symmetric around its center). 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,2,3,4,4,3]
//Output: true
// 
//
// Example 2: 
//
// 
//Input: root = [1,2,2,null,3,null,3]
//Output: false
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 1000]. 
// -100 <= Node.val <= 100 
// 
//
// 
//Follow up: Could you solve it both recursively and iteratively? Related Topics
// 树 深度优先搜索 广度优先搜索 
// 👍 1271 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <deque>

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
    bool isSymmetric(TreeNode *root) {
#define SOLUTION_2

#ifdef SOLUTION_1
        /**
         * DFS:两次遍历并存储遍历的结果，最后比较结果是否相同
         * 第一次遍历按照前序遍历，根结点 --> 左子树 --> 右子树
         * 第二次调整前序遍历的左右子树的遍历顺序，根结点 --> 右子树 --> 左子树
         */
        if (!root) return true;
        vector<int> v1, v2;
        traversal_(root, v1);
        traversal_(root, v2, false);
        return v1 == v2;
#elif defined(SOLUTION_2)
        /**
         * DFS:一次遍历，同时遍历比较左子树和右子树
         * 首先对左子树的左子树和右子树的右子树进行第一次比较
         * 然后对左子树的右子树和右子树的左子树进行第二次比较
         * 两次比较的结果作为最终的比较结果
         */
        if (!root) return true;
        return compare_(root->left, root->right);
#else
        /**
         * BFS:利用双端队列
         * 入队的顺序先是左子树的左子树，然后右子树的右子树,
         * 紧接着就是左子树的右子树，右子树的左子树
         * 这样队列的前两个就是要比较的值，相等则弹出前两个数据，然后继续比较
         * 不等则说明树非对称
         */
        if (!root) return true;
        deque<TreeNode *> D;
        D.push_back(root->left);
        D.push_back(root->right);
        while (!D.empty()) {
            auto first = D[0];
            auto second = D[1];

            if (!first ^ !second) return first == second;
            // 两个空结点，直接弹出
            if (!first) {
                D.pop_front();
                D.pop_front();
                continue;
            }
            if (first->val != second->val) return false;

            D.pop_front();
            D.pop_front();
            D.push_back(first->left);
            D.push_back(second->right);
            D.push_back(first->right);
            D.push_back(second->left);
        }
        return true;
#endif
    }

private:
    void traversal_(TreeNode *root, vector<int> &v, bool direction = true) {
        if (!root) {
            v.emplace_back(101);
            return;
        }
        v.emplace_back(root->val);
        if (direction) {
            traversal_(root->left, v);
            traversal_(root->right, v);
        } else {
            traversal_(root->right, v, false);
            traversal_(root->left, v, false);
        }
    }

    bool compare_(TreeNode *left, TreeNode *right) {
        if (!left || !right) return left == right;
        if (left->val != right->val) return false;
        return compare_(left->left, right->right) && compare_(left->right, right->left);
    }
};
//leetcode submit region end(Prohibit modification and  deletion)


int main(int argc, char **argv) {
    auto tree1 = BinaryTree({"2", "3", "3", "4", "5", "null", "4"});
    auto tree2 = BinaryTree({"1", "2", "2", "3", "4", "4", "3"});
    auto tree3 = BinaryTree({"1", "2", "2", "null", "3", "null", "3"});
    Solution solution;
    START_TIMESTAMP(tag);
    std::cout << std::boolalpha
              << solution.isSymmetric(tree1.Root())
              << std::endl
              << solution.isSymmetric(tree2.Root())
              << std::endl
              << solution.isSymmetric(tree3.Root())
              << std::endl;
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
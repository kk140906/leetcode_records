//Given the root of a binary tree, return the postorder traversal of its nodes' 
//values. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,null,2,3]
//Output: [3,2,1]
// 
//
// Example 2: 
//
// 
//Input: root = []
//Output: []
// 
//
// Example 3: 
//
// 
//Input: root = [1]
//Output: [1]
// 
//
// Example 4: 
//
// 
//Input: root = [1,2]
//Output: [2,1]
// 
//
// Example 5: 
//
// 
//Input: root = [1,null,2]
//Output: [2,1]
// 
//
// 
// Constraints: 
//
// 
// The number of the nodes in the tree is in the range [0, 100]. 
// -100 <= Node.val <= 100 
// 
//
// 
//
// Follow up: 
//
// Recursive solution is trivial, could you do it iteratively? 
//
// 
// Related Topics 栈 树 
// 👍 535 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <stack>

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
    vector<int> postorderTraversal(TreeNode *root) {

#ifdef SOLUTION_1
        vector<int> v;
        recursive_(root, v);
        return v;
#elif defined(SOLUTION_2)
        /**
         * 前序遍历反转：
         * 后序遍历的顺序：左子树 --> 右子树 --> 根结点.
         * 前序遍历的顺序为:根结点 --> 左子树 --> 右子树.
         * 那么将前序遍历调整为:根结点 --> 右子树 --> 左子树,反转即可得到后序遍历的结果
         * 由于入栈顺序与出栈顺序相反，因此实际的入栈顺序应该为 左子树 --> 右子树
         */
        if (!root) return {};
        vector<int> v;
        stack<TreeNode *> S;
        S.push(root);
        while (!S.empty()) {
            root = S.top();
            v.emplace_back(root->val);
            S.pop();

            if (root->left) S.push(root->left);
            if (root->right) S.push(root->right);
        }
        reverse(v.begin(), v.end());
        return v;

#elif defined(SOLUTION_3)
        /**
         * DFS非递归遍历 nullptr标记法：
         * DFS遍历，非递归遍历记录结果其实是当该结点作为子树的根结点时才记录的
         * nullptr标记法是在入栈根结点之后再入栈一个nullptr的空指针作为标记
         * 当栈顶为空则表明下一个结点就是根结点，就是我们需要的结果
         * 入栈的顺序决定了出栈的顺序，也就是说入栈的顺序决定了最终的结果
         * 二叉树的后序遍历顺序为：左子树 --> 右子树 --> 根结点
         * 而栈的特性是后入先出，因此入栈的顺序应为 根结点 --> 右子树 --> 左子树
         */
        if (!root) return {};
        vector<int> v;
        stack<TreeNode *> S;
        S.push(root);
        TreeNode *top = root, flag;
        while (!S.empty()) {
            top = S.top();
            if (top) {
                S.pop(); // 弹出重复的结点

                S.push(top); // 根结点入栈
                S.push(nullptr); // nullptr标记要处理的根结点

                if (top->right) S.push(top->right); // 右子结点入栈
                if (top->left) S.push(top->left); // 左子结点入栈
                continue;
            }
            S.pop();
            v.emplace_back(S.top()->val);
            S.pop();
        }
        return v;
#else
        /**
         * 迭代，set标记法:
         * 首先遍历左子树，将其所有结点压入栈中
         * 当遍历到没有左子树后，获取当前栈顶的结点，
         * 检查当前结点是否已经遍历过，遍历过则从栈中弹出，并将结果记录到vector
         * 如果当前结点没有遍历过，那么就将其加入set中，继续遍历右子树
         */
        if (!root) return {};

        vector<int> v;
        stack<TreeNode *> S;
        unordered_set<TreeNode *> seen;

        while (root || !S.empty()) {
            if (root) {
                S.push(root);
                root = root->left;
                continue;
            }

            auto top = S.top();

            if (seen.count(top)) {
                S.pop();
                v.emplace_back(top->val);
                continue;
            }

            seen.insert(top);
            root = top->right;

        }
        return v;
#endif
    }

private:
    void recursive_(TreeNode *root, vector<int> &v) {
        if (!root) return;
        recursive_(root->left, v);
        recursive_(root->right, v);
        v.emplace_back(root->val);
    }
};



//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    auto tree = BinaryTree({"1", "3", "2", "4", "5", "3"});
    START_TIMESTAMP(tag);
    auto v = Solution().postorderTraversal(tree.Root());
    for (const auto &cl : v) {
        std::cout << cl << std::endl;
    }
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
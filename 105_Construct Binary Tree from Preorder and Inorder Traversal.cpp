//Given two integer arrays preorder and inorder where preorder is the preorder t
//raversal of a binary tree and inorder is the inorder traversal of the same tree,
// construct and return the binary tree. 
//
// 
// Example 1: 
//
// 
//Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
//Output: [3,9,20,null,null,15,7]
// 
//
// Example 2: 
//
// 
//Input: preorder = [-1], inorder = [-1]
//Output: [-1]
// 
//
// 
// Constraints: 
//
// 
// 1 <= preorder.length <= 3000 
// inorder.length == preorder.length 
// -3000 <= preorder[i], inorder[i] <= 3000 
// preorder and inorder consist of unique values. 
// Each value of inorder also appears in preorder.
// preorder is guaranteed to be the preorder traversal of the tree. 
// inorder is guaranteed to be the inorder traversal of the tree. 
// 
// Related Topics 树 深度优先搜索 数组 
// 👍 908 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <unordered_map>


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
    using It_ = vector<int>::iterator;

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {

#ifdef SOLUTION_1
        return build(preorder.begin(),preorder.end(),inorder.begin(),inorder.end());
#else
        auto beg = inorder.begin();
        unordered_map<int, TreeNode *> M;
        TreeNode dummy_root, *prev = &dummy_root;
        bool right = false;
        for (const auto &v : preorder) {
            auto cur = new TreeNode(v);
            M[v] = cur;
            if (right) {
                prev->right = cur;
                right = false;
            } else {
                prev->left = cur;
            }
            prev = cur;

            while (v == *beg || M.count(*beg)) {
                right = true;
                prev = M[*beg];
                if (++beg == inorder.end()) break;
            }
        }
        return dummy_root.left;
#endif
    }
    TreeNode *build(It_ p1, It_ p2, It_ i1, It_ i2) {
        if (p1 == p2 || i1 == i2) return nullptr;
        int root_value = *p1;
        auto root = new TreeNode(root_value);
        auto mid = find(i1,i2,root_value);
        auto dist = distance(i1,mid);
        root->left = build(p1 + 1, p1 + dist + 1,i1,mid);
        root->right = build(p1+ dist + 1,p2,mid + 1,i2);
        return root;
    }

};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {
    vector<int> preorder{3,9,20,15,7}, inorder{9,3,15,20,7};
    Solution solution;
    START_TIMESTAMP(tag);
    auto root = solution.buildTree(preorder, inorder);
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
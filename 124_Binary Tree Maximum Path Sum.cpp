//A path in a binary tree is a sequence of nodes where each pair of adjacent nod
//es in the sequence has an edge connecting them. A node can only appear in the se
//quence at most once. Note that the path does not need to pass through the root. 
//
//
// The path sum of a path is the sum of the node's values in the path. 
//
// Given the root of a binary tree, return the maximum path sum of any path. 
//
// 
// Example 1: 
//
// 
//Input: root = [1,2,3]
//Output: 6
//Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
//
// 
//
// Example 2: 
//
// 
//Input: root = [-10,9,20,null,null,15,7]
//Output: 42
//Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 
//= 42.
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 3 * 104]. 
// -1000 <= Node.val <= 1000 
// 
// Related Topics 树 深度优先搜索 递归 
// 👍 932 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <algorithm>

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
    int maxPathSum(TreeNode *root) {
        /**
         *     10
         *    /  \
         *   9    1
         *  / \
         * 2   3
         * 要求最大路径和首先要确定保证和最大的路径，路径的选取本质上就是贪心，以保证路径上的元素都尽可能大，尽可能多
         * 对于一个单独的子结点，其路径只有6条:
         * 1、根结点 --> 左子树结点;
         * 2、根结点 --> 右子树结点;
         * 3、左子树结点 --> 根结点 --> 右子树结点;
         * 4、单独的根结点;
         * 5、单独的左子树结点;
         * 6、单独的右子树结点;
         * 那么对于最大路径和则需要在上面6条路径中进行选取；
         * 如果该子结点的根结点作为树中某个其他路径中的一个子结点，
         * 那么该根结点后的对应路径只能选择第1、2、4条路径中的某一条路径。
         *
         * 根据贪心的思路，如果左子树和右子树都小于0，那么则只能第4条路径，
         * 如果左子树和右子树至少其中一个大于0则说明存在对总和有增益的路径，
         * 因此选择第1、2中构成总和最大的路径
         *
         */

#ifdef SOLUTION_1
        vector<int> sum;
        dfs_(root, sum);
        return *max_element(sum.begin(), sum.end());
#else
        int sum{INT_MIN};
        maxGain(root, sum);
        return sum;
#endif
    }

private:
    int maxGain(TreeNode *root, int &sum) {
        if (!root) return 0;
        int left = max(maxGain(root->left, sum), 0);
        int right = max(maxGain(root->right, sum), 0);
        int gain = max(root->val + left, root->val + right);
        sum = max(sum, root->val + left + right);
        return gain;
    }


    int dfs_(TreeNode *root, vector<int> &result) {
        // 叶子结点
        if (!root->left && !root->right) {
            result.emplace_back(root->val);
            return root->val;
        }
        int left = root->left ? dfs_(root->left, result) : -1500;
        int right = root->right ? dfs_(root->right, result) : -1500;
        int two_sum = root->val + max(left, right);
        int tri_sum = root->val + left + right;
        vector<int> v{root->val, two_sum, left, right, tri_sum};
        int max_sum = *max_element(v.begin(), v.end());
        result.emplace_back(max_sum);
        // 作为其他路径的子结点则在根结点和左右子树中选择路径
        if (max_sum == tri_sum || max_sum == left || max_sum == right)
            return max(root->val, two_sum);
        return max_sum;
    }
};
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {

    auto tree = BinaryTree({"0", "-1", "0", "0", "0", "-2", "3", "0", "4"});
    Solution solution;
    START_TIMESTAMP(tag);
    cout << solution.maxPathSum(tree.Root());
    END_TIMESTAMP(tag);
    DURATION_TIME(tag, common::microseconds);
    return 0;
}
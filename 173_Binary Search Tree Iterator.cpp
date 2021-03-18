//Implement the BSTIterator class that represents an iterator over the in-order 
//traversal of a binary search tree (BST): 
//
// 
// BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. Th
//e root of the BST is given as part of the constructor. The pointer should be ini
//tialized to a non-existent number smaller than any element in the BST. 
// boolean hasNext() Returns true if there exists a number in the traversal to t
//he right of the pointer, otherwise returns false. 
// int next() Moves the pointer to the right, then returns the number at the poi
//nter. 
// 
//
// Notice that by initializing the pointer to a non-existent smallest number, th
//e first call to next() will return the smallest element in the BST. 
//
// You may assume that next() calls will always be valid. That is, there will be
// at least a next number in the in-order traversal when next() is called. 
//
// 
// Example 1: 
//
// 
//Input
//["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext
//", "next", "hasNext"]
//[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
//Output
//[null, 3, 7, true, 9, true, 15, true, 20, false]
//
//Explanation
//BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
//bSTIterator.next();    // return 3
//bSTIterator.next();    // return 7
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 9
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 15
//bSTIterator.hasNext(); // return True
//bSTIterator.next();    // return 20
//bSTIterator.hasNext(); // return False
// 
//
// 
// Constraints: 
//
// 
// The number of nodes in the tree is in the range [1, 105]. 
// 0 <= Node.val <= 106 
// At most 105 calls will be made to hasNext, and next. 
// 
//
// 
// Follow up: 
//
// 
// Could you implement next() and hasNext() to run in average O(1) time and use 
//O(h) memory, where h is the height of the tree? 
// 
// Related Topics 栈 树 设计 
// 👍 340 👎 0

#include <iostream>
#include <common.h>
#include <tree_node.h>
#include <cassert>
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
class BSTIterator {
    /**
     * 使用vector保存中序遍历的所有结点数据，O(n)的空间复杂度，与题目要求O(h)的空间复杂度不太相符
     * 使用栈可以使最大空间复杂度为O(h)，反复查找最左侧点结点的平均时间复杂度是O(1)
     */
public:
    BSTIterator(TreeNode *root) {
#ifdef SOLUTION_1
        inorder_(root);
        it_ = v_.begin();
#else
        find_most_left_(root);
        get_next_();
#endif
    }

    int next() {
#ifdef SOLUTION_1
        assert(hasNext());
        return (*it_++)->val;
#else
        int value = next_->val;
        if (next_->right)
            find_most_left_(next_->right);
        get_next_();
        return value;
#endif
    }

    bool hasNext() {
#ifdef SOLUTION_1
        return it_ != v_.end();
#else
        return next_ != nullptr;
#endif
    }

private:
    vector<TreeNode *> v_;
    vector<TreeNode *>::iterator it_{nullptr};
    stack<TreeNode *> s_;
    TreeNode *next_{nullptr};

    void find_most_left_(TreeNode *root) {
        if (!root) return;
        s_.push(root);
        while (root->left) {
            s_.push(root->left);
            root = root->left;
        }
    }

    void get_next_() {
        next_ = nullptr;
        if (!s_.empty()) {
            next_ = s_.top();
            s_.pop();
        }
    }

    void inorder_(TreeNode *root) {
        if (!root) return;
        inorder_(root->left);
        v_.emplace_back(root);
        inorder_(root->right);
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
//leetcode submit region end(Prohibit modification and deletion)


int main(int argc, char **argv) {

    auto tree = BinaryTree({"7", "3", "15", "null", "null", "9", "20"});
    BSTIterator bst(tree.Root());
    bst.next();
    bst.next();
    bst.hasNext();
    bst.next();
    bst.hasNext();
    bst.next();
    bst.hasNext();
    bst.next();
    bst.hasNext();
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
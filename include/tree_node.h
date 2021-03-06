//
// Created by KK on 2021/2/16.
//

#ifndef LEETCODE_TREE_NODE_H
#define LEETCODE_TREE_NODE_H

#include <string>
#include <initializer_list>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BinaryTree {
public:
    BinaryTree(const std::initializer_list<std::string> &il) {
        root_ = initial_(il, 0);
    }

    TreeNode *Root() { return root_; }

private:
    TreeNode *root_;

    TreeNode *initial_(const std::initializer_list<std::string> &il, int index) {
        auto begin = il.begin();
        if (begin + index >= il.end()) return nullptr;
        std::string value = *(begin + index);
        if ("null" == value) return nullptr;
        auto *node = new TreeNode(strtol(value.c_str(), nullptr, 0));
        node->left = initial_(il, 2 * index + 1);
        node->right = initial_(il, 2 * index + 2);
        return node;
    }
};

#endif //LEETCODE_TREE_NODE_H

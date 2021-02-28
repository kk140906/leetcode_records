//
// Created by KK on 2021/2/16.
//

#ifndef LEETCODE_TREE_NODE_H
#define LEETCODE_TREE_NODE_H

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif //LEETCODE_TREE_NODE_H

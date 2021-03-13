//
// Created by KK on 2021/2/16.
//

#ifndef LEETCODE_TREE_NODE_H
#define LEETCODE_TREE_NODE_H

#include <string>
#include <initializer_list>
#include <queue>

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
//        root_ = initial_(il, 0);
        std::queue<TreeNode *> q;
        auto begin = il.begin(), end = il.end();
        if (il.size() != 0) {
            root_ = new TreeNode(strtol(begin++->c_str(), nullptr, 0));
            q.push(root_);
            while (begin < end) {
                auto front = q.front();
                q.pop();
                if (!front) continue;
                TreeNode *trees[2];
                for (auto &tree : trees) {
                    tree = nullptr;
                    if (begin < end)
                        tree = "null" == *begin ? nullptr :
                               new TreeNode(strtol(begin->c_str(), nullptr, 0));
                    begin++;
                }
                q.push(trees[0]);
                q.push(trees[1]);
                front->left = trees[0];
                front->right = trees[1];
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, BinaryTree &rhs) {
        auto level = rhs.get_levels(rhs.root_);
        int level_nodes = pow(2, level - 1);
        int char_cnt = 5 * level_nodes + level_nodes - 1;
        std::cout << std::string(char_cnt / 2, ' ') << rhs.root_->val << std::endl;
        std::queue<TreeNode *> q;
        q.push(rhs.root_);
        while (!q.empty()) {
//            auto n = q.size();
//            for(int i = 0; i < n; ++i) {
//                auto
//            }
        }
    }

    TreeNode *Root() { return root_; }

private:
    TreeNode *root_;

    int get_levels(TreeNode *root) {
        if (!root) return 0;
        return std::max(get_levels(root->left), get_levels(root->right)) + 1;
    }

    TreeNode *initial_(const std::initializer_list<std::string> &il, int index) {
        auto begin = il.begin();
        if (begin + index >= il.end()) return nullptr;
        std::string value = *(begin + index);
        if ("null" == value) return nullptr;
        auto *node = new TreeNode();
        node->left = initial_(il, 2 * index + 1);
        node->right = initial_(il, 2 * index + 2);
        return node;
    }

};

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
};


#endif //LEETCODE_TREE_NODE_H

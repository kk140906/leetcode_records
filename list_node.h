//
// Created by KK on 2020/11/20.
//

#ifndef LEETCODE_LIST_NODE_H
#define LEETCODE_LIST_NODE_H

#include <iostream>
#include <initializer_list>
#include <utility>
#include <vector>

enum ListType {
    Forward, Binary
} list_type_;

void SetListType(ListType &&t) {
    list_type_ = t;
}

/**
 * @brief 获取链表类型
 * @return
 */
std::string GetListType() {
    switch (list_type_) {
        case ListType::Forward:
            return " =====> ";
        case ListType::Binary:
            return " <====> ";
        default:
            return "";
    }
}

struct Node {
    int val{};
    Node *prev = nullptr;
    Node *next = nullptr;
    Node *child = nullptr;
    Node *random = nullptr;

    Node() = default;

    explicit Node(int val_) : val(val_) {}

};


struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * @brief 尾插法创建正向链表
 * @param il
 * @return
 */
template<typename T_>
T_ *CreateList(const std::initializer_list<int> &il) {
    T_ *head = new T_, *tail = head;
    for (const auto &cil : il) {
        auto node = new T_;
        node->val = cil;
        tail = tail->next = node;
    }
    SetListType(ListType::Forward);
    return head->next;
}

/**
 * @brief 头插法创建反向链表
 * @param il
 * @return
 */
ListNode *CreateReverseList(const std::initializer_list<int> &il) {
    ListNode *head = nullptr;
    for (const auto &cil : il) {
        auto tail = new ListNode(cil);
        tail->next = head;
        head = tail;
    }
    SetListType(ListType::Forward);
    return head;
}

/**
 * @brief 迭代器尾插法创建正向链表
 * @tparam It_
 * @param begin
 * @param end
 * @return
 */
template<typename It_>
ListNode *CreateList(It_ begin, It_ end) {
    ListNode *head = new ListNode, *tail = head;
    while (begin != end) {
        tail = tail->next = new ListNode(*begin++);
    }
    SetListType(ListType::Forward);
    return head->next;
}

/**
 * @brief 迭代器头插法创建反向链表
 * @tparam It_
 * @param begin
 * @param end
 * @return
 */

template<typename It_>
ListNode *CreateReverseList(It_ begin, It_ end) {
    ListNode *head = nullptr;
    while (begin != end) {
        auto tail = new ListNode(*begin++);
        tail->next = head;
        head = tail;
    }
    SetListType(ListType::Forward);
    return head;
}

/**
 * @brief 链表打印
 * @tparam T_
 * @param os
 * @param rhs
 * @return
 */
template<typename T_>
std::enable_if_t<std::is_same<Node, T_>::value ||
                 std::is_same<ListNode, T_>::value,
        std::ostream &> operator<<(std::ostream &os, T_ *rhs) {
    while (rhs) {
        os << rhs->val;
        rhs = rhs->next;
        if (rhs) os << GetListType();
    }
    return os;
}

/**
 * @brief 创建带有环的链表
 */
class CycleLinkedList {
public:
    CycleLinkedList(std::vector<int> vi, int pos) : elements(std::move(vi)), cycle_pos(pos) {
        tail = head = new ListNode(INT_MAX);
    }

    ListNode *Creat() {
        for (int i = 0; i < elements.size(); ++i) {
            auto node = new ListNode(elements[i]);
            cycle_head = cycle_pos == i ? node : cycle_head;
            append(node);
        }
        tail->next = cycle_head;
        return head->next;
    }

private:
    std::vector<int> elements;
    int cycle_pos;
    ListNode *cycle_head = nullptr;
    ListNode *head;
    ListNode *tail;

    void append(ListNode *ln) {
        tail->next = ln;
        tail = ln;
    }
};

/**
 * @brief 递归/迭代方式反转列表的前N个结点
 * @param head
 * @param n
 * @return
 */
#define REVERSE_N_BY_ITERATOR

ListNode *ReverseN(ListNode *head, int n) {
#ifdef REVERSE_N_BY_ITERATOR
    ListNode dummy_head(INT_MAX, head);
    for (int i = 1; i < n && head->next; ++i) {
        ListNode *p1 = head->next;
        head->next = head->next->next;
        p1->next = dummy_head.next;
        dummy_head.next = p1;
    }
    return dummy_head.next;
#else
    static ListNode *pivot{nullptr};
    if(n <= 1 || !head->next) {
        pivot = head->next;
        return head;
    }
    ListNode *p = ReverseN(head->next,n - 1);
    head->next->next = head;
    head->next = pivot;
    return p;
#endif
}

/**
 * @brief 尾插法创建双向链表
 * @param il
 * @return
 */
Node *CreateDoublyList(const std::initializer_list<int> &il) {
    Node dummy{}, *head = &dummy;
    for (const auto &cil : il) {
        Node *node = new Node;
        node->val = cil;
        node->prev = head;
        head->next = node;
        head = head->next;
    }
    SetListType(ListType::Binary);
    dummy.next->prev = nullptr;
    return dummy.next;
}

/**
 * @brief 给双向链表插入子结点
 * @param head
 * @param child
 * @param pos 表示插入子结点的位置，从1开始计数
 */
void insertChild(Node *head, Node *child, int pos) {
    // pos 从1开始计数
    for (int i = 1; i < pos; ++i) {
        head = head->next;
    }
    head->child = child;
}

/**
 * @brief 递归法创建带有随机指针的链表
 * @tparam It_  迭代器指向的类型为 std::pair<int,int>,
 *              第一个数值为链表结点的值，第二个数值为随机指针指向的位置，从0开始计数，
 *              -1表示该结点的随机指针不指向其他结点，
 * @param start
 * @param end
 * @return
 */
template<typename It_>
Node *CreateList(It_ start, It_ end) {
    static std::vector<Node *> vec;
    if (start == end) return nullptr;
    Node *node = new Node(start->first);
    vec.push_back(node);
    node->next = CreateList(start + 1, end);
    node->random = start->second == -1 ? nullptr : vec[start->second];
    SetListType(ListType::Forward);
    return node;
}

#endif //LEETCODE_LIST_NODE_H

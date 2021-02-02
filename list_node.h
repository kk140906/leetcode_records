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

std::string GetListType() {
    switch (list_type_) {
        case ListType::Forward:
            return " --> ";
        case ListType::Binary:
            return " <--> ";
        default:
            return "";
    }
}

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
ListNode *CreateList(const std::initializer_list<int> &il) {
    ListNode *head = new ListNode, *tail = head;
    for (const auto &cil : il) {
        tail = tail->next = new ListNode(cil);
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


std::ostream &operator<<(std::ostream &os, ListNode *rhs) {
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
        tail = head = new ListNode(0);
    }

    ListNode *Creat() {
        for (int i = 0; i < elements.size(); ++i) {
            auto node = new ListNode(elements[i]);
            cycle_head = cycle_pos == i ? node : cycle_head;
            append(node);
        }
        tail->next = cycle_head;
        return head;
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

#endif //LEETCODE_LIST_NODE_H

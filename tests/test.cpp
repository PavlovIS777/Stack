#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include <string>
#include <exception>
#include "stack.hpp"

TEST(stackTop, empty)
{
    PIlib::stack<int64_t> s;

    try {
        s.top();
        FAIL();
    } catch (const std::exception &e) {
        ASSERT_STREQ("Segmentation fault. Stack is empty.\n", e.what());
    }
}

TEST(stackTop, notEmpty)
{
    PIlib::stack<int64_t> s;
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }
    ASSERT_EQ(s.top(), 4);
}

TEST(stackEmpty, empty)
{
    PIlib::stack<int64_t> s;
    ASSERT_EQ(s.empty(), true);
}

TEST(stackEmpty, notempty)
{
    PIlib::stack<int64_t> s;
    s.push(1);
    ASSERT_EQ(s.empty(), false);
}

TEST(stackPush, push)
{
    PIlib::stack<int64_t> s;
    std::string result;
    for (int i = 0; i < 2 * PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        s.push(i);
        result.insert(0, std::to_string(i) + " ");
    }
    std::string stackStr;
    while (!s.empty()) {
        stackStr.append(std::to_string(s.top()));
        stackStr += " ";
        s.pop();
    }
    ASSERT_EQ(result, stackStr);
}

TEST(stackPop, pop)
{
    PIlib::stack<int64_t> s;
    for (int i = 10; i < 100; i++) {
        s.push(i);
    }
    for (int i = 10; i < 99; i++) {
        s.pop();
    }
    ASSERT_EQ(s.top(), 10);
}

TEST(stackEmplace, emplace)
{
    PIlib::stack<std::pair<int64_t, char>> stack;
    for (int64_t i = 'A'; i < 'A' + 10; i++) {
        stack.emplace(i - 'A', i);
    }
    std::pair<int64_t, char> testPair {9, 'J'};
    ASSERT_EQ(stack.top(), testPair);
}

TEST(stackCopyCtor, copyOtherLvalue)
{
    PIlib::stack<int64_t> src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> dst(src);
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != dst.top()) {
            FAIL();
        }
        src.pop();
        dst.pop();
    }
    if (src.size() != 0 || dst.size() != 0) {
        FAIL();
    }
}

TEST(stackAssigment, assignmentOther)
{
    PIlib::stack<int64_t> src, dst;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> src2;
    dst = src2 = src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != src2.top() || src.top() != dst.top() || src2.top() != dst.top()) {
            FAIL();
        }
        src.pop();
        src2.pop();
        dst.pop();
    }
    if (src.size() != 0 || src2.size() != 0 || dst.size() != 0) {
        FAIL();
    }
}

TEST(stackAssigment, assignmentSelf)
{
    PIlib::stack<int64_t> src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> srcCpy;
    srcCpy = src;
    src = src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != srcCpy.top()) {
            FAIL();
        }
        src.pop();
        srcCpy.pop();
    }
    if (src.size() != 0 || srcCpy.size() != 0) {
        FAIL();
    }
}

PIlib::stack<int64_t> stackReturnRvalue()
{
    PIlib::stack<int64_t> rvalue;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        rvalue.push(i);
    }
    return rvalue;
}

TEST(stackAssigment, assignmentRvalue)
{
    PIlib::stack<int64_t> dst = stackReturnRvalue();
    for (int64_t i = PIlib::DEFAULT_STACK_CAPACITY + 99; i >= 0; --i) {
        if (dst.top() != i) {
            FAIL();
        }
        dst.pop();
    }
    if (dst.size() != 0) {
        FAIL();
    }
}

TEST(stackCopyCtor, copyOtherRvalue)
{
    PIlib::stack<int64_t> dst(stackReturnRvalue());
    for (int64_t i = PIlib::DEFAULT_STACK_CAPACITY + 99; i >= 0; --i) {
        if (dst.top() != i) {
            FAIL();
        }
        dst.pop();
    }
    if (dst.size() != 0) {
        FAIL();
    }
}

TEST(stackBoolTop, empty)
{
    PIlib::stack<bool> s;

    try {
        s.top();
        FAIL();
    } catch (const std::exception &e) {
        ASSERT_STREQ("Segmentation fault. Stack is empty.\n", e.what());
    }
}

TEST(stackBoolTop, notEmpty)
{
    PIlib::stack<bool> s;
    for (int i = 0; i < 5; ++i) {
        s.push(i % 2);
    }
    ASSERT_EQ(s.top(), false);
}

TEST(stackBoolEmpty, empty)
{
    PIlib::stack<bool> s;
    ASSERT_EQ(s.empty(), true);
}

TEST(stackBoolEmpty, notempty)
{
    PIlib::stack<bool> s;
    s.push(true);
    ASSERT_EQ(s.empty(), false);
}

TEST(stackBoolPush, push)
{
    PIlib::stack<bool> s;
    std::string result;
    for (int i = 0; i < PIlib::DEFAULT_BOOL_STACK_CAPACITY + 100; ++i) {
        bool val = rand() % 2;
        s.push(val);
        result.insert(0, std::to_string(val) + " ");
    }
    std::string stackStr;
    while (!s.empty()) {
        stackStr.append(std::to_string(s.top()));
        stackStr += " ";
        s.pop();
    }
    ASSERT_EQ(result, stackStr);
}

TEST(stackBoolPop, pop)
{
    PIlib::stack<bool> s;
    for (int i = 10; i < 100; i++) {
        s.push(i % 2);
    }
    for (int i = 10; i < 99; i++) {
        s.pop();
    }
    ASSERT_EQ(s.top(), 0);
}

TEST(stackBoolCopyCtor, copyOtherLvalue)
{
    PIlib::stack<bool> src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> dst(src);
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != dst.top()) {
            FAIL();
        }
        src.pop();
        dst.pop();
    }
    if (src.size() != 0 || dst.size() != 0) {
        FAIL();
    }
}

TEST(stackBoolAssigment, assignmentOther)
{
    PIlib::stack<bool> src, dst;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> src2;
    dst = src2 = src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != src2.top() || src.top() != dst.top() || src2.top() != dst.top()) {
            FAIL();
        }
        src.pop();
        src2.pop();
        dst.pop();
    }
    if (src.size() != 0 || src2.size() != 0 || dst.size() != 0) {
        FAIL();
    }
}

TEST(stackBoolAssigment, assignmentSelf)
{
    PIlib::stack<bool> src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> srcCpy;
    srcCpy = src;
    src = src;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        if (src.top() != srcCpy.top()) {
            FAIL();
        }
        src.pop();
        srcCpy.pop();
    }
    if (src.size() != 0 || srcCpy.size() != 0) {
        FAIL();
    }
}

PIlib::stack<bool> stackBoolReturnRvalue()
{
    PIlib::stack<bool> rvalue;
    for (int64_t i = 0; i < PIlib::DEFAULT_STACK_CAPACITY + 100; ++i) {
        rvalue.push(i % 2);
    }
    return rvalue;
}

TEST(stackBoolAssigment, assignmentRvalue)
{
    PIlib::stack<bool> dst = stackBoolReturnRvalue();
    for (int64_t i = PIlib::DEFAULT_STACK_CAPACITY + 99; i >= 0; --i) {
        if (dst.top() != (i % 2)) {
            FAIL();
        }
        dst.pop();
    }
    if (dst.size() != 0) {
        FAIL();
    }
}

TEST(stackBoolCopyCtor, copyOtherRvalue)
{
    PIlib::stack<bool> dst(stackBoolReturnRvalue());
    for (int64_t i = PIlib::DEFAULT_STACK_CAPACITY + 99; i >= 0; --i) {
        if (dst.top() != (i % 2)) {
            FAIL();
        }
        dst.pop();
    }
    if (dst.size() != 0) {
        FAIL();
    }
}

int main(int argc, char **argv)
{
    srand(time(nullptr));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
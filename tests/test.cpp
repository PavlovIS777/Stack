#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <random>
#include <string>
#include "stack.h"

TEST(stackTop, notEmpty)
{
    PIlib::stack<int64_t> s;
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }
    for (int i = 4; !s.top(); --i) {
        ASSERT_EQ(s.top(), i);
    }
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
    for (int i = 0; i < 2 * PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
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
    for (int i = 'A' + 9; !stack.empty(); --i) {
        std::pair<int64_t, char> testPair {i - 'A', i};
        ASSERT_EQ(stack.top(), testPair);
        stack.pop();
    }
}

TEST(stackCopyCtor, copyOtherLvalue)
{
    PIlib::stack<int64_t> src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> dst(src);
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        ASSERT_EQ(src.top(), dst.top());
        src.pop();
        dst.pop();
    }
    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackAssigment, assignmentOther)
{
    PIlib::stack<int64_t> src, dst;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> src2;
    dst = src2 = src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        ASSERT_EQ(src.top(), src2.top());
        ASSERT_EQ(src.top(), dst.top());
        ASSERT_EQ(src2.top(), dst.top());
        src.pop();
        src2.pop();
        dst.pop();
    }
    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(src2.size(), 0);
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackAssigment, assignmentSelf)
{
    PIlib::stack<int64_t> src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i);
    }
    PIlib::stack<int64_t> srcCpy;
    srcCpy = src;
    src = src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        ASSERT_EQ(src.top(), srcCpy.top());
        src.pop();
        srcCpy.pop();
    }
    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(srcCpy.size(), 0);
}

PIlib::stack<int64_t> stackReturnRvalue()
{
    PIlib::stack<int64_t> rvalue;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        rvalue.push(i);
    }
    return rvalue;
}

TEST(stackAssigment, assignmentRvalue)
{
    PIlib::stack<int64_t> dst = stackReturnRvalue();
    for (int64_t i = PIlib::stack<int64_t>::DEFAULT_CAPACITY + 99; i >= 0; --i) {
        ASSERT_EQ(dst.top(), i);
        dst.pop();
    }
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackCopyCtor, copyOtherRvalue)
{
    PIlib::stack<int64_t> dst(stackReturnRvalue());
    for (int64_t i = PIlib::stack<int64_t>::DEFAULT_CAPACITY + 99; i >= 0; --i) {
        ASSERT_EQ(dst.top(), i);
        dst.pop();
    }
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackGeneral, general)
{
    PIlib::stack<int64_t> stack;
    std::vector<int64_t> stackVector;
    for (int i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY * 1000; ++i) {
        int64_t tmp = rand();
        stack.push(tmp);
        stackVector.push_back(tmp);
    }
    while (!stack.empty()) {
        ASSERT_EQ(stack.top(), stackVector.back());
        stack.pop();
        stackVector.pop_back();
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
    for (int i = 0; i < PIlib::stack<bool>::DEFAULT_BOOL_STACK_CAPACITY + 100; ++i) {
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
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> dst(src);
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        if (src.top() != dst.top()) {
            FAIL();
        }
        src.pop();
        dst.pop();
    }
    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackBoolAssigment, assignmentOther)
{
    PIlib::stack<bool> src, dst;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> src2;
    dst = src2 = src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        ASSERT_EQ(src.top(), src2.top());
        ASSERT_EQ(src.top(), dst.top());
        ASSERT_EQ(src2.top(), dst.top());
        src.pop();
        src2.pop();
        dst.pop();
    }
    ASSERT_EQ(src.size(), 0);
    ASSERT_EQ(dst.size(), 0);
    ASSERT_EQ(src2.size(), 0);
}

TEST(stackBoolAssigment, assignmentSelf)
{
    PIlib::stack<bool> src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        src.push(i % 2);
    }
    PIlib::stack<bool> srcCpy;
    srcCpy = src;
    src = src;
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        ASSERT_EQ(src.top(), srcCpy.top());
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
    for (int64_t i = 0; i < PIlib::stack<int64_t>::DEFAULT_CAPACITY + 100; ++i) {
        rvalue.push(i % 2);
    }
    return rvalue;
}

TEST(stackBoolAssigment, assignmentRvalue)
{
    PIlib::stack<bool> dst = stackBoolReturnRvalue();
    for (int64_t i = PIlib::stack<int64_t>::DEFAULT_CAPACITY + 99; i >= 0; --i) {
        ASSERT_EQ(dst.top(), i % 2);
        dst.pop();
    }
    ASSERT_EQ(dst.size(), 0);
}

TEST(stackBoolCopyCtor, copyOtherRvalue)
{
    PIlib::stack<bool> dst(stackBoolReturnRvalue());
    for (int64_t i = PIlib::stack<int64_t>::DEFAULT_CAPACITY + 99; i >= 0; --i) {
        ASSERT_EQ(dst.top(), i % 2);
        dst.pop();
    }
    ASSERT_EQ(dst.size(), 0);
}

int main(int argc, char **argv)
{
    std::srand(time(nullptr));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
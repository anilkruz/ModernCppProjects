#include "../src/memory_management/String_impl.cc"
#include <gtest/gtest.h>
#include <cstring>

TEST(StringTest, DefaultConstructor) {
    String s;
    EXPECT_EQ(s.size(), 0u);
}

TEST(StringTest, ParamConstructor) {
    String s("hello");
    EXPECT_EQ(s.size(), 5u);
    EXPECT_STREQ(s.c_str(), "hello");
}

TEST(StringTest, CopyConstructorIsDeepCopy) {
    String s1("world");
    String s2 = s1;
    EXPECT_STREQ(s2.c_str(), "world");
    // They must be different allocations
    EXPECT_NE(s1.c_str(), s2.c_str());
}

TEST(StringTest, CopyAssignmentIsDeepCopy) {
    String s1("foo");
    String s2("bar");
    s2 = s1;
    EXPECT_STREQ(s2.c_str(), "foo");
    EXPECT_NE(s1.c_str(), s2.c_str());
}

TEST(StringTest, MoveConstructorStealsResource) {
    String s1("move_me");
    String s2 = std::move(s1);
    EXPECT_STREQ(s2.c_str(), "move_me");
    EXPECT_EQ(s1.size(), 0u);
}

TEST(StringTest, Concatenation) {
    String s1("Hello");
    String s2(" World");
    String s3 = s1 + s2;
    EXPECT_STREQ(s3.c_str(), "Hello World");
    EXPECT_EQ(s3.size(), 11u);
}

TEST(StringTest, SelfAssignment) {
    String s("self");
    s = s;
    EXPECT_STREQ(s.c_str(), "self");
}

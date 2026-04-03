#include "../src/memory_management/unique_ptr.cc"
#include <gtest/gtest.h>

TEST(UniquePtrTest, BasicValueAccess) {
    unique_ptr<int> up(new int(42));
    EXPECT_EQ(*up, 42);
    EXPECT_NE(up.get(), nullptr);
}

TEST(UniquePtrTest, MoveTransfersOwnership) {
    unique_ptr<int> up1(new int(10));
    unique_ptr<int> up2 = std::move(up1);
    EXPECT_EQ(up1.get(), nullptr);
    EXPECT_EQ(*up2, 10);
}

TEST(UniquePtrTest, MoveAssignment) {
    unique_ptr<int> up1(new int(7));
    unique_ptr<int> up2(new int(8));
    up2 = std::move(up1);
    EXPECT_EQ(up1.get(), nullptr);
    EXPECT_EQ(*up2, 7);
}

TEST(UniquePtrTest, Release) {
    unique_ptr<int> up(new int(5));
    int* raw = up.release();
    EXPECT_EQ(up.get(), nullptr);
    EXPECT_EQ(*raw, 5);
    delete raw;
}

TEST(UniquePtrTest, Reset) {
    unique_ptr<int> up(new int(1));
    up.reset(new int(99));
    EXPECT_EQ(*up, 99);
    up.reset();
    EXPECT_EQ(up.get(), nullptr);
}

TEST(UniquePtrTest, ArrowOperator) {
    struct Point { int x, y; };
    unique_ptr<Point> up(new Point{3, 4});
    EXPECT_EQ(up->x, 3);
    EXPECT_EQ(up->y, 4);
}

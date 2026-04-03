#include "../src/memory_management/Shared_ptr.cc"
#include <gtest/gtest.h>

TEST(SharedPtrTest, DefaultConstructor) {
    SharedPtr<int> sp;
    EXPECT_EQ(sp.use_count(), 0);
}

TEST(SharedPtrTest, BasicValueAccess) {
    SharedPtr<int> sp(new int(10));
    EXPECT_EQ(*sp, 10);
    EXPECT_EQ(sp.use_count(), 1);
}

TEST(SharedPtrTest, CopyIncreasesRefCount) {
    SharedPtr<int> sp1(new int(10));
    SharedPtr<int> sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

TEST(SharedPtrTest, MoveTransfersOwnership) {
    SharedPtr<int> sp1(new int(99));
    SharedPtr<int> sp2 = std::move(sp1);
    EXPECT_EQ(sp1.use_count(), 0);
    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(*sp2, 99);
}

TEST(SharedPtrTest, CopyAssignment) {
    SharedPtr<int> sp1(new int(5));
    SharedPtr<int> sp2(new int(6));
    sp2 = sp1;
    EXPECT_EQ(*sp2, 5);
    EXPECT_EQ(sp1.use_count(), 2);
}

TEST(SharedPtrTest, DestructorDecrementsCount) {
    SharedPtr<int> sp1(new int(42));
    {
        SharedPtr<int> sp2 = sp1;
        EXPECT_EQ(sp1.use_count(), 2);
    } // sp2 destroyed here
    EXPECT_EQ(sp1.use_count(), 1);
}

TEST(SharedPtrTest, ArrowOperator) {
    struct Point { int x, y; };
    SharedPtr<Point> sp(new Point{3, 4});
    EXPECT_EQ(sp->x, 3);
    EXPECT_EQ(sp->y, 4);
}

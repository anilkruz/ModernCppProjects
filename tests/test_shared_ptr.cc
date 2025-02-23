#include "../src/memory_management/Shared_ptr.cc"  // actual implementation
#include <gtest/gtest.h>

TEST(SharedPtrTest, BasicFunctionality) {
    SharedPtr<int> sp1(new int(10));
    EXPECT_EQ(*sp1, 10);
    EXPECT_EQ(sp1.use_count(), 1);

    SharedPtr<int> sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);

 //   sp1.reset();
    EXPECT_EQ(sp1.use_count(), 0);
    EXPECT_EQ(sp2.use_count(), 1);
}


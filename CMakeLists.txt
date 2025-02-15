cmake_minimum_required(VERSION 3.10)
project(ModernCppProjects)

set(CMAKE_CXX_STANDARD 17)

# Custom Memory Allocator
add_executable(allocator ../custum_memory_allocator.cc)

# Smart Pointer Implementation
add_executable(shared_ptr ../Shared_ptr.cc)
add_executable(weakptr ../Weak_ptr.cc)

# GoogleTest Setup
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test for Smart Pointer
add_executable(test_shared_ptr ../test_shared_ptr.cc)
target_link_libraries(test_shared_ptr GTest::GTest GTest::Main pthread)
add_test(NAME TestSharedPtr COMMAND test_shared_ptr)


cmake_minimum_required(VERSION 3.10)
project(ModernCppProjects)
set(CMAKE_CXX_STANDARD 17)
add_executable(allocator ../custum_memory_allocator.cc)
# Manually set GoogleTest path
add_subdirectory(googletest)
include_directories(${GTEST_INCLUDE_DIRS})

# Smart Pointer Code
add_executable(shared_ptr ../shared_ptr.cc)
add_executable(test_shared_ptr ../test_shared_ptr.cc)
target_link_libraries(test_shared_ptr GTest::GTest GTest::Main pthread)
add_executable(weakptr ../Weak_ptr.cc)

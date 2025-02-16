cmake_minimum_required(VERSION 3.10)
project(ModernCppProjects)

set(CMAKE_CXX_STANDARD 17)

# Include directories (for headers)
include_directories(${CMAKE_SOURCE_DIR}/src/memory_management)

# ✅ Create a STATIC library for shared_ptr
add_library(shared_ptr_lib STATIC memory_management/Shared_ptr.cc)

# ✅ Create an executable for testing
add_executable(test_shared_ptr ../tests/test_shared_ptr.cc)

# ✅ Link the library instead of the executable
target_link_libraries(test_shared_ptr shared_ptr_lib GTest::GTest GTest::Main pthread)

# GoogleTest Setup
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Register the test
add_test(NAME TestSharedPtr COMMAND test_shared_ptr)


cmake_minimum_required(VERSION 3.10)
project(ModernCppProjects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
enable_testing()
find_package(GTest REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/memory_management
    ${GTEST_INCLUDE_DIRS}
)

# ── Libraries ──────────────────────────────────────────────────────────────────

add_library(shared_ptr_lib   STATIC memory_management/Shared_ptr.cc)
add_library(unique_ptr_lib   STATIC memory_management/unique_ptr.cc)
add_library(string_lib       STATIC memory_management/String_impl.cc)
add_library(allocator_lib    STATIC memory_management/custom_memory_allocator.cc)
add_library(weak_ptr_lib     STATIC memory_management/Weak_ptr.cc)

# ── Standalone executables ─────────────────────────────────────────────────────

add_executable(shared_ptr_example  memory_management/Shared_ptr.cc)
add_executable(unique_ptr_example  memory_management/unique_ptr.cc)
add_executable(string_example      memory_management/String_impl.cc)
add_executable(allocator_example   memory_management/custom_memory_allocator.cc)
add_executable(weak_ptr_example    memory_management/Weak_ptr.cc)

# ── Tests ──────────────────────────────────────────────────────────────────────

add_executable(test_shared_ptr  ../tests/test_shared_ptr.cc)
target_link_libraries(test_shared_ptr  GTest::GTest GTest::Main pthread)
add_test(NAME TestSharedPtr  COMMAND test_shared_ptr)

add_executable(test_unique_ptr  ../tests/test_unique_ptr.cc)
target_link_libraries(test_unique_ptr  GTest::GTest GTest::Main pthread)
add_test(NAME TestUniquePtr  COMMAND test_unique_ptr)

add_executable(test_string  ../tests/test_string.cc)
target_link_libraries(test_string  GTest::GTest GTest::Main pthread)
add_test(NAME TestString  COMMAND test_string)

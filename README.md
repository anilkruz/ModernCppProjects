# 🚀 Modern C++ Projects

Modern C++ Projects 🚀

Project Overview

This project implements custom smart pointers (shared_ptr, weak_ptr) and a custom memory allocator using Modern C++. The goal is to improve memory management and optimize performance.

Features

✅ Custom Shared Pointer (shared_ptr) Implementation
✅ Custom Weak Pointer (weak_ptr) Implementation
✅ Custom Memory Allocator for Performance Optimization
✅ Unit Tests using GoogleTest
✅ CI/CD Pipeline with GitHub Actions

How to Build & Run?

Step 1: Clone the Repository
git clone https://github.com/anilkruz/ModernCppProjects.git
cd ModernCppProjects
Step 2: Build the Project
mkdir build
cd build
cmake ..
make
Step 3: Run the Executables
Run Shared Pointer Example

./shared_ptr
Run Memory Allocator Example

./allocator
Step 4: Run Unit Tests
ctest --output-on-failure
CI/CD Pipeline Explained

Trigger: The pipeline automatically starts on a push or pull request to the main branch.
Steps:
✅ Checkout Code
✅ Install Dependencies (cmake, g++, GoogleTest)
✅ Build Project using CMake
✅ Run Unit Tests using GoogleTest
Failure Handling: If a test fails or the build breaks, GitHub Actions logs the error.
Code Example: Smart Pointer Usage

#include "shared_ptr.h"

int main() {
    SharedPtr<int> sp1(new int(10));
    SharedPtr<int> sp2 = sp1; // Reference count increases
    std::cout << "Value: " << *sp1 << ", Use Count: " << sp1.use_count() << std::endl;
    return 0;
}
Contributing

If you want to contribute, feel free to create a pull request!

💡 For suggestions and improvements, open an issue in the repository.



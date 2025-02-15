# 🚀 Modern C++ Projects
Modern C++ Smart Pointers & Custom Memory Allocator 🚀

A performance-optimized implementation of custom shared_ptr, weak_ptr, and a custom memory allocator using Modern C++ (C++20).
This project ensures efficient memory management, avoids memory leaks, and improves performance using RAII principles and custom allocation strategies.

🔥 Features

✅ Custom Smart Pointers (shared_ptr, weak_ptr) implementation
✅ Reference Counting Mechanism for smart pointers
✅ Custom Memory Allocator for optimized allocation & deallocation
✅ CI/CD Integration with GitHub Actions for automated builds
✅ CMake Build System for easy cross-platform compilation

⚙️ How to Build & Run?

Step 1: Clone the Repository
git clone https://github.com/anilkruz/ModernCppProjects.git
cd ModernCppProjects
Step 2: Build the Project
mkdir build && cd build
cmake ..
make
Step 3: Run the Executables
Run Smart Pointer Implementation

./shared_ptr
Run Custom Memory Allocator

./allocator
🚀 CI/CD Pipeline Explained

This project uses GitHub Actions for CI/CD, which automatically builds and tests the code whenever you push changes.
📌 CI/CD Workflow:

Push Code to GitHub (git push origin main)
GitHub Actions Trigger Hota Hai (.github/workflows/ci.yml se)
CI/CD Steps:
Checkout Code
Install Dependencies (CMake, Compiler)
Run cmake .. && make
Execute Tests
Agar Sab Sahi Hai ✅, toh CI/CD Pass Ho Jayega!
Agar Error Hai ❌, toh Logs Actions Tab Me Milenge!
📌 Check CI/CD Status Here:
👉 GitHub Actions

📌 Code Example: Custom shared_ptr Usage

#include "shared_ptr.h"
#include <iostream>

int main() {
    SharedPtr<int> sp1(new int(10));
    SharedPtr<int> sp2 = sp1; // Reference count increases

    std::cout << "Value: " << *sp1 << std::endl;
    std::cout << "Use count: " << sp1.use_count() << std::endl;

    return 0;
}
📌 Output:

Value: 10
Use count: 2
🔥 Reference counting work kar raha hai!

📜 License

This project is open-source under the MIT License.

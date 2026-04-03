# Modern C++ Projects

[![C++ CI](https://github.com/anilkruz/ModernCppProjects/actions/workflows/ci.yml/badge.svg)](https://github.com/anilkruz/ModernCppProjects/actions/workflows/ci.yml)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A collection of Modern C++ implementations covering smart pointers, custom memory management, and RAII principles — built from scratch to understand the internals of the STL.

## Projects

| Component | Description | Key Concepts |
|-----------|-------------|--------------|
| `SharedPtr<T>` | Reference-counted smart pointer | Atomic ref-counting, RAII, Rule of Five |
| `UniquePtr<T>` | Exclusive-ownership smart pointer | Move semantics, deleted copy, `make_unique` |
| `WeakPtr<T>` | Non-owning observer pointer | Breaking circular references, `lock()` |
| `String` | Custom string class | Deep copy, move semantics, operator overloading |
| `PoolAllocator` | Fixed-size block memory pool | Pre-allocation, free lists, cache locality |

## Design Highlights

- **Thread-safe reference counting** in `SharedPtr` using `std::atomic<int>`
- **Zero-overhead move semantics** — move constructor/assignment implemented for all classes
- **Rule of Five** applied consistently across all resource-owning classes
- **WeakPtr** breaks circular `SharedPtr` references without affecting ownership
- **Pool allocator** reduces heap fragmentation for workloads with many small, same-size allocations

## Build & Run

### Prerequisites

- CMake >= 3.10
- GCC/Clang with C++17 support
- [GoogleTest](https://github.com/google/googletest)

### Steps

```bash
# Clone
git clone https://github.com/anilkruz/ModernCppProjects.git
cd ModernCppProjects

# Build
cmake -B build -S src
cmake --build build

# Run tests
cd build && ctest --output-on-failure
```

### Run individual examples

```bash
./build/shared_ptr_example
./build/unique_ptr_example
./build/string_example
./build/allocator_example
```

## Usage Examples

### SharedPtr

```cpp
#include "Shared_ptr.cc"

SharedPtr<int> sp1(new int(42));
SharedPtr<int> sp2 = sp1;           // ref count → 2

std::cout << *sp1;                  // 42
std::cout << sp1.use_count();       // 2
// both sp1 and sp2 go out of scope → memory freed automatically
```

### UniquePtr

```cpp
#include "unique_ptr.cc"

UniquePtr<int> u1(new int(10));
UniquePtr<int> u2 = std::move(u1); // ownership transferred; u1 is now null

auto u3 = make_unique<int>(99);    // preferred factory function
```

### WeakPtr

```cpp
#include "Weak_ptr.cc"

SharedPtr<int> sp(new int(7));
WeakPtr<int> wp = sp;              // does NOT increment ref count

if (auto locked = wp.lock()) {     // safe access — returns SharedPtr or null
    std::cout << *locked;          // 7
}
```

### Pool Allocator

```cpp
#include "custom_memory_allocator.cc"

PoolAllocator pool(64, 1000);      // 1000 blocks of 64 bytes each

void* block = pool.allocate();
// ... use block ...
pool.deallocate(block);
```

## Testing

Tests use [GoogleTest](https://github.com/google/googletest). Coverage includes:

- `SharedPtr`: construction, copy/move, ref counting, destruction
- `UniquePtr`: exclusive ownership, move transfer, `release()`, `reset()`
- `String`: deep copy, move steal, concatenation

```bash
cd build && ctest -V
```

## CI/CD

GitHub Actions runs on every push and pull request to `main`:

1. Install dependencies (`cmake`, `g++`, GoogleTest)
2. Configure and build with CMake
3. Run all tests with `ctest --output-on-failure`

## Project Structure

```
ModernCppProjects/
├── src/
│   ├── CMakeLists.txt
│   └── memory_management/
│       ├── Shared_ptr.cc              # SharedPtr<T> implementation
│       ├── unique_ptr.cc              # UniquePtr<T> implementation
│       ├── Weak_ptr.cc                # WeakPtr<T> implementation
│       ├── String_impl.cc             # Custom String class
│       ├── custom_memory_allocator.cc # Pool allocator
│       └── operator_insertion_.cc     # Operator overloading demo
├── tests/
│   ├── test_shared_ptr.cc
│   ├── test_unique_ptr.cc
│   └── test_string.cc
├── .github/workflows/ci.yml
└── Doxyfile
```

## Contributing

Pull requests are welcome. For major changes, open an issue first to discuss what you'd like to change.

#include <iostream>
#include <utility>
#include <memory>
using namespace std;
// Custom unique_ptr implementation
template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Constructor
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    // Delete copy constructor and copy assignment
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment operator
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Destructor
    ~unique_ptr() {
        delete ptr;
    }

    // Overloaded operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // Get raw pointer
    T* get() const { return ptr; }

    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Reset with a new pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// make_unique implementation?
 /*
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}*/

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args){
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// Example usage
class Test {
public:
    int x;
    Test(int val) : x(val) {
        std::cout << "Test Constructor: " << x << "\n";
    }
    ~Test() {
        std::cout << "Test Destructor\n";
    }
};

int main() {
    // Using unique_ptr
    unique_ptr<int> u1(new int(10));
    std::cout << "Value: " << *u1 << "\n";

    // Using make_unique
    auto u2 = make_unique<Test>(42);
    std::cout << "Test value: " << u2->x << "\n";
    
    return 0;
}


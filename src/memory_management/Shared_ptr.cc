#include <iostream>
#include <atomic>
using namespace std;
// Custom shared_ptr implementation
template <typename T>
class SharedPtr {
private:
    T* ptr;
    std::atomic<int>* ref_count;
public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) : ptr(p) {
        if (ptr) {
            ref_count = new std::atomic<int>(1);
        } else {
            ref_count = nullptr;
        }
    }
    // Copy Constructor
    SharedPtr(const SharedPtr& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) {
            (*ref_count)++;
        }
    }
    // Move Constructor
    SharedPtr(SharedPtr&& other) noexcept {
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }
    // Destructor
    ~SharedPtr() {
        release();
    }
    // Copy Assignment Operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                (*ref_count)++;
            }
        }
        return *this;
    }
    // Move Assignment Operator
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }
    // Overload * and -> operators
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    // Get reference count
    int use_count() const { return ref_count ? ref_count->load() : 0; }
private:
    void release() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
    }
};
// Test Code
int main() {
    SharedPtr<int> sp1( new int(10));
    SharedPtr<int> sp2 = sp1;
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    return 0;
}


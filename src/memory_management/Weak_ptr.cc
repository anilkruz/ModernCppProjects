#include <iostream>
#include <atomic>

// Forward declaration
template <typename T>
class WeakPtr;

// Shared control block used by SharedPtr and WeakPtr
template <typename T>
struct ControlBlock {
    T* ptr;
    std::atomic<int> strong_count;
    std::atomic<int> weak_count;

    explicit ControlBlock(T* p)
        : ptr(p), strong_count(1), weak_count(0) {}
};

// SharedPtr with weak_ptr support via ControlBlock
template <typename T>
class SharedPtr {
    template <typename U>
    friend class WeakPtr;

private:
    ControlBlock<T>* ctrl;

    void release() {
        if (!ctrl) return;
        if (--ctrl->strong_count == 0) {
            delete ctrl->ptr;
            ctrl->ptr = nullptr;
            if (ctrl->weak_count == 0) {
                delete ctrl;
            }
        }
        ctrl = nullptr;
    }

public:
    explicit SharedPtr(T* p = nullptr) {
        ctrl = p ? new ControlBlock<T>(p) : nullptr;
    }

    // Construct from WeakPtr (throws if expired)
    explicit SharedPtr(const WeakPtr<T>& wp) {
        if (!wp.ctrl || wp.ctrl->strong_count == 0)
            throw std::runtime_error("WeakPtr is expired");
        ctrl = wp.ctrl;
        ++ctrl->strong_count;
    }

    SharedPtr(const SharedPtr& other) : ctrl(other.ctrl) {
        if (ctrl) ++ctrl->strong_count;
    }

    SharedPtr(SharedPtr&& other) noexcept : ctrl(other.ctrl) {
        other.ctrl = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl) ++ctrl->strong_count;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    ~SharedPtr() { release(); }

    T& operator*()  const { return *ctrl->ptr; }
    T* operator->() const { return ctrl->ptr; }
    T* get()        const { return ctrl ? ctrl->ptr : nullptr; }

    int use_count() const { return ctrl ? ctrl->strong_count.load() : 0; }
    bool expired()  const { return use_count() == 0; }
};

// WeakPtr — non-owning observer; does not prevent deletion
template <typename T>
class WeakPtr {
    template <typename U>
    friend class SharedPtr;

private:
    ControlBlock<T>* ctrl;

    void release() {
        if (!ctrl) return;
        if (--ctrl->weak_count == 0 && ctrl->strong_count == 0) {
            delete ctrl;
        }
        ctrl = nullptr;
    }

public:
    WeakPtr() : ctrl(nullptr) {}

    WeakPtr(const SharedPtr<T>& sp) : ctrl(sp.ctrl) {
        if (ctrl) ++ctrl->weak_count;
    }

    WeakPtr(const WeakPtr& other) : ctrl(other.ctrl) {
        if (ctrl) ++ctrl->weak_count;
    }

    WeakPtr(WeakPtr&& other) noexcept : ctrl(other.ctrl) {
        other.ctrl = nullptr;
    }

    WeakPtr& operator=(const SharedPtr<T>& sp) {
        release();
        ctrl = sp.ctrl;
        if (ctrl) ++ctrl->weak_count;
        return *this;
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl) ++ctrl->weak_count;
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    ~WeakPtr() { release(); }

    // Returns true if the managed object has been destroyed
    bool expired() const {
        return !ctrl || ctrl->strong_count == 0;
    }

    // Safely promotes to SharedPtr; returns empty SharedPtr if expired
    SharedPtr<T> lock() const {
        if (expired()) return SharedPtr<T>(nullptr);
        return SharedPtr<T>(*this);
    }

    int use_count() const { return ctrl ? ctrl->strong_count.load() : 0; }
};

// Demo
int main() {
    SharedPtr<int> sp1(new int(42));
    WeakPtr<int> wp = sp1;

    std::cout << "use_count: " << wp.use_count() << "\n"; // 1
    std::cout << "expired:   " << wp.expired()   << "\n"; // 0

    {
        auto sp2 = wp.lock();
        if (sp2.get()) {
            std::cout << "locked value: " << *sp2 << "\n"; // 42
            std::cout << "use_count:    " << wp.use_count() << "\n"; // 2
        }
    } // sp2 destroyed, count back to 1

    // sp1 goes out of scope at end of main → object deleted
    // wp.expired() would then return true
    return 0;
}

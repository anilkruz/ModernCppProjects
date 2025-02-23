#include <iostream>
#include <cstring> // for strlen & strcpy

class String {
private:
    char* data;
    size_t length;

public:
    // Default Constructor
    String() : data(nullptr), length(0) {}

    // Parameterized Constructor
    String(const char* str) {
        length = strlen(str);
        data = new char[length + 1]; // +1 for null terminator
        strcpy(data, str);
    }

    // Copy Constructor (Deep Copy)
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // Copy Assignment Operator (Deep Copy)
    String& operator=(const String& other) {
        if (this != &other) { // Self-assignment check
            delete[] data; // Free old memory
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // Move Constructor (Steal Resource)
    String(String&& other) noexcept : data(nullptr), length(0) {
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }

    // Move Assignment Operator (Steal Resource)
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data; // Free old memory
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // Concatenation (+ operator)
    String operator+(const String& other) const {
        String newStr;
        newStr.length = length + other.length;
        newStr.data = new char[newStr.length + 1];
        strcpy(newStr.data, data);
        strcat(newStr.data, other.data);
        return newStr;
    }

    // Print (<< operator overload)
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // Get C-style string
    const char* c_str() const { return data; }

    // Get size of string
    size_t size() const { return length; }

    // Destructor (Free Memory)
    ~String() { delete[] data; }
};

// ✅ **Test Cases**
int main() {
    String s1("Hello");
    String s2(" World");

    // Copy Constructor
    String s3 = s1;

    // Move Constructor
    String s4 = std::move(s2);

    // Concatenation
    String s5 = s1 + s3;

    std::cout << "s1: " << s1 << "\n";
    std::cout << "s3 (copy of s1): " << s3 << "\n";
    std::cout << "s4 (moved from s2): " << s4 << "\n";
    std::cout << "s5 (s1 + s3): " << s5 << "\n";

    return 0;
}


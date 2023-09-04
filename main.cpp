#include <iostream>
#include <memory>

class Integer {
private:
    int* value_ptr;
    std::shared_ptr<int> ref_count;

public:
    Integer(int value) : value_ptr(new int(value)), ref_count(new int(1)) {}

    Integer(const Integer& other) : value_ptr(other.value_ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    Integer& operator=(const Integer& other) {
        if (this == &other) {
            return *this;
        }

        // Decrement the old reference count and check if it should be deleted
        (*ref_count)--;
        if (*ref_count == 0) {
            delete value_ptr;
            value_ptr = nullptr;
        }

        // Copy the new values
        value_ptr = other.value_ptr;
        ref_count = other.ref_count;
        (*ref_count)++;

        return *this;
    }

    ~Integer() {
        (*ref_count)--;
        if (*ref_count == 0) {
            delete value_ptr;
            value_ptr = nullptr;
        }
    }

    int getValue() const {
        if (value_ptr) {
            return *value_ptr;
        }
        return 0; // Return 0 for uninitialized or deleted integers
    }

    int getRefCount() const {
        if (ref_count) {
            return *ref_count;
        }
        return 0; // Return 0 for uninitialized or deleted integers
    }
};

int main() {
    Integer a(42);
    Integer b = a;
    Integer c(17);

    std::cout << "a: Value=" << a.getValue() << ", Ref Count=" << a.getRefCount() << std::endl;
    std::cout << "b: Value=" << b.getValue() << ", Ref Count=" << b.getRefCount() << std::endl;
    std::cout << "c: Value=" << c.getValue() << ", Ref Count=" << c.getRefCount() << std::endl;

    b = c;

    std::cout << "a: Value=" << a.getValue() << ", Ref Count=" << a.getRefCount() << std::endl;
    std::cout << "b: Value=" << b.getValue() << ", Ref Count=" << b.getRefCount() << std::endl;
    std::cout << "c: Value=" << c.getValue() << ", Ref Count=" << c.getRefCount() << std::endl;

    return 0;
}

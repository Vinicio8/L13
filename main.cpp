#include <iostream>
#include <algorithm>

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s), data(new int[s]()) {
        std::cout << "Constructor called\n";
    }

    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
        std::cout << "Copy constructor called\n";
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) { 
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }

    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor called\n";
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "Move assignment called\n";
        }
        return *this;
    }

    ~Buffer() {
        if (data) {
            delete[] data;
            std::cout << "Destructor called\n";
        }
    }
};

int main() {
    Buffer b1(100);            
    Buffer b2 = b1;            
    Buffer b3 = std::move(b1); 

    Buffer b4(50);             
    b4 = b2;                   
    b4 = std::move(b2);        

    return 0;
}

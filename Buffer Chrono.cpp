#include <iostream>
#include <algorithm> 
#include <chrono>   

class Buffer {
private:
    int* data;
    size_t size;

public:
    Buffer(size_t s) : size(s), data(new int[s]()) {
    }

    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) { 
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Buffer() {
        if (data) {
            delete[] data;
        }
    }
};

int main() {
    const size_t bufferSize = 100000000; 
    const int numIterations = 9; 

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        Buffer b1(bufferSize);
        Buffer b2 = b1; 
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Copy operation duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i) {
        Buffer b1(bufferSize);
        Buffer b2 = std::move(b1); 
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Move operation duration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}

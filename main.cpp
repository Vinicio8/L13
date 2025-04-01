#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1 = {2, 1, 5, 8, 4, 6};
    std::vector<int> v2 = v1;        
    std::vector<int> v3 = std::move(v1); 

    std::cout << "v1 size: " << v1.size() << std::endl;
    std::cout << "v2 size: " << v2.size() << std::endl;
    std::cout << "v3 size: " << v3.size() << std::endl;

    return 0;
}

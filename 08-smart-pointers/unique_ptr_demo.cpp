#include <iostream>
#include <memory>

int main() {

    std::unique_ptr<int> p1 = std::make_unique<int>(100);
    std::cout << "1. Print *p1 " << *p1 << "\n";
    std::unique_ptr<int> p2 = std::move(p1);
    std::cout << "2. Print *p2 " << *p2 << "\n";
    if (!p1) {
        std::cout << "p1 = null";
    } else {
        std::cout << "p1 != null";
    }

    return 0;
}
#include <iostream>
#include <RMCode/RMCode.hpp>

int main() {

    auto decodedBits = RMCode<1, 4>::getValidCodeword({1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0});
    std::cout << util::Array::print(decodedBits.value()) << std::endl;

    return 0;
}

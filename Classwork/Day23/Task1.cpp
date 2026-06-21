#include <iostream>
#include <array>
#include <stdexcept>

int main() {
    // Initializing a std::array of 5 integers
    std::array<int, 5> myNumbers = {10, 20, 30, 40, 50};

    try {
        // Safe access
        std::cout << "Element at index 2: " << myNumbers.at(2) << std::endl;

        // Modifying an element
        myNumbers.at(0) = 100;

        // Attempting out-of-bounds access
        std::cout << "Out of bounds: " << myNumbers.at(10) << std::endl; 
    } 
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

class BinaryNumber {
private:
    std::vector<int> bits;  // Store binary digits as a vector of integers (0 or 1)

public:
    // Constructors
    BinaryNumber(const std::string& binaryStr);
    BinaryNumber(const BinaryNumber& other);
    BinaryNumber& operator=(const BinaryNumber& other); // Assignment operator

    // Member functions
    void print() const; // Print the binary number
    void leftShift(int positions); // Left shift function

    // overload inside class
    //BinaryNumber operator+(const BinaryNumber& val2) const; // Addition


    // Friend operator overloads
    friend BinaryNumber operator+(const BinaryNumber& val1, const BinaryNumber& val2); // Addition
    friend BinaryNumber operator*(const BinaryNumber& val1, const BinaryNumber& val2); // Multiplication

private:
    // Private constructor for internal use
    //This constructor can be used to create and return a Binay number object.
    BinaryNumber(const std::vector<int>& bits);
};

// Constructor from binary string
BinaryNumber::BinaryNumber(const std::string& binaryStr) {
    for (char c : binaryStr) {
        if (c == '0') {
            bits.push_back(0);
        } else if (c == '1') {
            bits.push_back(1);
        } else {
            throw std::invalid_argument("Invalid binary string");
        }
    }
}

// Copy constructor
// Task 1 Write Copy constructor below
BinaryNumber::BinaryNumber(const BinaryNumber& other) : bits(other.bits) {}

// Assignment operator
BinaryNumber& BinaryNumber::operator=(const BinaryNumber& other) {
    if (this != &other) {
        bits = other.bits;
    }
    return *this;
}

// Print the binary number
// Task 1 Complete the below Print the binary number functionxs

void BinaryNumber::print() const {
    for (int bit : bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

void BinaryNumber::leftShift(int positions) {
    // Shift bits to the left by the specified number of positions
    for (int i = 0; i < positions; ++i) {
        bits.push_back(0); // Add a zero at the end for each position shifted
    }
}

// Constructor from bits vector for internal use
BinaryNumber::BinaryNumber(const std::vector<int>& bits) : bits(bits) {}

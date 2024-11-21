#include "Bin_Number.h"

/*
BinaryNumber BinaryNumber :: operator+(const BinaryNumber& val2) const {

    std::vector<int> result;
    int carry = 0;

    size_t maxSize = std::max(bits.size(), val2.bits.size());
    result.reserve(maxSize + 1); // +1 for possible carry

    for (size_t i = 0; i < maxSize; ++i) {
        int bitA = (i < bits.size()) ? bits[bits.size() - 1 - i] : 0;
        int bitB = (i < val2.bits.size()) ? val2.bits[val2.bits.size() - 1 - i] : 0;

        int sum = bitA + bitB + carry; // Add bits and carry
        result.push_back(sum % 2); // Result bit is sum modulo 2
        carry = sum / 2; // New carry is sum divided by 2
    }

    if (carry) {
        result.push_back(carry); // Add final carry if necessary
    }

    std::reverse(result.begin(), result.end()); // Reverse to correct order
    return BinaryNumber(result); // Create a new BinaryNumber from the result vector
} */ 

BinaryNumber operator+(const BinaryNumber& val1, const BinaryNumber& val2) {
    std::vector<int> result;
    int carry = 0;

    size_t maxSize = std::max(val1.bits.size(), val2.bits.size());
    result.reserve(maxSize + 1); // +1 for possible carry

    for (size_t i = 0; i < maxSize; ++i) {
        int bitA = (i < val1.bits.size()) ? val1.bits[val1.bits.size() - 1 - i] : 0;
        int bitB = (i < val2.bits.size()) ? val2.bits[val2.bits.size() - 1 - i] : 0;

        int sum = bitA + bitB + carry; // Add bits and carry
        result.push_back(sum % 2); // Result bit is sum modulo 2
        carry = sum / 2; // New carry is sum divided by 2
    }

    if (carry) {
        result.push_back(carry); // Add final carry if necessary
    }

    std::reverse(result.begin(), result.end()); // Reverse to correct order
    return BinaryNumber(result); // Create a new BinaryNumber from the result vector
}

// Multiplication operator overload (friend function)
BinaryNumber operator*(const BinaryNumber& val1, const BinaryNumber& val2) {
    BinaryNumber result("0"); // Initialize result to 0

    // Perform multiplication bit by bit
    for (size_t i = 0; i < val2.bits.size(); ++i) {
        if (val2.bits[val2.bits.size() - 1 - i]) { // If the bit is 1
            BinaryNumber temp = val1; // Copy current binary number
            temp.leftShift(i); // Shift temp left by i positions
            result = result + temp; // Add shifted value to result
        }
    }

    return result; // Return the result of multiplication
}


// Example usage
int main() {
    try {
        BinaryNumber bin1("101");  // Binary representation of 13
        std::cout << "Binary 1: ";
        bin1.print();                 // Output: 1101

        BinaryNumber bin2("1101");    // Binary representation of 5
        std::cout << "Binary 2: ";
        bin2.print();                 // Output: 101

        BinaryNumber sum = bin1 + bin2; // Addition
        std::cout << "Sum: ";
        sum.print();                   // Output: 10000 (18 in decimal)

        BinaryNumber product = bin1 * bin2; // Multiplication
        std::cout << "Product: ";
        product.print();               // Output: 111101 (65 in decimal)

        // try a different way of doing addition
        std::string str1 = "101";
        // this invokes the overload + operator inside the class, and it works
        BinaryNumber sum2 = bin2 + str1;
        std::cout << "Sum2: ";
        sum2.print();

	// but if you swap the order, oops! So why the commutative law of summation fails to hold here?
        BinaryNumber sum3 = str1 + bin2;
        std::cout << "Sum3: ";
        sum3.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

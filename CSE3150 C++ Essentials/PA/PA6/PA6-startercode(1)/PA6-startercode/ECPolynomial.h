#ifndef ECPolynomial_h
#define ECPolynomial_h

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

// Class to represent a polynomial of a single variable
class ECPolynomial {
public:
    // Constructor to initialize polynomial with given coefficients
    ECPolynomial(const std::vector<double> &listCoeffsIn);
    
    // Copy constructor
    ECPolynomial(const ECPolynomial &rhs);
    
    // Accessor to get the degree of the polynomial
    int GetDegree() const;
    
    // Scale the polynomial by a constant factor
    ECPolynomial Scale(double factor) const;
    
    // Operator overloads for polynomial addition and multiplication
    ECPolynomial operator+(const ECPolynomial &rhs) const;
    ECPolynomial operator*(const ECPolynomial &rhs) const;
    ECPolynomial operator/(const ECPolynomial &rhs) const;
    ECPolynomial operator%(const ECPolynomial &rhs) const;
    
    // Utility function for debugging
    void Dump() const;

private:
    // Coefficients of the polynomial
    std::vector<double> coefficients;
    
    // Helper function to trim trailing zeros
    void Trim();
};

#endif /* ECPolynomial_h */

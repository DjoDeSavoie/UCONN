#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "ECPolynomial.h"

using namespace std;

// Constructor: Initializes the polynomial and trims trailing zeros
ECPolynomial::ECPolynomial(const std::vector<double> &listCoeffsIn) : coefficients(listCoeffsIn) {
    Trim();
}

// Copy constructor: Creates a deep copy of another ECPolynomial
ECPolynomial::ECPolynomial(const ECPolynomial &rhs) : coefficients(rhs.coefficients) {}

// Helper function to remove trailing zeros (coefficients with absolute value < 1e-10)
void ECPolynomial::Trim() {
    while (coefficients.size() > 1 && fabs(coefficients.back()) < 1e-10) {
        coefficients.pop_back();
    }
}

// Get the degree of the polynomial
int ECPolynomial::GetDegree() const {
    return static_cast<int>(coefficients.size()) - 1;
}

// Scale the polynomial by a constant factor and return the resulting polynomial
ECPolynomial ECPolynomial::Scale(double factor) const {
    std::vector<double> scaledCoeffs = coefficients;
    for(auto &coef : scaledCoeffs) {
        coef *= factor;
    }
    return ECPolynomial(scaledCoeffs);
}

// Add two polynomials and return the result
ECPolynomial ECPolynomial::operator+(const ECPolynomial &rhs) const {
    size_t maxSize = std::max(coefficients.size(), rhs.coefficients.size());
    std::vector<double> resultCoeffs(maxSize, 0.0);
    
    // Add coefficients from the first polynomial
    for(size_t i = 0; i < coefficients.size(); ++i) {
        resultCoeffs[i] += coefficients[i];
    }
    
    // Add coefficients from the second polynomial
    for(size_t i = 0; i < rhs.coefficients.size(); ++i) {
        resultCoeffs[i] += rhs.coefficients[i];
    }
    
    return ECPolynomial(resultCoeffs);
}

// Multiply two polynomials and return the result
ECPolynomial ECPolynomial::operator*(const ECPolynomial &rhs) const {
    size_t deg1 = coefficients.size();
    size_t deg2 = rhs.coefficients.size();
    std::vector<double> resultCoeffs(deg1 + deg2 - 1, 0.0);
    
    for(size_t i = 0; i < deg1; ++i) {
        for(size_t j = 0; j < deg2; ++j) {
            resultCoeffs[i + j] += coefficients[i] * rhs.coefficients[j];
        }
    }
    
    return ECPolynomial(resultCoeffs);
}

// Divide the current polynomial by another polynomial and return the quotient
ECPolynomial ECPolynomial::operator/(const ECPolynomial &rhs) const {
    if(rhs.coefficients.empty() || (rhs.coefficients.size() == 1 && fabs(rhs.coefficients[0]) < 1e-10)) {
        throw std::invalid_argument("Division by zero polynomial.");
    }
    
    ECPolynomial dividend(*this);    
    ECPolynomial divisor(rhs);       
    std::vector<double> quotientCoeffs;
    
    while(dividend.GetDegree() >= divisor.GetDegree()) {
        int degDiff = dividend.GetDegree() - divisor.GetDegree();
        double leadCoeff = dividend.coefficients.back() / divisor.coefficients.back();
        
        std::vector<double> termCoeffs(degDiff, 0.0);
        for(auto coef : divisor.coefficients) {
            termCoeffs.push_back(coef * leadCoeff);
        }
        ECPolynomial term(termCoeffs);
        
        dividend = dividend + term.Scale(-1.0);
        
        if(static_cast<int>(quotientCoeffs.size()) <= degDiff) {
            quotientCoeffs.resize(degDiff + 1, 0.0);
        }
        quotientCoeffs[degDiff] += leadCoeff;
    }
    
    ECPolynomial quotient(quotientCoeffs);
    quotient.Trim();
    return quotient;
}

// Calculate the remainder when dividing the current polynomial by another polynomial
ECPolynomial ECPolynomial::operator%(const ECPolynomial &rhs) const {
    if(rhs.coefficients.empty() || (rhs.coefficients.size() == 1 && fabs(rhs.coefficients[0]) < 1e-10)) {
        throw std::invalid_argument("Division by zero polynomial.");
    }
    
    ECPolynomial dividend(*this);    
    ECPolynomial divisor(rhs);       
    
    while(dividend.GetDegree() >= divisor.GetDegree()) {
        int degDiff = dividend.GetDegree() - divisor.GetDegree();
        double leadCoeff = dividend.coefficients.back() / divisor.coefficients.back();
        
        std::vector<double> termCoeffs(degDiff, 0.0);
        for(auto coef : divisor.coefficients) {
            termCoeffs.push_back(coef * leadCoeff);
        }
        ECPolynomial term(termCoeffs);
        
        dividend = dividend + term.Scale(-1.0);
    }
    
    dividend.Trim();
    return dividend;
}

// Dump the polynomial to the terminal for debugging
void ECPolynomial::Dump() const {
    if(coefficients.empty()) {
        cout << "0";
        return;
    }
    
    bool first = true;
    for(int i = GetDegree(); i >= 0; --i) {
        double coef = coefficients[i];
        if(fabs(coef) < 1e-10) continue; // Skip zero coefficients
        
        if(!first) {
            cout << (coef >= 0 ? " + " : " - ");
        } else {
            if(coef < 0) cout << "-";
        }
        
        double absCoef = fabs(coef);
        if(i == 0 || absCoef != 1.0) {
            cout << absCoef;
            if(i > 0) cout << "*";
        }
        if(i > 0) {
            cout << "x";
            if(i > 1) cout << "^" << i;
        }
        first = false;
    }
    
    if(first) { // All coefficients are zero
        cout << "0";
    }
}

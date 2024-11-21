#include "ECRational.h"
#include <stdexcept> // For std::invalid_argument

// Constructor
template <class T>
ECRational<T>::ECRational(const T &numeratorIn, const T &denominatorIn)
    : numerator(numeratorIn), denominator(denominatorIn) {
    // Ensure the denominator is not zero
    if (denominatorIn == T(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
}

// Copy constructor
template <class T>
ECRational<T>::ECRational(const ECRational<T> &other)
    : numerator(other.numerator), denominator(other.denominator) {}

// Assignment operator
template <class T>
ECRational<T>& ECRational<T>::operator=(const ECRational<T> &other) {
    if (this != &other) { // Self-assignment check
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

// Addition operator
template <class T>
ECRational<T> ECRational<T>::operator+(const ECRational<T> &other) const {
    T newNumerator = numerator * other.denominator + other.numerator * denominator;
    T newDenominator = denominator * other.denominator;
    return ECRational(newNumerator, newDenominator);
}

// Subtraction operator
template <class T>
ECRational<T> ECRational<T>::operator-(const ECRational<T> &other) const {
    T newNumerator = numerator * other.denominator - other.numerator * denominator;
    T newDenominator = denominator * other.denominator;
    return ECRational(newNumerator, newDenominator);
}

// Multiplication operator
template <class T>
ECRational<T> ECRational<T>::operator*(const ECRational<T> &other) const {
    T newNumerator = numerator * other.numerator;
    T newDenominator = denominator * other.denominator;
    return ECRational(newNumerator, newDenominator);
}

// Division operator
template <class T>
ECRational<T> ECRational<T>::operator/(const ECRational<T> &other) const {
    if (other.numerator == T(0)) {
        throw std::invalid_argument("Division by zero");
    }
    T newNumerator = numerator * other.denominator;
    T newDenominator = denominator * other.numerator;
    return ECRational(newNumerator, newDenominator);
}

// Accessor for numerator
template <class T>
const T &ECRational<T>::GetNumerator() const {
    return numerator;
}

// Accessor for denominator
template <class T>
const T &ECRational<T>::GetDenominator() const {
    return denominator;
}

// Explicit template instantiation (if needed)
template class ECRational<int>; // Add for other types if necessary

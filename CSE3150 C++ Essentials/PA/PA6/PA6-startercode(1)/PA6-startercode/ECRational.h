//
//  ECRational.h
//  
//
//  Created by Yufeng Wu on 1/7/23.
//

#ifndef ECRational_h
#define ECRational_h

// *****************************************************************
// Generic rational of two quantities (e.g. integers, floating point, complex number, or polynomials)
// Assume the quantity class T supports (i) default constructor and copy constructor, (ii) assignment operator, and (iii) arithmetic operators: +, -, * and /
template <class T>
class ECRational
{
public:
    // Default constructor
    ECRational() {}
    
    // Constructor with numerator and denominator
    ECRational(const T &numeratorIn, const T &denominatorIn);
    
    // Copy constructor
    ECRational(const ECRational<T> &other);
    
    // Assignment operator
    ECRational<T>& operator=(const ECRational<T> &other);
    
    // Arithmetic operators
    ECRational<T> operator+(const ECRational<T> &other) const;
    ECRational<T> operator-(const ECRational<T> &other) const;
    ECRational<T> operator*(const ECRational<T> &other) const;
    ECRational<T> operator/(const ECRational<T> &other) const;

    // Access numerator and denominator
    const T &GetNumerator() const; 
    const T &GetDenominator() const;
    
private:
    T numerator;   // Numerator of the rational number
    T denominator; // Denominator of the rational number
};

#endif /* ECRational_h */

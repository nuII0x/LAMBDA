// -*- C++ -*-
#ifndef WEXACTS_CORE_NUMBER_THEORY_H
#define WEXACTS_CORE_NUMBER_THEORY_H

#include <cmath>
#include <stdexcept>

namespace wrs {

struct reduced_fraction {
  int numerator;
  int denominator;
};

// Returns the greatest common divisor (GCD) of two integers.
// The result is always non-negative.
inline int gcd(int a, int b) {
  a = std::abs(a);
  b = std::abs(b);

  while (b != 0) {
    const int remainder = a % b;
    a = b;
    b = remainder;
  }

  return a;
}

// Simplifies a fraction in-place.
// Returns `false` only if the denominator starts as zero.
inline bool convertToLowestTerms(int& numerator, int& denominator) {
  if (denominator == 0) {
    return false;
  }

  if (numerator == 0) {
    denominator = 1;
    return true;
  }

  const int greatest = gcd(numerator, denominator);
  numerator /= greatest;
  denominator /= greatest;

  if (denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }

  return true;
}

// Returns a reduced fraction as a value object instead of mutating arguments.
inline reduced_fraction reduceFraction(int numerator, int denominator) {
  if (!convertToLowestTerms(numerator, denominator)) {
    throw std::invalid_argument("reduceFraction expects a non-zero denominator");
  }

  return {numerator, denominator};
}

// Checks whether a number is prime.
inline bool isPrime(int num) {
  if (num < 2) {
    return false;
  }

  for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
      return false;
    }
  }

  return true;
}

}  // namespace wrs

#endif  // WEXACTS_CORE_NUMBER_THEORY_H

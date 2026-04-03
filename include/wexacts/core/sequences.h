// -*- C++ -*-
#ifndef WEXACTS_CORE_SEQUENCES_H
#define WEXACTS_CORE_SEQUENCES_H

#include <cmath>
#include <stdexcept>

namespace wrs {

struct arithmetic_progression_summary {
  double first_term;
  int term_index;
  double ratio;
  double nth_term;
  double sum_until_n;
};

struct geometric_progression_summary {
  double first_term;
  int term_index;
  double ratio;
  double nth_term;
  double sum_until_n;
  double product_until_n;
};

// Returns the n-th Fibonacci number using 1-based positions.
inline int goldenSequence(int n) {
  if (n <= 0) {
    return 0;
  }

  if (n == 1) {
    return 0;
  }

  if (n == 2) {
    return 1;
  }

  int previous = 0;
  int current = 1;
  for (int i = 3; i <= n; ++i) {
    const int next = previous + current;
    previous = current;
    current = next;
  }

  return current;
}

// Returns the n-th term of an arithmetic progression.
inline double PAn(double A1, int n, double r) {
  if (n <= 0) {
    throw std::invalid_argument("PAn expects n >= 1");
  }

  return A1 + ((n - 1) * r);
}

// Returns the middle value around a term in an arithmetic progression.
inline double maPA(double Ak, double r) {
  return ((Ak - r) + (Ak + r)) / 2.0;
}

// Returns the sum of the first `n` terms of an arithmetic progression.
inline double sumPA(double A1, int n, double r) {
  if (n <= 0) {
    return 0.0;
  }

  const double An = PAn(A1, n, r);
  return ((A1 + An) * n) / 2.0;
}

// Returns the n-th term of a geometric progression.
inline double PGn(double A1, int n, double q) {
  if (n <= 0) {
    throw std::invalid_argument("PGn expects n >= 1");
  }

  return A1 * std::pow(q, n - 1);
}

// Returns the sum of the first `n` terms of a geometric progression.
inline double sumPG(double A1, int n, double q) {
  if (n <= 0) {
    return 0.0;
  }

  if (q == 1.0) {
    return A1 * n;
  }

  return A1 * ((std::pow(q, n) - 1.0) / (q - 1.0));
}

// Returns the geometric mean around `Ak` in a geometric progression.
inline double modPG(double Ak, double q) {
  if (q == 0.0) {
    throw std::domain_error("modPG expects a non-zero ratio");
  }

  const double radicand = (Ak / q) * (Ak * q);
  if (radicand < 0.0) {
    throw std::domain_error("modPG produced a negative radicand");
  }

  return std::sqrt(radicand);
}

// Returns the product of the first `n` terms of a geometric progression.
inline double prodPG(double A1, int n, double q) {
  if (n <= 0) {
    return 0.0;
  }

  const double An = PGn(A1, n, q);
  return std::sqrt(std::pow(A1 * An, n));
}

inline arithmetic_progression_summary describeArithmeticProgression(double A1, int n, double r) {
  return {A1, n, r, PAn(A1, n, r), sumPA(A1, n, r)};
}

inline geometric_progression_summary describeGeometricProgression(double A1, int n, double q) {
  return {A1, n, q, PGn(A1, n, q), sumPG(A1, n, q), prodPG(A1, n, q)};
}

}  // namespace wrs

#endif  // WEXACTS_CORE_SEQUENCES_H

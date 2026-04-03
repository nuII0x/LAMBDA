// -*- C++ -*-
#ifndef WEXACTS_CORE_ALGEBRA_H
#define WEXACTS_CORE_ALGEBRA_H

#include <cmath>
#include <limits>
#include <stdexcept>

namespace wrs {

enum class quadratic_root_kind {
  no_real_roots,
  one_real_root,
  two_real_roots,
};

enum class linear_equation_kind {
  no_solution,
  one_solution,
  infinitely_many_solutions,
};

enum class linear_system_kind {
  no_solution,
  one_solution,
  infinitely_many_solutions,
};

struct quadratic_solution {
  double a;
  double b;
  double c;
  double discriminant;
  double x1;
  double x2;
  quadratic_root_kind root_kind;
};

struct linear_equation_solution {
  double a;
  double b;
  double x;
  linear_equation_kind kind;
};

struct quadratic_vertex {
  double a;
  double b;
  double c;
  double x;
  double y;
};

struct linear_system_2x2_solution {
  double a1;
  double b1;
  double c1;
  double a2;
  double b2;
  double c2;
  double determinant;
  double determinant_x;
  double determinant_y;
  double x;
  double y;
  linear_system_kind kind;
};

inline bool isNearlyZero(double value, double epsilon = 1e-12) {
  return std::abs(value) <= epsilon;
}

inline quadratic_solution solveQuadraticEquation(double a, double b, double c) {
  if (isNearlyZero(a)) {
    throw std::invalid_argument("solveQuadraticEquation expects a != 0");
  }

  const double discriminant = (b * b) - (4.0 * a * c);
  const double nan = std::numeric_limits<double>::quiet_NaN();

  if (discriminant < 0.0) {
    return {a, b, c, discriminant, nan, nan, quadratic_root_kind::no_real_roots};
  }

  if (isNearlyZero(discriminant)) {
    const double repeated_root = (-b) / (2.0 * a);
    return {a, b, c, 0.0, repeated_root, repeated_root, quadratic_root_kind::one_real_root};
  }

  const double root_delta = std::sqrt(discriminant);
  const double denominator = 2.0 * a;
  const double x1 = (-b + root_delta) / denominator;
  const double x2 = (-b - root_delta) / denominator;
  return {a, b, c, discriminant, x1, x2, quadratic_root_kind::two_real_roots};
}

inline linear_equation_solution solveLinearEquation(double a, double b) {
  const double nan = std::numeric_limits<double>::quiet_NaN();

  if (isNearlyZero(a) && isNearlyZero(b)) {
    return {a, b, nan, linear_equation_kind::infinitely_many_solutions};
  }

  if (isNearlyZero(a)) {
    return {a, b, nan, linear_equation_kind::no_solution};
  }

  return {a, b, (-b) / a, linear_equation_kind::one_solution};
}

inline quadratic_vertex solveQuadraticVertex(double a, double b, double c) {
  if (isNearlyZero(a)) {
    throw std::invalid_argument("solveQuadraticVertex expects a != 0");
  }

  const double x = (-b) / (2.0 * a);
  const double y = (a * x * x) + (b * x) + c;
  return {a, b, c, x, y};
}

inline linear_system_2x2_solution solveLinearSystem2x2(double a1,
                                                       double b1,
                                                       double c1,
                                                       double a2,
                                                       double b2,
                                                       double c2) {
  const double determinant = (a1 * b2) - (a2 * b1);
  const double determinant_x = (c1 * b2) - (c2 * b1);
  const double determinant_y = (a1 * c2) - (a2 * c1);
  const double nan = std::numeric_limits<double>::quiet_NaN();

  if (!isNearlyZero(determinant)) {
    return {a1,
            b1,
            c1,
            a2,
            b2,
            c2,
            determinant,
            determinant_x,
            determinant_y,
            determinant_x / determinant,
            determinant_y / determinant,
            linear_system_kind::one_solution};
  }

  if (isNearlyZero(determinant_x) && isNearlyZero(determinant_y)) {
    return {a1,
            b1,
            c1,
            a2,
            b2,
            c2,
            determinant,
            determinant_x,
            determinant_y,
            nan,
            nan,
            linear_system_kind::infinitely_many_solutions};
  }

  return {a1,
          b1,
          c1,
          a2,
          b2,
          c2,
          determinant,
          determinant_x,
          determinant_y,
          nan,
          nan,
          linear_system_kind::no_solution};
}

inline int realRootCount(const quadratic_solution& solution) {
  switch (solution.root_kind) {
    case quadratic_root_kind::no_real_roots:
      return 0;
    case quadratic_root_kind::one_real_root:
      return 1;
    case quadratic_root_kind::two_real_roots:
      return 2;
  }

  return 0;
}

inline int linearEquationSolutionCount(const linear_equation_solution& solution) {
  switch (solution.kind) {
    case linear_equation_kind::no_solution:
      return 0;
    case linear_equation_kind::one_solution:
      return 1;
    case linear_equation_kind::infinitely_many_solutions:
      return -1;
  }

  return 0;
}

inline int linearSystemSolutionCount(const linear_system_2x2_solution& solution) {
  switch (solution.kind) {
    case linear_system_kind::no_solution:
      return 0;
    case linear_system_kind::one_solution:
      return 1;
    case linear_system_kind::infinitely_many_solutions:
      return -1;
  }

  return 0;
}

}  // namespace wrs

#endif  // WEXACTS_CORE_ALGEBRA_H

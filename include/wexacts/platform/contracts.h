// -*- C++ -*-
#ifndef WEXACTS_PLATFORM_CONTRACTS_H
#define WEXACTS_PLATFORM_CONTRACTS_H

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "../education/high_school_catalog.h"

namespace wrs {

struct solve_request {
  std::string skill_id;
  std::map<std::string, double> numeric_inputs;
  std::map<std::string, std::vector<double>> numeric_list_inputs;
  bool include_explanation;

  solve_request() : include_explanation(true) {}
};

struct solve_response {
  std::string skill_id;
  bool success;
  std::map<std::string, double> numeric_outputs;
  std::map<std::string, std::vector<double>> numeric_list_outputs;
  std::vector<solution_step> steps;
  std::string message;

  solve_response() : success(false) {}
};

inline double requiredNumericInput(const solve_request& request, const std::string& key) {
  std::map<std::string, double>::const_iterator found = request.numeric_inputs.find(key);
  if (found == request.numeric_inputs.end()) {
    throw std::invalid_argument("missing numeric input: " + key);
  }

  return found->second;
}

inline const std::vector<double>& requiredNumericListInput(const solve_request& request, const std::string& key) {
  std::map<std::string, std::vector<double>>::const_iterator found = request.numeric_list_inputs.find(key);
  if (found == request.numeric_list_inputs.end()) {
    throw std::invalid_argument("missing numeric list input: " + key);
  }

  return found->second;
}

inline solve_response solveRequest(const solve_request& request) {
  solve_response response;
  response.skill_id = request.skill_id;

  if (request.skill_id == "algebra.linear_equation.root") {
    const double a = requiredNumericInput(request, "a");
    const double b = requiredNumericInput(request, "b");

    if (request.include_explanation) {
      const explained_linear_equation_solution explained = explainLinearEquation(a, b);
      response.success = true;
      response.numeric_outputs["solution_count"] = linearEquationSolutionCount(explained.values);
      if (linearEquationSolutionCount(explained.values) == 1) {
        response.numeric_outputs["x"] = explained.values.x;
      }
      response.steps = explained.steps;
      response.message = "Linear equation solved.";
      return response;
    }

    const linear_equation_solution solution = solveLinearEquation(a, b);
    response.success = true;
    response.numeric_outputs["solution_count"] = linearEquationSolutionCount(solution);
    if (linearEquationSolutionCount(solution) == 1) {
      response.numeric_outputs["x"] = solution.x;
    }
    response.message = "Linear equation solved.";
    return response;
  }

  if (request.skill_id == "algebra.quadratic.roots") {
    const double a = requiredNumericInput(request, "a");
    const double b = requiredNumericInput(request, "b");
    const double c = requiredNumericInput(request, "c");

    if (request.include_explanation) {
      const explained_quadratic_solution explained = explainQuadraticEquation(a, b, c);
      response.success = true;
      response.numeric_outputs["delta"] = explained.values.discriminant;
      response.numeric_outputs["real_root_count"] = realRootCount(explained.values);
      if (realRootCount(explained.values) > 0) {
        response.numeric_outputs["x1"] = explained.values.x1;
        response.numeric_outputs["x2"] = explained.values.x2;
      }
      response.steps = explained.steps;
      response.message = "Quadratic equation solved.";
      return response;
    }

    const quadratic_solution solution = solveQuadraticEquation(a, b, c);
    response.success = true;
    response.numeric_outputs["delta"] = solution.discriminant;
    response.numeric_outputs["real_root_count"] = realRootCount(solution);
    if (realRootCount(solution) > 0) {
      response.numeric_outputs["x1"] = solution.x1;
      response.numeric_outputs["x2"] = solution.x2;
    }
    response.message = "Quadratic equation solved.";
    return response;
  }

  if (request.skill_id == "algebra.linear_system_2x2") {
    const double a1 = requiredNumericInput(request, "a1");
    const double b1 = requiredNumericInput(request, "b1");
    const double c1 = requiredNumericInput(request, "c1");
    const double a2 = requiredNumericInput(request, "a2");
    const double b2 = requiredNumericInput(request, "b2");
    const double c2 = requiredNumericInput(request, "c2");

    if (request.include_explanation) {
      const explained_linear_system_2x2_solution explained =
          explainLinearSystem2x2(a1, b1, c1, a2, b2, c2);
      response.success = true;
      response.numeric_outputs["D"] = explained.values.determinant;
      response.numeric_outputs["Dx"] = explained.values.determinant_x;
      response.numeric_outputs["Dy"] = explained.values.determinant_y;
      response.numeric_outputs["solution_count"] = linearSystemSolutionCount(explained.values);
      if (linearSystemSolutionCount(explained.values) == 1) {
        response.numeric_outputs["x"] = explained.values.x;
        response.numeric_outputs["y"] = explained.values.y;
      }
      response.steps = explained.steps;
      response.message = "Linear system solved.";
      return response;
    }

    const linear_system_2x2_solution solution = solveLinearSystem2x2(a1, b1, c1, a2, b2, c2);
    response.success = true;
    response.numeric_outputs["D"] = solution.determinant;
    response.numeric_outputs["Dx"] = solution.determinant_x;
    response.numeric_outputs["Dy"] = solution.determinant_y;
    response.numeric_outputs["solution_count"] = linearSystemSolutionCount(solution);
    if (linearSystemSolutionCount(solution) == 1) {
      response.numeric_outputs["x"] = solution.x;
      response.numeric_outputs["y"] = solution.y;
    }
    response.message = "Linear system solved.";
    return response;
  }

  if (request.skill_id == "functions.quadratic.vertex") {
    const double a = requiredNumericInput(request, "a");
    const double b = requiredNumericInput(request, "b");
    const double c = requiredNumericInput(request, "c");

    if (request.include_explanation) {
      const explained_quadratic_vertex explained = explainQuadraticVertex(a, b, c);
      response.success = true;
      response.numeric_outputs["xv"] = explained.values.x;
      response.numeric_outputs["yv"] = explained.values.y;
      response.steps = explained.steps;
      response.message = "Quadratic vertex computed.";
      return response;
    }

    const quadratic_vertex vertex = solveQuadraticVertex(a, b, c);
    response.success = true;
    response.numeric_outputs["xv"] = vertex.x;
    response.numeric_outputs["yv"] = vertex.y;
    response.message = "Quadratic vertex computed.";
    return response;
  }

  if (request.skill_id == "analytic_geometry.distance_between_points") {
    const double x1 = requiredNumericInput(request, "x1");
    const double y1 = requiredNumericInput(request, "y1");
    const double x2 = requiredNumericInput(request, "x2");
    const double y2 = requiredNumericInput(request, "y2");

    if (request.include_explanation) {
      const explained_distance_between_points explained = explainDistanceBetweenPoints(x1, y1, x2, y2);
      response.success = true;
      response.numeric_outputs["dx"] = explained.values.delta_x;
      response.numeric_outputs["dy"] = explained.values.delta_y;
      response.numeric_outputs["distance"] = explained.values.distance;
      response.steps = explained.steps;
      response.message = "Distance computed.";
      return response;
    }

    const distance_between_points_result result = distanceBetweenPoints(x1, y1, x2, y2);
    response.success = true;
    response.numeric_outputs["dx"] = result.delta_x;
    response.numeric_outputs["dy"] = result.delta_y;
    response.numeric_outputs["distance"] = result.distance;
    response.message = "Distance computed.";
    return response;
  }

  if (request.skill_id == "analytic_geometry.midpoint_between_points") {
    const double x1 = requiredNumericInput(request, "x1");
    const double y1 = requiredNumericInput(request, "y1");
    const double x2 = requiredNumericInput(request, "x2");
    const double y2 = requiredNumericInput(request, "y2");

    const midpoint_result result = midpointBetweenPoints(x1, y1, x2, y2);
    response.success = true;
    response.numeric_outputs["xm"] = result.midpoint.x;
    response.numeric_outputs["ym"] = result.midpoint.y;
    response.message = "Midpoint computed.";
    return response;
  }

  if (request.skill_id == "sequences.pa.nth_term") {
    const double A1 = requiredNumericInput(request, "A1");
    const int n = static_cast<int>(requiredNumericInput(request, "n"));
    const double r = requiredNumericInput(request, "r");
    const arithmetic_progression_summary summary = describeArithmeticProgression(A1, n, r);

    response.success = true;
    response.numeric_outputs["An"] = summary.nth_term;
    response.numeric_outputs["Sn"] = summary.sum_until_n;
    response.message = "Arithmetic progression analyzed.";
    return response;
  }

  if (request.skill_id == "sequences.pa.sum") {
    const double A1 = requiredNumericInput(request, "A1");
    const int n = static_cast<int>(requiredNumericInput(request, "n"));
    const double r = requiredNumericInput(request, "r");

    response.success = true;
    response.numeric_outputs["Sn"] = sumPA(A1, n, r);
    response.message = "Arithmetic progression sum computed.";
    return response;
  }

  if (request.skill_id == "sequences.pg.nth_term") {
    const double A1 = requiredNumericInput(request, "A1");
    const int n = static_cast<int>(requiredNumericInput(request, "n"));
    const double q = requiredNumericInput(request, "q");
    const geometric_progression_summary summary = describeGeometricProgression(A1, n, q);

    response.success = true;
    response.numeric_outputs["An"] = summary.nth_term;
    response.numeric_outputs["Sn"] = summary.sum_until_n;
    response.numeric_outputs["Pn"] = summary.product_until_n;
    response.message = "Geometric progression analyzed.";
    return response;
  }

  if (request.skill_id == "sequences.pg.sum") {
    const double A1 = requiredNumericInput(request, "A1");
    const int n = static_cast<int>(requiredNumericInput(request, "n"));
    const double q = requiredNumericInput(request, "q");

    response.success = true;
    response.numeric_outputs["Sn"] = sumPG(A1, n, q);
    response.message = "Geometric progression sum computed.";
    return response;
  }

  if (request.skill_id == "sequences.pg.product") {
    const double A1 = requiredNumericInput(request, "A1");
    const int n = static_cast<int>(requiredNumericInput(request, "n"));
    const double q = requiredNumericInput(request, "q");

    response.success = true;
    response.numeric_outputs["Pn"] = prodPG(A1, n, q);
    response.message = "Geometric progression product computed.";
    return response;
  }

  if (request.skill_id == "number_theory.gcd") {
    const int a = static_cast<int>(requiredNumericInput(request, "a"));
    const int b = static_cast<int>(requiredNumericInput(request, "b"));

    response.success = true;
    response.numeric_outputs["gcd"] = gcd(a, b);
    response.message = "Greatest common divisor computed.";
    return response;
  }

  if (request.skill_id == "number_theory.reduce_fraction") {
    int numerator = static_cast<int>(requiredNumericInput(request, "numerator"));
    int denominator = static_cast<int>(requiredNumericInput(request, "denominator"));
    const bool ok = convertToLowestTerms(numerator, denominator);
    response.success = ok;
    if (ok) {
      response.numeric_outputs["reduced_numerator"] = numerator;
      response.numeric_outputs["reduced_denominator"] = denominator;
      response.message = "Fraction reduced.";
      return response;
    }

    response.message = "Denominator must be non-zero.";
    return response;
  }

  if (request.skill_id == "number_theory.is_prime") {
    const int n = static_cast<int>(requiredNumericInput(request, "n"));

    response.success = true;
    response.numeric_outputs["is_prime"] = isPrime(n) ? 1.0 : 0.0;
    response.message = "Prime check completed.";
    return response;
  }

  if (request.skill_id == "sequences.fibonacci.term") {
    const int n = static_cast<int>(requiredNumericInput(request, "n"));

    response.success = true;
    response.numeric_outputs["term"] = goldenSequence(n);
    response.message = "Fibonacci term computed.";
    return response;
  }

  if (request.skill_id == "statistics.central_tendency") {
    const std::vector<double>& data = requiredNumericListInput(request, "data");

    if (request.include_explanation) {
      const explained_central_tendency explained = explainCentralTendency(data);
      response.success = true;
      response.numeric_outputs["mean"] = explained.values.mean;
      response.numeric_outputs["median"] = explained.values.median;
      response.numeric_list_outputs["modes"] = explained.values.modes;
      response.steps = explained.steps;
      response.message = "Central tendency computed.";
      return response;
    }

    const central_tendency_summary summary = describeCentralTendency(data);
    response.success = true;
    response.numeric_outputs["mean"] = summary.mean;
    response.numeric_outputs["median"] = summary.median;
    response.numeric_list_outputs["modes"] = summary.modes;
    response.message = "Central tendency computed.";
    return response;
  }

  const math_skill* skill = highSchoolCatalog().find(request.skill_id);
  if (skill != 0) {
    response.message = "Skill exists in the catalog but has no platform solver yet.";
    return response;
  }

  response.message = "Unknown skill id.";
  return response;
}

}  // namespace wrs

#endif  // WEXACTS_PLATFORM_CONTRACTS_H

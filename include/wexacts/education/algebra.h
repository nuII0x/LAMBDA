// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_ALGEBRA_H
#define WEXACTS_EDUCATION_ALGEBRA_H

#include <vector>

#include "../core/algebra.h"
#include "format.h"
#include "skill.h"
#include "step.h"

namespace wrs {

struct explained_linear_equation_solution {
  linear_equation_solution values;
  std::vector<solution_step> steps;
};

struct explained_linear_system_2x2_solution {
  linear_system_2x2_solution values;
  std::vector<solution_step> steps;
};

inline explained_linear_equation_solution explainLinearEquation(double a, double b) {
  explained_linear_equation_solution explained;
  explained.values = solveLinearEquation(a, b);

  explained.steps.push_back({
      "Read the equation",
      formatNumber(a) + "x + " + formatNumber(b) + " = 0",
      "We identify the equation in the form ax + b = 0."});

  if (explained.values.kind == linear_equation_kind::infinitely_many_solutions) {
    explained.steps.push_back({
        "Classify the equation",
        "0 = 0",
        "Both coefficients vanish, so any real number satisfies the equation."});
    return explained;
  }

  if (explained.values.kind == linear_equation_kind::no_solution) {
    explained.steps.push_back({
        "Classify the equation",
        formatNumber(b) + " = 0",
        "The x term disappears but the constant does not, so there is no solution."});
    return explained;
  }

  explained.steps.push_back({
      "Isolate x",
      "x = -b / a = " + formatNumber(explained.values.x),
      "We move the constant term and divide by the coefficient of x."});
  return explained;
}

inline explained_linear_system_2x2_solution explainLinearSystem2x2(double a1,
                                                                   double b1,
                                                                   double c1,
                                                                   double a2,
                                                                   double b2,
                                                                   double c2) {
  explained_linear_system_2x2_solution explained;
  explained.values = solveLinearSystem2x2(a1, b1, c1, a2, b2, c2);

  explained.steps.push_back({
      "Read the system",
      formatNumber(a1) + "x + " + formatNumber(b1) + "y = " + formatNumber(c1) + " and " +
          formatNumber(a2) + "x + " + formatNumber(b2) + "y = " + formatNumber(c2),
      "We identify the coefficients of the two equations."});

  explained.steps.push_back({
      "Compute determinants",
      "D = " + formatNumber(explained.values.determinant) + ", Dx = " +
          formatNumber(explained.values.determinant_x) + ", Dy = " +
          formatNumber(explained.values.determinant_y),
      "Cramer's rule uses the main determinant and the substituted determinants."});

  if (explained.values.kind == linear_system_kind::infinitely_many_solutions) {
    explained.steps.push_back({
        "Classify the system",
        "D = 0, Dx = 0, Dy = 0",
        "The equations represent the same line, so the system has infinitely many solutions."});
    return explained;
  }

  if (explained.values.kind == linear_system_kind::no_solution) {
    explained.steps.push_back({
        "Classify the system",
        "D = 0 with Dx or Dy different from 0",
        "The equations are inconsistent, so the system has no solution."});
    return explained;
  }

  explained.steps.push_back({
      "Apply Cramer's rule",
      "x = Dx / D = " + formatNumber(explained.values.x) + ", y = Dy / D = " +
          formatNumber(explained.values.y),
      "Because the main determinant is not zero, the system has a unique solution."});
  return explained;
}

inline math_skill linearEquationSkill() {
  math_skill skill;
  skill.id = "algebra.linear_equation.root";
  skill.title = "Root of a first-degree equation";
  skill.area = "algebra";
  skill.summary = "Solves ax + b = 0 and classifies whether the equation has zero, one or infinitely many solutions.";
  skill.required_inputs.push_back("a");
  skill.required_inputs.push_back("b");
  skill.outputs.push_back("x");
  skill.outputs.push_back("solution_count");
  skill.formulas.push_back("ax + b = 0");
  skill.formulas.push_back("x = -b / a when a != 0");
  skill.status = skill_status::explained;
  return skill;
}

inline math_skill linearSystem2x2Skill() {
  math_skill skill;
  skill.id = "algebra.linear_system_2x2";
  skill.title = "Linear system 2x2";
  skill.area = "algebra";
  skill.summary = "Solves a system with two equations and two unknowns using determinants.";
  skill.required_inputs.push_back("a1");
  skill.required_inputs.push_back("b1");
  skill.required_inputs.push_back("c1");
  skill.required_inputs.push_back("a2");
  skill.required_inputs.push_back("b2");
  skill.required_inputs.push_back("c2");
  skill.outputs.push_back("x");
  skill.outputs.push_back("y");
  skill.outputs.push_back("solution_count");
  skill.formulas.push_back("D = a1b2 - a2b1");
  skill.formulas.push_back("x = Dx / D, y = Dy / D when D != 0");
  skill.related_skills.push_back("algebra.linear_equation.root");
  skill.related_skills.push_back("linear_algebra.matrix.rref");
  skill.status = skill_status::explained;
  return skill;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_ALGEBRA_H

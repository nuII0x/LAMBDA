// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_QUADRATIC_H
#define WEXACTS_EDUCATION_QUADRATIC_H

#include <vector>

#include "../core/algebra.h"
#include "format.h"
#include "skill.h"
#include "step.h"

namespace wrs {

struct explained_quadratic_solution {
  quadratic_solution values;
  std::vector<solution_step> steps;
};

inline explained_quadratic_solution explainQuadraticEquation(double a, double b, double c) {
  explained_quadratic_solution explained;
  explained.values = solveQuadraticEquation(a, b, c);

  explained.steps.push_back({
      "Identify coefficients",
      "a = " + formatNumber(a) + ", b = " + formatNumber(b) + ", c = " + formatNumber(c),
      "We read the quadratic equation in the form ax^2 + bx + c = 0."});

  explained.steps.push_back({
      "Compute discriminant",
      "delta = b^2 - 4ac = " + formatNumber(explained.values.discriminant),
      "The discriminant tells us how many real roots the equation has."});

  if (explained.values.root_kind == quadratic_root_kind::no_real_roots) {
    explained.steps.push_back({
        "Classify roots",
        "delta < 0",
        "Because the discriminant is negative, there are no real roots."});
    return explained;
  }

  if (explained.values.root_kind == quadratic_root_kind::one_real_root) {
    explained.steps.push_back({
        "Apply Bhaskara formula",
        "x = -b / (2a) = " + formatNumber(explained.values.x1),
        "With delta equal to zero, both roots collapse into one repeated real root."});
    return explained;
  }

  explained.steps.push_back({
      "Apply Bhaskara formula",
      "x1 = " + formatNumber(explained.values.x1) + ", x2 = " + formatNumber(explained.values.x2),
      "With positive discriminant, the equation has two distinct real roots."});
  return explained;
}

inline math_skill quadraticRootsSkill() {
  math_skill skill;
  skill.id = "algebra.quadratic.roots";
  skill.title = "Roots of a quadratic equation";
  skill.area = "algebra";
  skill.summary = "Solves ax^2 + bx + c = 0 and classifies the number of real roots.";
  skill.required_inputs.push_back("a");
  skill.required_inputs.push_back("b");
  skill.required_inputs.push_back("c");
  skill.outputs.push_back("delta");
  skill.outputs.push_back("x1");
  skill.outputs.push_back("x2");
  skill.outputs.push_back("real_root_count");
  skill.formulas.push_back("delta = b^2 - 4ac");
  skill.formulas.push_back("x = (-b +- sqrt(delta)) / (2a)");
  skill.validation_rules.push_back("a must be different from zero");
  skill.related_skills.push_back("functions.quadratic.vertex");
  skill.related_skills.push_back("algebra.linear_system_2x2");
  skill.status = skill_status::explained;
  return skill;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_QUADRATIC_H

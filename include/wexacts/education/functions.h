// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_FUNCTIONS_H
#define WEXACTS_EDUCATION_FUNCTIONS_H

#include <vector>

#include "../core/algebra.h"
#include "format.h"
#include "skill.h"
#include "step.h"

namespace wrs {

struct explained_quadratic_vertex {
  quadratic_vertex values;
  std::vector<solution_step> steps;
};

inline explained_quadratic_vertex explainQuadraticVertex(double a, double b, double c) {
  explained_quadratic_vertex explained;
  explained.values = solveQuadraticVertex(a, b, c);

  explained.steps.push_back({
      "Read the function",
      "f(x) = " + formatNumber(a) + "x^2 + " + formatNumber(b) + "x + " + formatNumber(c),
      "We identify the quadratic coefficients a, b and c."});

  explained.steps.push_back({
      "Compute the x-coordinate of the vertex",
      "xv = -b / (2a) = " + formatNumber(explained.values.x),
      "The vertex x-coordinate depends only on a and b."});

  explained.steps.push_back({
      "Evaluate the function at xv",
      "yv = f(xv) = " + formatNumber(explained.values.y),
      "Substituting xv into the function gives the y-coordinate of the vertex."});
  return explained;
}

inline math_skill quadraticVertexSkill() {
  math_skill skill;
  skill.id = "functions.quadratic.vertex";
  skill.title = "Vertex of a quadratic function";
  skill.area = "functions";
  skill.summary = "Computes the vertex coordinates of f(x) = ax^2 + bx + c.";
  skill.required_inputs.push_back("a");
  skill.required_inputs.push_back("b");
  skill.required_inputs.push_back("c");
  skill.outputs.push_back("xv");
  skill.outputs.push_back("yv");
  skill.formulas.push_back("xv = -b / (2a)");
  skill.formulas.push_back("yv = f(xv)");
  skill.validation_rules.push_back("a must be different from zero");
  skill.related_skills.push_back("algebra.quadratic.roots");
  skill.status = skill_status::explained;
  return skill;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_FUNCTIONS_H

// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_GEOMETRY_H
#define WEXACTS_EDUCATION_GEOMETRY_H

#include <vector>

#include "../core/geometry.h"
#include "format.h"
#include "skill.h"
#include "step.h"

namespace wrs {

struct explained_distance_between_points {
  distance_between_points_result values;
  std::vector<solution_step> steps;
};

inline explained_distance_between_points explainDistanceBetweenPoints(double x1,
                                                                     double y1,
                                                                     double x2,
                                                                     double y2) {
  explained_distance_between_points explained;
  explained.values = distanceBetweenPoints(x1, y1, x2, y2);

  explained.steps.push_back({
      "Read the points",
      "A(" + formatNumber(x1) + ", " + formatNumber(y1) + "), B(" + formatNumber(x2) + ", " +
          formatNumber(y2) + ")",
      "We identify the two points in the plane."});

  explained.steps.push_back({
      "Compute coordinate differences",
      "dx = " + formatNumber(explained.values.delta_x) + ", dy = " + formatNumber(explained.values.delta_y),
      "The distance formula uses the horizontal and vertical variations between the points."});

  explained.steps.push_back({
      "Apply the distance formula",
      "d = " + formatNumber(explained.values.distance),
      "We apply the Pythagorean relation to the coordinate differences."});
  return explained;
}

inline math_skill distanceBetweenPointsSkill() {
  math_skill skill;
  skill.id = "analytic_geometry.distance_between_points";
  skill.title = "Distance between two points";
  skill.area = "analytic_geometry";
  skill.summary = "Computes the Euclidean distance between two points in the plane.";
  skill.required_inputs.push_back("x1");
  skill.required_inputs.push_back("y1");
  skill.required_inputs.push_back("x2");
  skill.required_inputs.push_back("y2");
  skill.outputs.push_back("distance");
  skill.formulas.push_back("d = sqrt((x2 - x1)^2 + (y2 - y1)^2)");
  skill.status = skill_status::explained;
  return skill;
}

inline math_skill midpointBetweenPointsSkill() {
  math_skill skill;
  skill.id = "analytic_geometry.midpoint_between_points";
  skill.title = "Midpoint between two points";
  skill.area = "analytic_geometry";
  skill.summary = "Computes the midpoint of a segment in the plane.";
  skill.required_inputs.push_back("x1");
  skill.required_inputs.push_back("y1");
  skill.required_inputs.push_back("x2");
  skill.required_inputs.push_back("y2");
  skill.outputs.push_back("xm");
  skill.outputs.push_back("ym");
  skill.formulas.push_back("M = ((x1 + x2)/2, (y1 + y2)/2)");
  skill.status = skill_status::implemented;
  return skill;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_GEOMETRY_H

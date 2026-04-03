// -*- C++ -*-
#ifndef WEXACTS_CORE_GEOMETRY_H
#define WEXACTS_CORE_GEOMETRY_H

#include <cmath>

namespace wrs {

struct point_2d {
  double x;
  double y;
};

struct distance_between_points_result {
  point_2d first;
  point_2d second;
  double delta_x;
  double delta_y;
  double distance;
};

struct midpoint_result {
  point_2d first;
  point_2d second;
  point_2d midpoint;
};

inline distance_between_points_result distanceBetweenPoints(double x1, double y1, double x2, double y2) {
  const double delta_x = x2 - x1;
  const double delta_y = y2 - y1;
  return {{x1, y1}, {x2, y2}, delta_x, delta_y, std::sqrt((delta_x * delta_x) + (delta_y * delta_y))};
}

inline midpoint_result midpointBetweenPoints(double x1, double y1, double x2, double y2) {
  return {{x1, y1}, {x2, y2}, {(x1 + x2) / 2.0, (y1 + y2) / 2.0}};
}

}  // namespace wrs

#endif  // WEXACTS_CORE_GEOMETRY_H

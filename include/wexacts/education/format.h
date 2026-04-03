// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_FORMAT_H
#define WEXACTS_EDUCATION_FORMAT_H

#include <sstream>
#include <string>
#include <vector>

namespace wrs {

inline std::string formatNumber(double value) {
  std::ostringstream out;
  out << value;
  return out.str();
}

inline std::string formatNumberList(const std::vector<double>& values) {
  std::ostringstream out;
  out << "[";
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i != 0) {
      out << ", ";
    }
    out << values[i];
  }
  out << "]";
  return out.str();
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_FORMAT_H

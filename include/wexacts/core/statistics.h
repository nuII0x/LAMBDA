// -*- C++ -*-
#ifndef WEXACTS_CORE_STATISTICS_H
#define WEXACTS_CORE_STATISTICS_H

#include <algorithm>
#include <map>
#include <stdexcept>
#include <vector>

namespace wrs {

struct central_tendency_summary {
  double mean;
  double median;
  std::vector<double> modes;
  bool has_mode;
};

inline double mean(const std::vector<double>& values) {
  if (values.empty()) {
    throw std::invalid_argument("mean expects at least one value");
  }

  double total = 0.0;
  for (std::vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {
    total += *it;
  }

  return total / static_cast<double>(values.size());
}

inline double median(const std::vector<double>& values) {
  if (values.empty()) {
    throw std::invalid_argument("median expects at least one value");
  }

  std::vector<double> sorted = values;
  std::sort(sorted.begin(), sorted.end());

  const std::size_t middle = sorted.size() / 2;
  if (sorted.size() % 2 == 1) {
    return sorted[middle];
  }

  return (sorted[middle - 1] + sorted[middle]) / 2.0;
}

inline std::vector<double> modes(const std::vector<double>& values) {
  if (values.empty()) {
    throw std::invalid_argument("modes expects at least one value");
  }

  std::map<double, int> frequencies;
  int highest_frequency = 0;

  for (std::vector<double>::const_iterator it = values.begin(); it != values.end(); ++it) {
    const int count = ++frequencies[*it];
    if (count > highest_frequency) {
      highest_frequency = count;
    }
  }

  std::vector<double> result;
  if (highest_frequency <= 1) {
    return result;
  }

  for (std::map<double, int>::const_iterator it = frequencies.begin(); it != frequencies.end(); ++it) {
    if (it->second == highest_frequency) {
      result.push_back(it->first);
    }
  }

  return result;
}

inline central_tendency_summary describeCentralTendency(const std::vector<double>& values) {
  const std::vector<double> mode_values = modes(values);
  return {mean(values), median(values), mode_values, !mode_values.empty()};
}

}  // namespace wrs

#endif  // WEXACTS_CORE_STATISTICS_H

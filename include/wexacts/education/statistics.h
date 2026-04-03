// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_STATISTICS_H
#define WEXACTS_EDUCATION_STATISTICS_H

#include <vector>

#include "../core/statistics.h"
#include "format.h"
#include "skill.h"
#include "step.h"

namespace wrs {

struct explained_central_tendency {
  central_tendency_summary values;
  std::vector<solution_step> steps;
};

inline explained_central_tendency explainCentralTendency(const std::vector<double>& values) {
  explained_central_tendency explained;
  explained.values = describeCentralTendency(values);

  explained.steps.push_back({
      "Read the dataset",
      formatNumberList(values),
      "We start from the list of observed values."});

  explained.steps.push_back({
      "Compute the mean",
      "mean = " + formatNumber(explained.values.mean),
      "The mean is the sum of all values divided by the number of observations."});

  explained.steps.push_back({
      "Compute the median",
      "median = " + formatNumber(explained.values.median),
      "The median is the central value after sorting the dataset."});

  if (explained.values.has_mode) {
    explained.steps.push_back({
        "Compute the mode",
        "mode = " + formatNumberList(explained.values.modes),
        "The mode is the value or values with the highest frequency."});
  } else {
    explained.steps.push_back({
        "Compute the mode",
        "no mode",
        "No value repeats more than the others, so the dataset is amodal."});
  }

  return explained;
}

inline math_skill centralTendencySkill() {
  math_skill skill;
  skill.id = "statistics.central_tendency";
  skill.title = "Central tendency";
  skill.area = "statistics";
  skill.summary = "Computes mean, median and mode for a numeric dataset.";
  skill.required_inputs.push_back("data[]");
  skill.outputs.push_back("mean");
  skill.outputs.push_back("median");
  skill.outputs.push_back("modes[]");
  skill.validation_rules.push_back("The dataset must contain at least one value");
  skill.status = skill_status::explained;
  return skill;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_STATISTICS_H

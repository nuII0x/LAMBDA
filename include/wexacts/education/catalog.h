// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_CATALOG_H
#define WEXACTS_EDUCATION_CATALOG_H

#include <algorithm>
#include <string>
#include <vector>

#include "skill.h"

namespace wrs {

class skill_catalog {
 public:
  void add(const math_skill& skill) {
    skills_.push_back(skill);
  }

  const math_skill* find(const std::string& skill_id) const {
    for (std::vector<math_skill>::const_iterator it = skills_.begin(); it != skills_.end(); ++it) {
      if (it->id == skill_id) {
        return &(*it);
      }
    }

    return 0;
  }

  std::vector<const math_skill*> byArea(const std::string& area) const {
    std::vector<const math_skill*> filtered;
    for (std::vector<math_skill>::const_iterator it = skills_.begin(); it != skills_.end(); ++it) {
      if (it->area == area) {
        filtered.push_back(&(*it));
      }
    }

    return filtered;
  }

  const std::vector<math_skill>& all() const {
    return skills_;
  }

  bool empty() const {
    return skills_.empty();
  }

  std::size_t size() const {
    return skills_.size();
  }

 private:
  std::vector<math_skill> skills_;
};

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_CATALOG_H

// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_SKILL_H
#define WEXACTS_EDUCATION_SKILL_H

#include <string>
#include <vector>

namespace wrs {

enum class skill_status {
  planned,
  seeded,
  implemented,
  explained,
};

struct math_skill {
  std::string id;
  std::string title;
  std::string area;
  std::string summary;
  std::vector<std::string> required_inputs;
  std::vector<std::string> outputs;
  std::vector<std::string> formulas;
  std::vector<std::string> validation_rules;
  std::vector<std::string> related_skills;
  skill_status status;
};

inline const char* skillStatusName(skill_status status) {
  switch (status) {
    case skill_status::planned:
      return "planned";
    case skill_status::seeded:
      return "seeded";
    case skill_status::implemented:
      return "implemented";
    case skill_status::explained:
      return "explained";
  }

  return "planned";
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_SKILL_H

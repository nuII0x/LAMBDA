// -*- C++ -*-
#ifndef WEXACTS_EDUCATION_HIGH_SCHOOL_CATALOG_H
#define WEXACTS_EDUCATION_HIGH_SCHOOL_CATALOG_H

#include "algebra.h"
#include "catalog.h"
#include "functions.h"
#include "geometry.h"
#include "quadratic.h"
#include "statistics.h"

namespace wrs {

inline math_skill makeSkill(const char* id,
                            const char* title,
                            const char* area,
                            const char* summary,
                            skill_status status) {
  math_skill skill;
  skill.id = id;
  skill.title = title;
  skill.area = area;
  skill.summary = summary;
  skill.status = status;
  return skill;
}

inline skill_catalog buildHighSchoolCatalog() {
  skill_catalog catalog;

  math_skill gcd_skill = makeSkill(
      "number_theory.gcd",
      "Greatest common divisor",
      "number_theory",
      "Computes the greatest common divisor with the Euclidean algorithm.",
      skill_status::implemented);
  gcd_skill.required_inputs.push_back("a");
  gcd_skill.required_inputs.push_back("b");
  gcd_skill.outputs.push_back("gcd");
  gcd_skill.formulas.push_back("gcd(a, b) = gcd(b, a mod b)");
  gcd_skill.validation_rules.push_back("Inputs must be integers");
  catalog.add(gcd_skill);

  math_skill fraction_skill = makeSkill(
      "number_theory.reduce_fraction",
      "Reduce a fraction",
      "number_theory",
      "Converts a fraction to lowest terms and normalizes the denominator sign.",
      skill_status::implemented);
  fraction_skill.required_inputs.push_back("numerator");
  fraction_skill.required_inputs.push_back("denominator");
  fraction_skill.outputs.push_back("reduced_numerator");
  fraction_skill.outputs.push_back("reduced_denominator");
  fraction_skill.validation_rules.push_back("Denominator must be non-zero");
  catalog.add(fraction_skill);

  math_skill prime_skill = makeSkill(
      "number_theory.is_prime",
      "Prime check",
      "number_theory",
      "Determines whether an integer is prime.",
      skill_status::implemented);
  prime_skill.required_inputs.push_back("n");
  prime_skill.outputs.push_back("is_prime");
  prime_skill.validation_rules.push_back("Input must be an integer");
  catalog.add(prime_skill);

  math_skill fibonacci_skill = makeSkill(
      "sequences.fibonacci.term",
      "Fibonacci term",
      "sequences",
      "Computes the n-th term of the Fibonacci sequence using 1-based positions.",
      skill_status::implemented);
  fibonacci_skill.required_inputs.push_back("n");
  fibonacci_skill.outputs.push_back("term");
  fibonacci_skill.validation_rules.push_back("n should be positive for the school sequence");
  catalog.add(fibonacci_skill);

  math_skill pa_term_skill = makeSkill(
      "sequences.pa.nth_term",
      "Arithmetic progression nth term",
      "sequences",
      "Computes the n-th term of an arithmetic progression.",
      skill_status::implemented);
  pa_term_skill.required_inputs.push_back("A1");
  pa_term_skill.required_inputs.push_back("n");
  pa_term_skill.required_inputs.push_back("r");
  pa_term_skill.outputs.push_back("An");
  pa_term_skill.formulas.push_back("An = A1 + (n - 1)r");
  pa_term_skill.validation_rules.push_back("n must be at least 1");
  catalog.add(pa_term_skill);

  math_skill pa_sum_skill = makeSkill(
      "sequences.pa.sum",
      "Arithmetic progression sum",
      "sequences",
      "Computes the sum of the first n terms of an arithmetic progression.",
      skill_status::implemented);
  pa_sum_skill.required_inputs.push_back("A1");
  pa_sum_skill.required_inputs.push_back("n");
  pa_sum_skill.required_inputs.push_back("r");
  pa_sum_skill.outputs.push_back("Sn");
  pa_sum_skill.formulas.push_back("Sn = (A1 + An)n / 2");
  pa_sum_skill.validation_rules.push_back("n should be positive in school exercises");
  catalog.add(pa_sum_skill);

  math_skill pg_term_skill = makeSkill(
      "sequences.pg.nth_term",
      "Geometric progression nth term",
      "sequences",
      "Computes the n-th term of a geometric progression.",
      skill_status::implemented);
  pg_term_skill.required_inputs.push_back("A1");
  pg_term_skill.required_inputs.push_back("n");
  pg_term_skill.required_inputs.push_back("q");
  pg_term_skill.outputs.push_back("An");
  pg_term_skill.formulas.push_back("An = A1 * q^(n - 1)");
  pg_term_skill.validation_rules.push_back("n must be at least 1");
  catalog.add(pg_term_skill);

  math_skill pg_sum_skill = makeSkill(
      "sequences.pg.sum",
      "Geometric progression sum",
      "sequences",
      "Computes the sum of the first n terms of a geometric progression.",
      skill_status::implemented);
  pg_sum_skill.required_inputs.push_back("A1");
  pg_sum_skill.required_inputs.push_back("n");
  pg_sum_skill.required_inputs.push_back("q");
  pg_sum_skill.outputs.push_back("Sn");
  pg_sum_skill.formulas.push_back("Sn = A1 * (q^n - 1) / (q - 1) when q != 1");
  catalog.add(pg_sum_skill);

  math_skill pg_product_skill = makeSkill(
      "sequences.pg.product",
      "Geometric progression product",
      "sequences",
      "Computes the product of the first n terms of a geometric progression.",
      skill_status::implemented);
  pg_product_skill.required_inputs.push_back("A1");
  pg_product_skill.required_inputs.push_back("n");
  pg_product_skill.required_inputs.push_back("q");
  pg_product_skill.outputs.push_back("Pn");
  catalog.add(pg_product_skill);

  catalog.add(linearEquationSkill());
  catalog.add(quadraticRootsSkill());
  catalog.add(linearSystem2x2Skill());
  catalog.add(quadraticVertexSkill());
  catalog.add(distanceBetweenPointsSkill());
  catalog.add(midpointBetweenPointsSkill());
  catalog.add(centralTendencySkill());

  return catalog;
}

inline const skill_catalog& highSchoolCatalog() {
  static const skill_catalog catalog = buildHighSchoolCatalog();
  return catalog;
}

}  // namespace wrs

#endif  // WEXACTS_EDUCATION_HIGH_SCHOOL_CATALOG_H

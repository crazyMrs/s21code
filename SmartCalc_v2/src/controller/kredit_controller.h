#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_KREDIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_KREDIT_CONTROLLER_H_

#include <string>

#include "../model/kredit_model.h"

namespace s21 {
class KreditController {
 public:
  KreditController() = default;
  ~KreditController() = default;

  inline void SetInputData(CreditInput &data) noexcept {
    value_.SetInputData(data);
  }

  inline CreditOutput GetOutputData() noexcept {
    return value_.GetOutputData();
  }

  inline void KreditCalculate() { value_.KreditCalculate(); }

 private:
  KreditCalc value_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_KREDIT_CONTROLLER_H_
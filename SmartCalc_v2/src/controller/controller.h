#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class CalcController {
 public:
  explicit CalcController(ModelCalculator *model) : value_(model) {}
  ~CalcController() = default;

  double Calculate(std::string &str) { return value_->InputStr(str); }

  inline enum Status GetStatus() const noexcept { return value_->GetStatus(); }
  Status ResetStatus() { return value_->ResetStatus(); }

 private:
  ModelCalculator *value_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CONTROLLER_H_
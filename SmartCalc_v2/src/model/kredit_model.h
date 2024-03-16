#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_KREDIT_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_MODEL_KREDIT_MODEL_H_

#include <string>
#include <vector>

namespace s21 {
struct CreditOutput {
  std::vector<double> monthly_payment;  // ежемесячно оплата
  double over_payment;                  // переплата
  double total_payment;                 // всего к оплате
};

struct CreditInput {
  double credit_amount;
  double credit_term;
  int credit_term_type;
  double credit_rate;
  std::string credit_payment_type;
};

class KreditCalc {
 public:
  KreditCalc() = default;
  ~KreditCalc() = default;

  void SetInputData(CreditInput &data) noexcept;
  CreditOutput GetOutputData() noexcept;
  void KreditCalculate();

 private:
  CreditOutput output_data_;
  CreditInput input_data_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_KREDIT_MODEL_H_
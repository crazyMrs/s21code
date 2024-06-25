#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_
#define CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_

#include <stack>
#include <string>
#include <vector>
#include <stdexcept>

namespace s21 {
enum Status { fOk, fError };
class ModelCalculator {
 public:
  ModelCalculator() = default;
  explicit ModelCalculator(const std::string &other_string);
  explicit ModelCalculator(const char &other_string);
  ModelCalculator(const ModelCalculator &other) = default;
  ModelCalculator(ModelCalculator &&other) = default;
  ~ModelCalculator() = default;

  long double SimpleCalculate(double val1, double val2, char oper);
  long double TrigonomCalculate(double val, char oper);
  long double InputStr(std::string &str);
  enum Status ReadOperand(std::string &str, char *oper);
  void FindOperand(std::string::const_iterator &str);
  void calculation();
  long double finish(std::string &str);
  int PriorityFunc(char oper);

  void ClearStacks();
  void ProcessExpression(const std::string &str);
  void ProcessNumber(std::string::const_iterator &it, const std::string &str);
  void ProcessNegativeNumber(std::string::const_iterator &it);
  void ProcessOperator(std::string::const_iterator &it, const std::string &str);
  void ProcessClosingParenthesis(const std::string &str);

  std::string FindOperation(std::string::const_iterator &it,
                            const std::vector<std::string> &operations);

  enum Status GetStatus() const { return status_; }
  Status ResetStatus() { return status_ = fOk; }

  bool is_digit(char c) noexcept;
  bool CheckStr(const std::string &str) noexcept;
  bool CheckValidCharacter(char ch) noexcept;
  bool CheckBracket(int &bracket, char ch) noexcept;
  bool CheckConsecutiveOperators(char prev, char ch) noexcept;
  bool CheckLastCharacter(char prev) noexcept;
  bool CheckBracketBalance(int bracket) noexcept;

 private:
  enum Status status_ = fOk;
  std::stack<char> stack_operand_;
  std::stack<long double> stack_number_;
  long double result_ = 0;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_MODEL_H_

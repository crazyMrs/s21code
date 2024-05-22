#ifndef S21_VIEWER_V20_INTERFACES_STRATEGY_STRATEGY_H_
#define S21_VIEWER_V20_INTERFACES_STRATEGY_STRATEGY_H_
#include <math.h>

#include <vector>
namespace s21 {

class Strategy {
 public:
  virtual ~Strategy() {}
  virtual void UseStrategy(std::vector<float>& v, const int& value) = 0;
  void UpdateLast(const int& value) noexcept;
  int GetLast() const noexcept;
  void ImplementationGeneral(std::vector<float>& v, const int& value,
                             const int& axis);

 protected:
  int last_value_ = 0;
  const float pi_ = 3.141592653589793;
};

class RotateX : public Strategy {
 public:
  void UseStrategy(std::vector<float>& v, const int& value) override;
};

class RotateY : public Strategy {
 public:
  void UseStrategy(std::vector<float>& v, const int& value) override;
};

class RotateZ : public Strategy {
 public:
  void UseStrategy(std::vector<float>& v, const int& value) override;
};

class Context {
 protected:
  Strategy* operation_;

 public:
  virtual ~Context() {}
  virtual void UseStrategy(std::vector<float>& v, const int& value) = 0;
  virtual void SetStrategy(Strategy* v) = 0;
};

}  // namespace s21

#endif  // S21_VIEWER_V20_INTERFACES_STRATEGY_STRATEGY_H_
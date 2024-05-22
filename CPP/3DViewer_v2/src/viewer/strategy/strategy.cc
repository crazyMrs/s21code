#include "strategy.h"
namespace s21 {
void Strategy::UpdateLast(const int& value) noexcept { last_value_ = value; }

int Strategy::GetLast() const noexcept { return last_value_; }

void Strategy::ImplementationGeneral(std::vector<float>& v, const int& value,
                                     const int& axis) {
  float sigma_ = pi_ * (value - last_value_) / 180.f;
  size_t v_size = v.size() / 3;
  float sin_function = sin(sigma_);
  float cos_function = cos(sigma_);

  int real_axis[2];
  for (int i{}, j{}; i != 3; ++i) {
    if (axis != i) {
      real_axis[j] = i;
      ++j;
    }
  }

  for (size_t i{}; i != v_size; ++i) {
    float& number1 = v[i * 3 + real_axis[0]];
    float& number2 = v[i * 3 + real_axis[1]];
    float value1 = number1 * cos_function + number2 * sin_function;
    float value2 = -number1 * sin_function + number2 * cos_function;
    number1 = value1;
    number2 = value2;
  }
  last_value_ = value;
}

void RotateX::UseStrategy(std::vector<float>& v, const int& value) {
  ImplementationGeneral(v, value, 0);
}

void RotateY::UseStrategy(std::vector<float>& v, const int& value) {
  ImplementationGeneral(v, value, 1);
}

void RotateZ::UseStrategy(std::vector<float>& v, const int& value) {
  ImplementationGeneral(v, value, 2);
}

}  // namespace s21

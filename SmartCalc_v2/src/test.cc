#include <gtest/gtest.h>

#include <cmath>

#include "./controller/kredit_controller.h"
#include "./model/kredit_model.cc"
#include "./model/kredit_model.h"
#include "./model/model.cc"
#include "./model/model.h"

class MyTests : public ::testing::Test {
 protected:
  s21::ModelCalculator calculator;
  s21::CreditInput input;
  s21::KreditController controller;
};

TEST_F(MyTests, Test0) {
  std::string expression = "5+-1)";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), s21::fError);
}

TEST_F(MyTests, Test1) {
  std::string expression = "sqrt(16)+sin(1)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 4.84147, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test2) {
  std::string expression = "2^(2^(2^2))";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 65536);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test3) {
  std::string expression = "log(25)-acos(0.45)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 0.293909, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test4) {
  std::string expression = "(4*sin(2.9)+3*cos(0.47))/4";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 0.907926, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test5) {
  std::string expression = "log(50)/acos(0.35)*atan(1.1)*sqrt(64)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 9.3318876, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test6) {
  std::string expression =
      "(sin(1.4)*cos(0.85)/tan(0.68))/(asin(0.38)/"
      "2*acos(0.45)^3-atan(0.54)*sqrt(49))+ln(5)*log(100)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 2.967829, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test7) {
  std::string expression =
      "acos(0.25)^ln(2)-atan(1.5)*sqrt(16)*log(10)*sin(2.5)/(cos(1.1))";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, -3.97576591, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test8) {
  std::string expression =
      "((sin(1.7)*acos(0.3)-atan(0.35)*tan(1.5))^2)/sqrt(9)*(ln(7)+log(1000)/"
      "acos(0.6))";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 21.0601731, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test10) {
  std::string expression =
      "(cos(2.1)^2*sin(1.2)*atan(0.85)+acos(0.4))/"
      "log(250)*sqrt(169)+ln(5)*asin(0.55)*tan(0.5)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 7.70412863, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test11) {
  std::string expression =
      "(sin(0.93)+acos(0.71)/atan(1.37)*tan(1.8))/"
      "(sqrt(25)*ln(10)*acos(0.3)-asin(0.6)*cos(1.1))";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, -0.193212471, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test12) {
  std::string expression = "sin(cos(tan(ln(log(1234)+1)*2)/3)-4)";
  long double result = calculator.InputStr(expression);
  double original_result = sin(cos(tan(logl(log10l(1234) + 1) * 2) / 3) - 4);
  EXPECT_DOUBLE_EQ(result, original_result);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test13) {
  std::string expression = "atan(acos(0.1*0.5))";
  long double result = calculator.InputStr(expression);
  double original_result = atan(acos(0.1 * 0.5));
  EXPECT_DOUBLE_EQ(result, original_result);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test14) {
  std::string expression = "1/0";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), 1);
}

TEST_F(MyTests, Test15) {
  std::string expression = "sqrt(-16)";
  long double result = calculator.InputStr(expression);
  EXPECT_TRUE(std::isnan(result));
}

TEST_F(MyTests, Test16) {
  std::string expression = "654+";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), s21::fOk);
}

TEST_F(MyTests, Test17) {
  std::string expression = "(5+";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), 1);
}

TEST_F(MyTests, Test19) {
  std::string expression = "=1e+06";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), s21::fError);
}

TEST_F(MyTests, Test20) {
  std::string expression = "-3+1e+06";
  long double result = calculator.InputStr(expression);
  double original_result = -3 + 1e+06;
  EXPECT_DOUBLE_EQ(result, original_result);
  // EXPECT_EQ(result, 1e+06 - 3);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test21) {
  std::string expression = "INCORRECT";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), 1);
}

TEST_F(MyTests, Test22) {
  std::string expression = "1e+999";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), 1);
}

TEST_F(MyTests, Test23) {
  std::string expression = "1e-900";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), 1);
}

TEST_F(MyTests, Test24) {
  std::string expression = "-1-(-1-(-1-(-2-1)))";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 2);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test25) {
  std::string expression = "1-(-1)";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 2);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test26) {
  std::string expression = "1-sin(1)";
  long double result = calculator.InputStr(expression);
  EXPECT_NEAR(result, 0.158529, 1e-6);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test27) {
  std::string expression = "+5+5";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 10);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test28) {
  std::string expression = "+5*(-5)";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, -25);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test29) {
  std::string expression = "";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), s21::fError);
}

TEST_F(MyTests, Test30) {
  std::string expression = "log(-1)*ln(-2)";
  long double result = calculator.InputStr(expression);
  EXPECT_TRUE(std::isnan(result));
}

TEST_F(MyTests, Test31) {
  std::string expression = "+";
  calculator.InputStr(expression);
  EXPECT_EQ(calculator.GetStatus(), s21::fError);
}

TEST_F(MyTests, Test32) {
  std::string expression = "20%5";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test33) {
  std::string expression = "1 + 3";
  long double result = calculator.InputStr(expression);
  EXPECT_EQ(result, 4);
  EXPECT_EQ(calculator.GetStatus(), 0);
}

TEST_F(MyTests, Test111) {
  input.credit_amount = 1000000;
  input.credit_term = 13;
  input.credit_term_type = 1;
  input.credit_rate = 23.13;
  input.credit_payment_type = "Аннуитетные";

  controller.SetInputData(input);
  controller.KreditCalculate();

  EXPECT_NEAR(controller.GetOutputData().monthly_payment[0], 87697.81, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().over_payment, 140071.55, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_payment, 1140071.55, 1e-2);
}

TEST_F(MyTests, Test222) {
  input.credit_amount = 123456;
  input.credit_term = 6;
  input.credit_term_type = 1;
  input.credit_rate = 14.32;
  input.credit_payment_type = "Дифференцированные";

  controller.SetInputData(input);
  controller.KreditCalculate();

  EXPECT_NEAR(controller.GetOutputData().monthly_payment[0], 22049.24, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().monthly_payment[1], 21803.70, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().monthly_payment[2], 21558.16, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().monthly_payment[3], 21312.62, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().monthly_payment[4], 21067.08, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().monthly_payment[5], 20821.54, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().over_payment, 5156.35, 1e-2);
  EXPECT_NEAR(controller.GetOutputData().total_payment, 128612.35, 1e-2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
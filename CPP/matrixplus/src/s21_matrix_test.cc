#include <gtest/gtest.h>

#include "s21_matrix_oop.h"
TEST(Create, False) {
  ASSERT_THROW(S21Matrix matrix_b(0, -2), std::out_of_range);
}

TEST(SetValue, False) {
  S21Matrix matrix_b(8, 8);
  ASSERT_THROW(matrix_b(9, 9) = 1, std::out_of_range);
}

TEST(Constructors, TwoArgs) {
  S21Matrix matrix_a(4, 5);
  EXPECT_EQ(matrix_a.GetCols(), 5);
  EXPECT_EQ(matrix_a.GetRows(), 4);
}

TEST(Constructors, CopyConstructor) {
  S21Matrix origin(4, 5);
  origin(1, 1) = 5.0;

  S21Matrix copy(origin);

  EXPECT_EQ(copy.GetRows(), 4);
  EXPECT_EQ(copy.GetCols(), 5);
  EXPECT_EQ(copy(1, 1), 5.0);
}

TEST(Constructors, MoveConstructor) {
  S21Matrix origin(4, 3);
  origin(1, 1) = 5.0;
  S21Matrix moved(std::move(origin));
  EXPECT_EQ(moved.GetRows(), 4);
  EXPECT_EQ(moved.GetCols(), 3);
  EXPECT_EQ(moved(1, 1), 5.0);
  EXPECT_EQ(origin.GetRows(), 0);
  EXPECT_EQ(origin.GetCols(), 0);
}

TEST(EqMatrix, True) {
  S21Matrix matrix_a(5, 5);
  S21Matrix matrix_b(5, 5);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  matrix_b(0, 0) = 1.0;
  matrix_b(0, 1) = 2.0;
  matrix_b(1, 0) = 3.0;
  matrix_b(1, 1) = 4.0;
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(EqMatrix, False) {
  S21Matrix matrix_a(5, 5);
  S21Matrix matrix_b(2, 2);
  ASSERT_FALSE(matrix_a == matrix_b);
}

TEST(SumMatrix, Basic) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  S21Matrix matrix_b(2, 2);
  matrix_b(0, 0) = 5.0;
  matrix_b(0, 1) = 6.0;
  matrix_b(1, 0) = 7.0;
  matrix_b(1, 1) = 8.0;

  matrix_a.SumMatrix(matrix_b);

  EXPECT_EQ(matrix_a(0, 0), 6.0);
  EXPECT_EQ(matrix_a(0, 1), 8.0);
  EXPECT_EQ(matrix_a(1, 0), 10.0);
  EXPECT_EQ(matrix_a(1, 1), 12.0);
}

TEST(SumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;
  matrix_a.SumMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(SumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SumMatrix(matrix_b), std::out_of_range);
}

TEST(SubMatrix, Basic) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  S21Matrix matrix_b(2, 2);
  matrix_b(0, 0) = 5.0;
  matrix_b(0, 1) = 6.0;
  matrix_b(1, 0) = 7.0;
  matrix_b(1, 1) = 8.0;

  matrix_a.SubMatrix(matrix_b);

  EXPECT_EQ(matrix_a(0, 0), -4.0);
  EXPECT_EQ(matrix_a(0, 1), -4.0);
  EXPECT_EQ(matrix_a(1, 0), -4.0);
  EXPECT_EQ(matrix_a(1, 1), -4.0);
}

TEST(SubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  matrix_a.SubMatrix(matrix_b);

  ASSERT_TRUE(matrix_a == result);
}

TEST(SubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::out_of_range);
}

TEST(MulNumber, Basic) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  double num = 2.0;
  matrix_a.MulNumber(num);

  EXPECT_EQ(matrix_a(0, 0), 2.0);
  EXPECT_EQ(matrix_a(0, 1), 4.0);
  EXPECT_EQ(matrix_a(1, 0), 6.0);
  EXPECT_EQ(matrix_a(1, 1), 8.0);
}

TEST(MulNumber, MultiplyByZero) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = 0;
  result(0, 1) = 0;
  result(1, 0) = 0;
  result(1, 1) = 0;

  matrix_a.MulNumber(0);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, MultiplyByNegativeNumber) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = 781.4;
  result(0, 1) = 0;
  result(1, 0) = 3;
  result(1, 1) = -20;

  matrix_a.MulNumber(-10);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulNumber, MultiplyByFractionalNumber) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 1.5;
  matrix_a(0, 1) = 2.5;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  result(0, 0) = 4.5;
  result(0, 1) = 7.5;
  result(1, 0) = 9.0;
  result(1, 1) = 12.0;

  matrix_a.MulNumber(3);

  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, Basic) {
  S21Matrix matrix_a(2, 3);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(0, 2) = 3.0;
  matrix_a(1, 0) = 4.0;
  matrix_a(1, 1) = 5.0;
  matrix_a(1, 2) = 6.0;

  S21Matrix matrix_b(3, 2);
  matrix_b(0, 0) = 7.0;
  matrix_b(0, 1) = 8.0;
  matrix_b(1, 0) = 9.0;
  matrix_b(1, 1) = 10.0;
  matrix_b(2, 0) = 11.0;
  matrix_b(2, 1) = 12.0;

  matrix_a.MulMatrix(matrix_b);

  EXPECT_EQ(matrix_a(0, 0), 58.0);
  EXPECT_EQ(matrix_a(0, 1), 64.0);
  EXPECT_EQ(matrix_a(1, 0), 139.0);
  EXPECT_EQ(matrix_a(1, 1), 154.0);
}

TEST(MulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  matrix_a.MulMatrix(matrix_b);
  ASSERT_TRUE(matrix_a == result);
}

TEST(MulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a.MulMatrix(matrix_b), std::out_of_range);
}
TEST(OperatorParentheses, True) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_EQ(matrix_a(0, 1), 2);
}
TEST(OperatorParentheses, False) {
  S21Matrix matrix_a(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;
  ASSERT_NE(matrix_a(0, 1), 10);
}
TEST(OperatorPlus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}
TEST(OperatorMinus, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a - matrix_b) == result);
}
TEST(OperatorMultiplyMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a * matrix_b) == result);
}
TEST(OperatorMultiplyNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}

TEST(OperatorEqMatrix, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(1, 3);
  matrix_a = matrix_b;
  ASSERT_TRUE(matrix_a == matrix_b);
}

TEST(OperatorSumMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a += matrix_b) == result);
}
TEST(OperatorSumMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW((matrix_a += matrix_b), std::out_of_range);
}

TEST(OperatorSubMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

  ASSERT_TRUE((matrix_a -= matrix_b) == result);
}
TEST(OperatorSubMatrix, False) {
  S21Matrix matrix_a(1, 2);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a -= matrix_b, std::out_of_range);
}
TEST(OperatorMulNumber, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a *= 10) == result);
}
TEST(OperatorMulMatrix, True) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6.6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  result(0, 0) = -28;
  result(0, 1) = 4;
  result(1, 0) = 46.2;
  result(1, 1) = 0;

  ASSERT_TRUE((matrix_a *= matrix_b) == result);
}
TEST(OperatorMulMatrix, False) {
  S21Matrix matrix_a(2, 1);
  S21Matrix matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(1, 0) = -6.6;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3.5;
  matrix_b(1, 1) = 2;

  EXPECT_THROW(matrix_a *= matrix_b, std::out_of_range);
}

TEST(Transpose, Basic) {
  S21Matrix matrix_a(2, 3);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(0, 2) = 3.0;
  matrix_a(1, 0) = 4.0;
  matrix_a(1, 1) = 5.0;
  matrix_a(1, 2) = 6.0;

  S21Matrix result = matrix_a.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

TEST(Transpose, True) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  result(0, 0) = 7;
  result(0, 1) = 0;
  result(0, 2) = 3.12;
  result(0, 3) = -78;
  result(1, 0) = -98;
  result(1, 1) = 5.4;
  result(1, 2) = 2323;
  result(1, 3) = 476.4;
  result(2, 0) = 0.5;
  result(2, 1) = 32;
  result(2, 2) = 23;
  result(2, 3) = 21;
  S21Matrix res = matrix_a.Transpose();
  ASSERT_TRUE(res == result);
}

TEST(Determinant, Basic_2_2) {
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix2.Determinant(), -2.0);
}

TEST(Determinant, Determinant1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 2;
  EXPECT_TRUE(matrix.Determinant() == 2);
}

TEST(Determinant, Determinant2x2) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 2;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 3;

  EXPECT_TRUE(matrix.Determinant() == 2);
}

TEST(Determinant, Determinant3x3) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 2;
  matrix(0, 2) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 3;
  matrix(1, 2) = 1;
  matrix(2, 0) = 3;
  matrix(2, 1) = 2;
  matrix(2, 2) = 5;

  EXPECT_NEAR(matrix.Determinant(), 2, std::numeric_limits<double>::epsilon());
}

TEST(Determinant, NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::out_of_range);
}

TEST(CalcComplements, Basic) {
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(0, 2) = 3.0;
  matrix_a(1, 0) = 4.0;
  matrix_a(1, 1) = 5.0;
  matrix_a(1, 2) = 6.0;
  matrix_a(2, 0) = 7.0;
  matrix_a(2, 1) = 8.0;
  matrix_a(2, 2) = 9.0;

  S21Matrix result = matrix_a.CalcComplements();

  EXPECT_EQ(result(0, 0), -3.0);
  EXPECT_EQ(result(0, 1), 6.0);
  EXPECT_EQ(result(0, 2), -3.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), -12.0);
  EXPECT_EQ(result(1, 2), 6.0);
  EXPECT_EQ(result(2, 0), -3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), -3.0);
}

TEST(CalcComplements, SquareMatrix1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  EXPECT_THROW(matrix.CalcComplements()(0, 0), std::out_of_range);
}

TEST(CalcComplements, SquareMatrix2x2) {
  S21Matrix matrix_a(2, 2), matrix_b(2, 2);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 5;
  matrix_a(1, 1) = 4;

  matrix_b(0, 0) = 4;
  matrix_b(0, 1) = -5;
  matrix_b(1, 0) = -2;
  matrix_b(1, 1) = 1;

  EXPECT_TRUE(matrix_b == matrix_a.CalcComplements());
}

TEST(CalcComplements, SquareMatrix3x3) {
  S21Matrix matrix_a(3, 3), matrix_b(3, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;

  matrix_b(0, 0) = 0;
  matrix_b(0, 1) = 10;
  matrix_b(0, 2) = -20;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = -14;
  matrix_b(1, 2) = 8;
  matrix_b(2, 0) = -8;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = 4;

  EXPECT_TRUE(matrix_b.EqMatrix(matrix_a.CalcComplements()));
}

TEST(CalcComplements, NonSquareMatrix) {
  S21Matrix matrix(4, 3);

  ASSERT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(Inverse, Basic) {
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.0;
  matrix_a(0, 1) = 2.0;
  matrix_a(1, 0) = 3.0;
  matrix_a(1, 1) = 4.0;

  S21Matrix result = matrix_a.InverseMatrix();

  EXPECT_EQ(result(0, 0), -2);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(1, 0), 1.5);
  EXPECT_EQ(result(1, 1), -0.5);
}

TEST(Inverse, False) {
  S21Matrix matrix_a(4, 3);
  S21Matrix result(3, 4);

  matrix_a(0, 0) = 7;
  matrix_a(0, 1) = -98;
  matrix_a(0, 2) = 0.5;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 5.4;
  matrix_a(1, 2) = 32;
  matrix_a(2, 0) = 3.12;
  matrix_a(2, 1) = 2323;
  matrix_a(2, 2) = 23;
  matrix_a(3, 0) = -78;
  matrix_a(3, 1) = 476.4;
  matrix_a(3, 2) = 21;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::out_of_range);
}
TEST(Inverse, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));

  S21Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  EXPECT_THROW(matrix_b.InverseMatrix(), std::out_of_range);
}
TEST(Get, True) {
  S21Matrix matrix_a(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  ASSERT_EQ(matrix_a.GetRows(), 3);
  ASSERT_EQ(matrix_a.GetCols(), 3);
}
TEST(Set, True) {
  S21Matrix matrix_a(3, 3);
  S21Matrix result(3, 2);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 2;
  result(0, 1) = 5;

  result(1, 0) = 6;
  result(1, 1) = 3;

  result(2, 0) = 5;
  result(2, 1) = -2;
  matrix_a.SetCols(2);

  ASSERT_TRUE(matrix_a == result);

  S21Matrix matrix_b(3, 3);
  S21Matrix result_b(2, 3);

  matrix_b(0, 0) = 2;
  matrix_b(0, 1) = 5;
  matrix_b(0, 2) = 7;
  matrix_b(1, 0) = 6;
  matrix_b(1, 1) = 3;
  matrix_b(1, 2) = 4;
  matrix_b(2, 0) = 5;
  matrix_b(2, 1) = -2;
  matrix_b(2, 2) = -3;

  result_b(0, 0) = 2;
  result_b(0, 1) = 5;
  result_b(0, 2) = 7;
  result_b(1, 0) = 6;
  result_b(1, 1) = 3;
  result_b(1, 2) = 4;

  matrix_b.SetRows(2);
  ASSERT_TRUE(matrix_b == result_b);
}

TEST(InverseMatrix, SquareMatrix1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 2;
  EXPECT_TRUE(matrix.InverseMatrix()(0, 0) == 0.5);
}

TEST(InverseMatrix, SquareMatrix2x2) {
  S21Matrix matrix_a(2, 2), matrix_b(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = 5;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = 0;
  matrix_b(0, 1) = 0.2;
  matrix_b(1, 0) = 0.5;
  matrix_b(1, 1) = -0.3;

  EXPECT_TRUE(matrix_b.EqMatrix(matrix_a.InverseMatrix()));
}

TEST(InverseMatrix, SquareMatrix3x3) {
  S21Matrix matrix_a(3, 3), matrix_b(3, 3);

  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 1;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;

  matrix_b(0, 0) = 0;
  matrix_b(0, 1) = -0.5;
  matrix_b(0, 2) = 1;
  matrix_b(1, 0) = -0.25;
  matrix_b(1, 1) = 0.25;
  matrix_b(1, 2) = 0.25;
  matrix_b(2, 0) = 0.5;
  matrix_b(2, 1) = 0;
  matrix_b(2, 2) = -0.5;

  EXPECT_TRUE(matrix_b.EqMatrix(matrix_a.InverseMatrix()));
}

TEST(InverseMatrix, ZeroMatrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 3;
  matrix(0, 1) = 3;
  matrix(1, 0) = 3;
  matrix(1, 1) = 3;

  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, NonSquareMatrix) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = 6;
  EXPECT_THROW(matrix.InverseMatrix(), std::logic_error);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
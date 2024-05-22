#include "s21_matrix_oop.h"

#include <cmath>
#include <cstring>
#include <iostream>

void S21Matrix::CreateMatrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;

  matrix_ = new double*[rows_]();

  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range(
        "Неправильный ввод, матрицы должны иметь столбцы и строки.");
  }
  CreateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix(rows_, cols_);
  CopyVal(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

void S21Matrix::CopyVal(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (IsCondition(other)) {
    return false;
  } else {
    for (int i = 0; i < rows_ && res != false; ++i) {
      for (int j = 0; j < cols_ && res != false; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= kEps) {
          res = false;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (IsCheckMatrix(other) == true) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (IsCheckMatrix(other) == true) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr) {
    throw std::out_of_range("Неправильный ввод, матриц нет");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (IsCheckMul(other)) {
    throw std::out_of_range("Неправильный ввод, не совпадают размеры");
  } else {
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        result.matrix_[i][j] = 0.0;
        for (int k = 0; k < cols_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = result;
  }
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (rows_ != cols_) {
    throw std::out_of_range("Не квадратная матрица");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix res_minor = CalculateMinor(i, j);
      result.matrix_[i][j] = pow((-1), i + j) * res_minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::CalculateMinor(int row, int col) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, mi = 0; mi < result.rows_; ++mi) {
    if (row == i) ++i;
    for (int j = 0, mj = 0; mj < result.cols_; ++mj) {
      if (col == j) ++j;
      result.matrix_[mi][mj] = matrix_[i][j];
      j++;
    }
    i++;
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range(
        "Неправильный ввод, несоответствии числа строк и столбцов");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  } else if (rows_ > 2) {
    for (int i = 0; i < rows_; ++i) {
      S21Matrix res_minor = CalculateMinor(i, 0);
      int sign = (i % 2 == 0) ? 1 : -1;
      result += sign * matrix_[i][0] * res_minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (matrix_ == nullptr || rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Неправильный ввод, матриц нет");
  } else if (rows_ != cols_) {
    throw std::out_of_range(
        "Неправильный ввод, несоответствии числа строк и столбцов");
  } else {
    double deter = Determinant();
    if (fabs(deter) < kEps) {
      throw std::out_of_range("Детерминант = 0");
    }
    S21Matrix result(rows_, cols_);
    if (rows_ == 1) {
      result.matrix_[0][0] = 1 / matrix_[0][0];
    } else {
      S21Matrix temp = CalcComplements();
      result = temp.Transpose();
      result.MulNumber(1 / deter);
    }
    return result;
  }
}

double& S21Matrix::operator()(int row, int col) {
  if (IsOperator(row, col)) {
    throw std::out_of_range("Segmentation fault");
  }
  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
  if (IsOperator(row, col)) {
    throw std::out_of_range("Segmentation fault");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix(rows_, cols_);
    CopyVal(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix operator*(const double number, const S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::out_of_range(
        "Неправильный ввод, матрицы должны иметь строки и стобцы");
  }
  S21Matrix result(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < rows_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetCols(const int cols) {
  if (cols <= 0) {
    throw std::out_of_range(
        "Неправильный ввод, матрицы должны иметь строки и стобцы");
  }
  S21Matrix result(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j < cols_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

bool S21Matrix::IsCondition(const S21Matrix& other) {
  return (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0 ||
          matrix_ == nullptr || other.matrix_ == nullptr ||
          rows_ != other.rows_ || cols_ != other.cols_);
}

bool S21Matrix::IsOperator(int row, int col) const {
  return (row >= rows_ || col >= cols_ || row < 0 || col < 0);
}

bool S21Matrix::IsCheckMul(const S21Matrix& other) {
  return (cols_ != other.rows_ || rows_ != other.cols_);
}

bool S21Matrix::IsCheckMatrix(const S21Matrix& other) {
  if (IsCondition(other)) {
    throw std::out_of_range("Неправильный ввод");
    return false;
  } else {
    return true;
  }
}
void S21Matrix::print_matrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}


// int main(){
//   S21Matrix matrix_a(3, 3);

//   matrix_a(0, 0) = 2;
//   matrix_a(0, 1) = 5;
//   matrix_a(0, 2) = 7;
//   matrix_a(1, 0) = 6;
//   matrix_a(1, 1) = 3;
//   matrix_a(1, 2) = 4;
//   matrix_a(2, 0) = 5;
//   matrix_a(2, 1) = -2;
//   matrix_a(2, 2) = -3;

//   matrix_a.SetCols(5);
//   matrix_a.print_matrix();
// }
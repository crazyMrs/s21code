#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

const double kEps = 1e-7;

class S21Matrix {
 public:
  S21Matrix() : rows_(0), cols_(0), matrix_(nullptr){};
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }

  void SetRows(const int rows);
  void SetCols(const int cols);

  double& operator()(int row, int col);
  double operator()(int row, int col) const;

  S21Matrix operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);

  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);

  friend S21Matrix operator*(double, S21Matrix&);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);

  S21Matrix operator*(const double num);
  S21Matrix& operator*=(const double num);

  bool operator==(const S21Matrix& other);

  bool IsCheckMatrix(const S21Matrix& other);
  bool IsCondition(const S21Matrix& other);
  bool IsOperator(int row, int col) const;
  bool IsCheckMul(const S21Matrix& other);
  void print_matrix();

 private:
  void CreateMatrix(int rows, int cols);
  S21Matrix CalculateMinor(int row, int col);
  void CopyVal(const S21Matrix& other);
  void RemoveMatrix();
  int rows_, cols_;
  double** matrix_;
};

#endif  //  CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H_

#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_

// /// @brief
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  //    Mutators
  void SetRows(int rows);
  void SetCols(int cols);
  void SetMatrix(double value, int i, int j);
  int GetRows() const;
  int GetCols() const;
  double GetMatrix(int i, int j);

  //    Operators
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  double& operator()(int i, int j);
  double& operator()(int i, int j) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

 private:
  int rows_, cols_;
  double** matrix_;

  //    Helpers:
  void AllocMatrix();
  void DeleteMatrix();
  void CopyMatrix(const S21Matrix& other);
  void CopyValueMatrix(const S21Matrix& other);
  S21Matrix MatrixMinusOne(int i, int j);
};

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H_
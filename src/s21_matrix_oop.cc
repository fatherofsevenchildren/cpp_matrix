#include "s21_matrix_oop.h"

#include <cmath>
#include <iostream>

void S21Matrix::AllocMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix() {
  rows_ = 2;
  cols_ = 2;
  AllocMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("inncorect matrix");
  }
  AllocMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) : S21Matrix(other) {
  other.DeleteMatrix();
}

void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  cols_ = 0;
  rows_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    DeleteMatrix();
  }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    DeleteMatrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    AllocMatrix();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::CopyValueMatrix(const S21Matrix& other) {
  for (int i = 0; i < other.rows_ && i < rows_; i++) {
    for (int j = 0; j < other.cols_ && j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

double S21Matrix::GetMatrix(int i, int j) { return matrix_[i][j]; }

// В СЕТТЕРАХ НУЖНО ДОБАВИТЬ ПЕРЕСОБИРАНИЕ МАТРИЦЫ С НОВЫМИ ДАННЫМИ

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("inncorect matrix");
  }
  if (rows != rows_) {
    S21Matrix res(rows, cols_);
    res.CopyValueMatrix(*this);
    DeleteMatrix();
    *this = res;
  }
  return;
}

void S21Matrix::SetMatrix(double value, int i, int j) {
  matrix_[i - 1][j - 1] = value;
  return;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("inncorect matrix");
  }
  if (cols != cols_) {
    S21Matrix res(rows_, cols);
    res.CopyValueMatrix(*this);
    DeleteMatrix();
    *this = res;
  }
  return;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (cols_ != other.cols_ || rows_ != other.rows_)
    res = false;
  else {
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_ && res; j++)
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) res = false;
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("cols non eq rows, bro((");
  }
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      for (int k = 0; k != other.cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) res.matrix_[j][i] = matrix_[i][j];
  }
  return res;
}

S21Matrix S21Matrix::MatrixMinusOne(int i, int j) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int a = 0; a < result.rows_; a++) {
    int skip_a = 0;
    if (a >= i) skip_a++;
    for (int b = 0; b < result.cols_; b++) {
      int skip_b = 0;
      if (b >= j) skip_b++;
      result.matrix_[a][b] = matrix_[a + skip_a][b + skip_b];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("different matrix dimensions");
  }
  double resulte = 0;
  if (cols_ == 1) {
    resulte = matrix_[0][0];
  } else if (cols_ == 2) {
    resulte = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix VarMatrix(rows_ - 1, cols_ - 1);
      VarMatrix = MatrixMinusOne(0, j);
      double var_res = 0;
      var_res = VarMatrix.Determinant();
      resulte += matrix_[0][j] * pow(-1.00, (double)j) * var_res;
    }
  }
  return resulte;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("different matrix dimensions");
  }
  S21Matrix resulte(rows_, cols_);
  if (cols_ == 1) {
    resulte.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix VarMatrix(rows_ - 1, cols_ - 1);
        VarMatrix = MatrixMinusOne(i, j);
        resulte.matrix_[i][j] = VarMatrix.Determinant();
        resulte.matrix_[i][j] *= pow(-1, (i + j));
      }
    }
  }
  return resulte;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (Determinant() == 0) {
    throw std::out_of_range("zero determinant");
  }
  S21Matrix resulte(*this);
  resulte = CalcComplements().Transpose();
  resulte.MulNumber(1 / (fabs(Determinant())));
  return resulte;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  bool res = EqMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  CopyMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    CopyMatrix(other);
    other.DeleteMatrix();
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res += other;
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res *= other;
  ;
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res *= num;
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res -= other;
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || i < 1 || j < 1) {
    throw std::out_of_range("inncorect matrix");
  }
  return matrix_[i - 1][j - 1];
}

double& S21Matrix::operator()(int i, int j) const {
  if (i > rows_ || j > cols_ || i < 1 || j < 1) {
    throw std::out_of_range("inncorect matrix");
  }
  return matrix_[i - 1][j - 1];
}

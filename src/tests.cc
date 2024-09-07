#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Matrix, Constructors) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_EQ(matrix1.GetCols(), matrix2.GetCols());
}

TEST(Matrix, Indexation) {
  S21Matrix matrix1;
  matrix1.SetMatrix(1.0, 1, 1);
  EXPECT_EQ(matrix1(1, 1), 1.0);
}

TEST(Matrix, Indexation_error) {
  S21Matrix matrix1;
  matrix1.SetMatrix(1.0, 1, 1);
  EXPECT_EQ(matrix1(1, 1), 1.0);
}

TEST(Matrix, False) {
  S21Matrix matrix1;
  S21Matrix matrix2(3, 3);
  EXPECT_FALSE(matrix1.GetCols() == matrix2.GetCols());
}

TEST(Matrix, Eq) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(Matrix, Eq2) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1.SetMatrix(2, 1, 1);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), false);
}

TEST(Matrix, Eq_operator) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  EXPECT_EQ(matrix1 == matrix2, true);
}

TEST(Matrix, Eq_operator1) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 3);
  EXPECT_EQ(matrix1 == matrix2, false);
}

TEST(Matrix, Sum) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1.SetMatrix(4, 1, 1);
  matrix2.SetMatrix(1, 1, 1);
  matrix1.SetMatrix(0.004, 1, 2);
  matrix2.SetMatrix(1, 1, 2);
  matrix1.SumMatrix(matrix2);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 1.004);
}

TEST(Matrix, Sum_operator) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1(1, 1) = 4.0;
  matrix2.SetMatrix(1, 1, 1);
  matrix1.SetMatrix(0.004, 1, 2);
  matrix2.SetMatrix(1, 1, 2);
  matrix1 += matrix2;
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 1.004);
}

TEST(Matrix, Sub) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1.SetMatrix(4, 1, 1);
  matrix2.SetMatrix(1, 1, 1);
  matrix1.SetMatrix(0.004, 1, 2);
  matrix2.SetMatrix(1, 1, 2);
  matrix1.SubMatrix(matrix2);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), -0.996);
}

TEST(Matrix, Sub_operator) {
  S21Matrix matrix1;
  S21Matrix matrix2;
  matrix1.SetMatrix(4, 1, 1);
  matrix2.SetMatrix(1, 1, 1);
  matrix1.SetMatrix(0.004, 1, 2);
  matrix2.SetMatrix(1, 1, 2);
  matrix1 -= matrix2;
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 3.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), -0.996);
}

TEST(Matrix, Eq_operator_constr) {
  S21Matrix other(4, 4);
  S21Matrix other1(4, 4);
  other1.SetMatrix(3, 3, 3);
  other = other1;
  EXPECT_DOUBLE_EQ(other(3, 3), 3.0);
}

TEST(Matrix, Eq_operator_constr2) {
  S21Matrix other(4, 4);
  S21Matrix other1(4, 4);
  other1.SetMatrix(3, 3, 3);
  other = other1 = other;
  EXPECT_DOUBLE_EQ(other(3, 3), 0);
}

TEST(Matrix, Eq_operator_move) {
  S21Matrix other1(4, 4);
  other1.SetMatrix(3, 3, 3);
  S21Matrix other(std::move(other1));
  EXPECT_EQ(other1.GetCols(), 0);
  EXPECT_EQ(other1.GetRows(), 0);
}

TEST(Matrix, Eq_operator_constr_move) {
  S21Matrix other1(4, 4);
  S21Matrix other(4, 4);
  other1.SetMatrix(3, 3, 3);
  other = std::move(other1);
  EXPECT_EQ(other1.GetCols(), 0);
  EXPECT_EQ(other1.GetRows(), 0);
}

TEST(Matrix, Sum_operator_singl) {
  S21Matrix other = {4, 4};
  S21Matrix other1 = {4, 4};
  S21Matrix res(4, 4);
  other1.SetMatrix(3, 3, 3);
  other.SetMatrix(3, 3, 3);
  res = other + other1;
  EXPECT_DOUBLE_EQ(res(3, 3), 6.0);
}

TEST(Matrix, Sub_operator_singl) {
  S21Matrix other = {4, 4};
  S21Matrix other1 = {4, 4};
  S21Matrix res(4, 4);
  other1.SetMatrix(2, 3, 3);
  other.SetMatrix(3, 3, 3);
  res = other - other1;
  EXPECT_DOUBLE_EQ(res(3, 3), 1);
}

TEST(Matrix, Mul) {
  S21Matrix other = {4, 4};
  other.SetMatrix(3, 3, 3);
  other.SetMatrix(2, 2, 2);
  other.MulNumber(3);
  EXPECT_DOUBLE_EQ(other(3, 3), 9);
  EXPECT_DOUBLE_EQ(other(2, 2), 6);
}

TEST(Matrix, MulMatrix) {
  S21Matrix matrix(2, 2);
  S21Matrix other = {2, 2};
  other(1, 1) = 3;
  matrix(1, 1) = 5;
  matrix(1, 2) = 5;
  matrix(2, 1) = 5;
  matrix(2, 2) = 5;
  matrix.MulMatrix(other);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 15);
  EXPECT_DOUBLE_EQ(other(2, 2), 0);
}

TEST(Matrix, Mul_operator_eq) {
  S21Matrix other = {4, 4};
  other.SetMatrix(3, 3, 3);
  other.SetMatrix(2, 2, 2);
  other *= 3;
  EXPECT_DOUBLE_EQ(other(3, 3), 9);
  EXPECT_DOUBLE_EQ(other(2, 2), 6);
}

TEST(Matrix, MulMatrix_operator_eq) {
  S21Matrix matrix(2, 2);
  S21Matrix other = {2, 2};
  other(1, 1) = 3;
  matrix(1, 1) = 5;
  matrix(1, 2) = 5;
  matrix(2, 1) = 5;
  matrix(2, 2) = 5;
  matrix *= other;
  EXPECT_DOUBLE_EQ(matrix(1, 1), 15);
  EXPECT_DOUBLE_EQ(other(2, 2), 0);
}

TEST(Matrix, Mul_operator) {
  S21Matrix other = {4, 4};
  S21Matrix res = {4, 4};
  other.SetMatrix(3, 3, 3);
  other.SetMatrix(2, 2, 2);
  res = other * 3;
  EXPECT_DOUBLE_EQ(res(3, 3), 9);
  EXPECT_DOUBLE_EQ(res(2, 2), 6);
}

TEST(Matrix, MulMatrix_operator) {
  S21Matrix matrix(2, 2);
  S21Matrix other = {2, 2};
  S21Matrix res = {2, 2};
  other(1, 1) = 3;
  matrix(1, 1) = 5;
  matrix(1, 2) = 5;
  matrix(2, 1) = 5;
  matrix(2, 2) = 5;
  res = other * matrix;
  EXPECT_DOUBLE_EQ(res(1, 1), 15);
  EXPECT_DOUBLE_EQ(res(2, 2), 0);
}

TEST(Matrix, Mul_operator_wrong) {
  S21Matrix other = {4, 4};
  S21Matrix res = {4, 4};
  other.SetMatrix(3, 3, 3);
  other.SetMatrix(2, 2, 2);
  res = other * 3;
  EXPECT_DOUBLE_EQ(res(3, 3), 9);
  EXPECT_DOUBLE_EQ(res(2, 2), 6);
}

TEST(Matrix, doublee) {
  S21Matrix other = {4, 4};
  other.SetMatrix(3, 3, 3);
  other.SetMatrix(2, 2, 2);
  other *= other;
  EXPECT_DOUBLE_EQ(other(3, 3), 9);
  EXPECT_DOUBLE_EQ(other(2, 2), 4);
}

TEST(Matrix, Transpose) {
  S21Matrix other = {1, 2};
  other(1, 1) = 3;
  other(1, 2) = 1;
  other = other.Transpose();
  EXPECT_DOUBLE_EQ(other(2, 1), 1);
}

TEST(Matrix, Determinant) {
  S21Matrix other = {3, 3};
  other(1, 1) = 5;
  other(1, 3) = 6.52;
  other(2, 1) = 1.25;
  other(3, 2) = 3;
  other(2, 3) = 3;
  other(2, 2) = 5;
  other(3, 3) = 3;
  EXPECT_DOUBLE_EQ(other.Determinant(), 54.45);
}

TEST(Matrix, Invers) {
  S21Matrix other = {3, 3};
  other(1, 1) = 5;
  other(1, 3) = 6.52;
  other(2, 1) = 1.25;
  other(3, 2) = 3;
  other(2, 3) = 3;
  other(2, 2) = 5;
  other(3, 3) = 3;
  other = other.InverseMatrix();
  ASSERT_NEAR(other(3, 3), 0.4591368, 0.0000001);
  ASSERT_NEAR(other(2, 2), 0.2754821, 0.0000001);
  ASSERT_NEAR(other(1, 1), 0.1101928, 0.0000001);
}

TEST(Matrix, complement) {
  S21Matrix other = {3, 3};
  other(1, 1) = 5;
  other(1, 3) = 6.52;
  other(2, 1) = 1.25;
  other(3, 2) = 3;
  other(2, 3) = 3;
  other(2, 2) = 5;
  other(3, 3) = 3;
  other = other.CalcComplements();
  EXPECT_DOUBLE_EQ(other(3, 3), 25);
  EXPECT_DOUBLE_EQ(other(2, 2), 15);
  EXPECT_DOUBLE_EQ(other(1, 1), 6);
}

TEST(Matrix, complement1) {
  S21Matrix other = {1, 1};
  other = other.CalcComplements();
  EXPECT_DOUBLE_EQ(other(1, 1), 0);
}

TEST(Matrix, SetRows) {
  S21Matrix other(1, 1);
  other.SetRows(3);
  other(3, 1) = 3;
  EXPECT_DOUBLE_EQ(other(3, 1), 3);
  EXPECT_EQ(other.GetRows(), 3);
}

TEST(Matrix, SetCols) {
  S21Matrix other(1, 1);
  other.SetCols(3);
  other(1, 3) = 3;
  EXPECT_DOUBLE_EQ(other(1, 3), 3);
  EXPECT_EQ(other.GetCols(), 3);
}

TEST(Matrix, Determinant1x1) {
  S21Matrix const determinant(1, 1);
  // determinant(1,1) = 8;
  EXPECT_DOUBLE_EQ(determinant(1, 1), 0);
}

TEST(Matrix, Const) {
  S21Matrix determinant(1, 1);
  determinant(1, 1) = 8;
  EXPECT_DOUBLE_EQ(determinant.Determinant(), 8);
}

TEST(Matrix, Errors) {
  S21Matrix error;
  S21Matrix const error3;
  S21Matrix error2(5, 6);
  EXPECT_THROW(S21Matrix errors(-123, 0), std::out_of_range);
  EXPECT_THROW(error.SetRows(0), std::out_of_range);
  EXPECT_THROW(error.SetCols(0), std::out_of_range);
  EXPECT_THROW(error.SumMatrix(error2), std::out_of_range);
  EXPECT_THROW(error.SubMatrix(error2), std::out_of_range);
  EXPECT_THROW(error.MulMatrix(error2), std::out_of_range);
  EXPECT_THROW(error2.CalcComplements(), std::out_of_range);
  EXPECT_THROW(error2.Determinant(), std::out_of_range);
  EXPECT_THROW(error.InverseMatrix(), std::out_of_range);
  EXPECT_THROW(error(10, 1), std::out_of_range);
  EXPECT_THROW(error3(10, 1), std::out_of_range);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
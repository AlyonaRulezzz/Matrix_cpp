#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

using namespace std;

TEST(Constructors, Default) {
    S21Matrix m1;
    EXPECT_EQ(3, m1.GetRows());
    EXPECT_EQ(3, m1.GetCols());
}

TEST(Constructors, With_parameters) {
    S21Matrix m1(4, 5);
    EXPECT_EQ(4, m1.GetRows());
    EXPECT_EQ(5, m1.GetCols());
    EXPECT_NO_THROW(S21Matrix m1(4, 5));

    EXPECT_ANY_THROW(S21Matrix m2(0, 8));
    EXPECT_ANY_THROW(S21Matrix(-8, 8));
}

TEST(Constructors, Copy) {
    S21Matrix test1;
    test1.Fill(5);

    S21Matrix m1(test1);
    EXPECT_EQ(test1.GetRows(), m1.GetRows());
    EXPECT_EQ(test1.GetCols(), m1.GetCols());
    for (int i = 0; i < m1.GetRows(); i++) {
        for (int j = 0; j< m1.GetCols(); j++) {
            EXPECT_EQ(test1(i, j), m1(i, j));
        }
    }
}

TEST(Constructors, Move) {
    S21Matrix test1(4, 5);
    test1.Fill(0, 2);
    S21Matrix res1(test1);
    S21Matrix m1(move(test1));
    EXPECT_EQ(m1.GetRows(), res1.GetRows());
    EXPECT_EQ(m1.GetCols(), res1.GetCols());
    EXPECT_EQ(true, m1.EqMatrix(res1));
    EXPECT_EQ(false, m1.EqMatrix(test1));
}

TEST(Constructors, Destructor) {
    S21Matrix m1(4, 5);
    m1.Fill(0, 2);
    m1.~S21Matrix();
    EXPECT_EQ(0, m1.GetRows());
    EXPECT_EQ(0, m1.GetCols());
    EXPECT_EQ(nullptr, m1.GetMatrix());
}


TEST(Method, Equal) {
    S21Matrix m1(4, 5), test1(4, 5);
    m1.Fill(5, 2);
    test1.Fill(5, 1);
    S21Matrix test2(m1);
    EXPECT_EQ(false, m1.EqMatrix(test1));
    EXPECT_EQ(true, m1.EqMatrix(test2));
}

TEST(Method, Sum) {
    S21Matrix m1(4, 5), m2(4, 5), m3(4, 5), m4(4, 5);
    m1.Fill(3);
    m2.Fill(6);
    m3.Fill(8);
    m4.Fill(9);
    m1.SumMatrix(m2);
    EXPECT_NE(false, m1.EqMatrix(m4));  //  means equal
    EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, Sub) {
    S21Matrix m1(4, 5), m2(4, 5), m3(4, 5), m4(4, 5);
    m1.Fill(9);
    m2.Fill(6);
    m3.Fill(8);
    m4.Fill(3);
    m1.SubMatrix(m2);
    EXPECT_NE(false, m1.EqMatrix(m4));  //  means equal
    EXPECT_EQ(false, m1.EqMatrix(m3));
}

TEST(Method, MulNumber) {
    S21Matrix m1(4, 5), m2(4, 5), m3(4, 5);
    int num = 2;
    m1.Fill(3);
    m2.Fill(8);
    m3.Fill(6);
    m1.MulNumber(num);
    EXPECT_NE(false, m1.EqMatrix(m3));  //  means equal
    EXPECT_EQ(false, m1.EqMatrix(m2));
}

TEST(Methods, MultMatrix) {
  S21Matrix m1;
  m1.Fill(1, 1);
  S21Matrix test1;
  test1.Fill(4);
  m1.MulMatrix(test1);
  S21Matrix res1;
  res1(0, 0) = 24;
  res1(0, 1) = 24;
  res1(0, 2) = 24;
  res1(1, 0) = 60;
  res1(1, 1) = 60;
  res1(1, 2) = 60;
  res1(2, 0) = 96;
  res1(2, 1) = 96;
  res1(2, 2) = 96;

  S21Matrix m2(2, 4);
  m2.Fill(2, 0.2);
  S21Matrix test2(3, 2);
  test2.Fill(4);
  test2.MulMatrix(m2);
  S21Matrix res2(3, 4);
  res2(0, 0) = 19.2;
  res2(0, 1) = 20.8;
  res2(0, 2) = 22.4;
  res2(0, 3) = 24;
  res2(1, 0) = 19.2;
  res2(1, 1) = 20.8;
  res2(1, 2) = 22.4;
  res2(1, 3) = 24;
  res2(2, 0) = 19.2;
  res2(2, 1) = 20.8;
  res2(2, 2) = 22.4;
  res2(2, 3) = 24;

  EXPECT_EQ(true, m1.EqMatrix(res1));
  EXPECT_EQ(true, test2.EqMatrix(res2));
  EXPECT_ANY_THROW(m1.MulMatrix(m2));

//   m1.Pr();
//   cout << "\n";
//   res1.Pr();
}

TEST(Methods, Transpose) {
  S21Matrix m1, m2;
  m1.Fill(1, 1);
  m1.Transpose();
  m2(0, 0) = 1;
  m2(0, 1) = 4;
  m2(0, 2) = 7;
  m2(1, 0) = 2;
  m2(1, 1) = 5;
  m2(1, 2) = 8;
  m2(2, 0) = 3;
  m2(2, 1) = 6;
  m2(2, 2) = 9;

  EXPECT_EQ(true, m2.EqMatrix(m1.Transpose()));

  // m1.Pr();
  // cout << "\n";
  // m1.Transpose().Pr();
}

TEST(Methods, Complements) {
  S21Matrix m1, res1, test1;
  m1.Fill(1, 1);
  test1 = m1.CalcComplements();
  res1(0, 0) = -3;
  res1(0, 1) = 6;
  res1(0, 2) = -3;
  res1(1, 0) = 6;
  res1(1, 1) = -12;
  res1(1, 2) = 6;
  res1(2, 0) = -3;
  res1(2, 1) = 6;
  res1(2, 2) = -3;
  EXPECT_EQ(true, test1.EqMatrix(res1));

  S21Matrix m2(4, 5);
  EXPECT_ANY_THROW(m2.CalcComplements());

	// m1.Pr();
  cout << "\n";
  m1.CalcComplements().Pr();
	cout << m1.Determinant();
	cout << "\n";
}

TEST(Methods, Determinant) {
  S21Matrix m1, test1;
  m1.Fill(1, 1);
	double det1;
  det1 = m1.Determinant();
  EXPECT_EQ(0, det1);

  S21Matrix m2(4, 5);
  EXPECT_ANY_THROW(m2.Determinant());

	// m1.Pr();
  cout << "\n";
  m1.CalcComplements().Pr();
	cout << m1.Determinant();
	cout << "\n";
}
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
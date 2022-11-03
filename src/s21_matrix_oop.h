#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cmath>

class S21Matrix {
 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated

  void AllocateMemory_();
  void CopyValue_(const S21Matrix& other);
  void CleanMemory_();
  double Det_(int n);
  S21Matrix MiniMatrix_(int n, int c);

 public:
  // constructors
  S21Matrix();                        // default constructor
  S21Matrix(int rows, int cols);      // parameterized constructor
  S21Matrix(const S21Matrix& other);  // copy constructor
  S21Matrix(S21Matrix&& other);       // move constructor
  ~S21Matrix();                       // destructor

  // accessors and mutators
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  double** GetMatrix() const;

  // public methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators overloads
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator*(const double& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& other);

  void Fill(double n);
  void Fill(double n, double add);
};

#endif

#include "s21_matrix_oop.h"
using namespace std;

void S21Matrix::AllocateMemory_() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::CopyValue_(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::CleanMemory_() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

// constructors
S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  AllocateMemory_();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("Incorrect input: size less ");
  }
  AllocateMemory_();
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory_();
  CopyValue_(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_; // CopyValue_(other);
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_= 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
      CleanMemory_();
    }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// accessors and mutators
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }
double** S21Matrix::GetMatrix() const { return matrix_; }

// add functions
void S21Matrix::Fill(double n) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = n;
    }
  }
}

void S21Matrix::Fill(double n, double add) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = n;
      n += add;
    }
  }
}

void S21Matrix::FillRev(double n, double sub) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = n;
      n -= sub;
    }
  }
}

// public methods
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 0.0000001) {
          i = rows_;  /* break */
          j = cols_;  /* break */
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::exception();
  }
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

// operators overloads
double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input: index is out of range");
  }
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input: index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix &S21Matrix::operator=(const S21Matrix& other) {
  CleanMemory_();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory_();
  CopyValue_(other);
  return *this;
}

void S21Matrix::Pr() const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      cout << setw(15) << setprecision(10) << matrix_[i][j];
    }
    cout << endl;
  }
}

////////
// int main() {}
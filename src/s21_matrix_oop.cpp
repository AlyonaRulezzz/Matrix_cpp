#include "s21_matrix_oop.hpp"
using namespace std;

void S21Matrix::AllocateMemory_() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

// constructors
S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  AllocateMemory_();
}

// accessors and mutators
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

////////
// int main() {}
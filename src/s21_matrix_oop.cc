#include "s21_matrix_oop.h"
using namespace std;

void S21Matrix::AllocateMemory_() {
  matrix_ = new double*[rows_];
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

double S21Matrix::Det_(int n) {
  double det = 0;
  if (n == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    S21Matrix submat(rows_, cols_);
    for (int c = 0; c < n; c++) {
      int sub_i = 0;
      for (int i = 1; i < n; i++) {
        int sub_j = 0;
        for (int j = 0; j < n; j++) {
          if (j != c) {
            submat.matrix_[sub_i][sub_j] = matrix_[i][j];
            sub_j++;
          }
        }
        sub_i++;
      }
      det += pow(-1, c) * matrix_[0][c] * submat.Det_(n - 1);
    }
  }
  return det;
}

S21Matrix S21Matrix::MiniMatrix_(int n, int c) {
  S21Matrix minimat(rows_ - 1, cols_ - 1);
  int sub_i = 0;
  for (int i = 0; i < rows_; i++) {
    int sub_j = 0;
    if (i != n) {
      for (int j = 0; j < cols_; j++) {
        if (j != c) {
          minimat.matrix_[sub_i][sub_j] = matrix_[i][j];
          sub_j++;
        }
      }
      sub_i++;
    }
  }
  return minimat;
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

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory_();
  CopyValue_(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;  // CopyValue_(other);
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
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
          i = rows_; /* break */
          j = cols_; /* break */
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

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input: it's not a square matrix");
  }
  S21Matrix tmp(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor_mat = this->MiniMatrix_(i, j);
      double r = minor_mat.Determinant();
      tmp.matrix_[i][j] = pow((-1), i + j) * r;
    }
  }
  return tmp;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input: it's not a square matrix");
  }
  double determinant;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else {
    determinant = this->Det_(rows_);
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (Determinant() == 0) {
    throw ::exception();
  }
  S21Matrix alg_dop = CalcComplements();
  S21Matrix transpose_alg_dop = alg_dop.Transpose();
  transpose_alg_dop.MulNumber(pow(Determinant(), -1));
  return transpose_alg_dop;
}

// operators overloads
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Incorrect input: different matrix size");
  }
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input: index is out of range");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input: index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  CleanMemory_();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory_();
  CopyValue_(other);
  return *this;
}

// print
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
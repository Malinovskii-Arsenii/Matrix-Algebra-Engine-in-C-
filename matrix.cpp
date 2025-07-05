#include <iostream>

using namespace std;

class Matrix {
 public:
  // Конструктор класса. По умолчанию она проинициализирована 0
  Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      data_[i] = new double[cols_];
    }
  }

  // Получение элемента с помощью скобок
  double* operator[](int index) const { return data_[index]; }

  // Сложение двух матриц
  Matrix operator+(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      cout << "\nНесовместимые размеры матрицы для сложения\n";
      return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result[i][j] = data_[i][j] + other[i][j];
      }
    }
    return result;
  }

  // Вычитание матриц
  Matrix operator-(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      cout << "\nНесовместимые размеры матрицы для вычитания\n";
      return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result[i][j] = data_[i][j] - other[i][j];
      }
    }
    return result;
  }

  // Умножение матриц
  Matrix operator*(const Matrix& other) {
    if (cols_ != other.rows_) {
      cout << "\nНесовместимые размеры матрицы для умножения\n";
      return Matrix(0, 0);
    }

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        double sum = 0;
        for (int k = 0; k < cols_; k++) {
          sum += data_[i][k] * other[k][j];
        }
        result[i][j] = sum;
      }
    }
    return result;
  }

  Matrix inverse() const {
    if (rows_ != cols_) {
      cout << "\nМатрица не квадратная\n";
      return Matrix(0, 0);
    }

    // Создаем новую матрицу
    Matrix mat(*this);

    // Создаем единичную матрицу того же размера
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      result[i][i] = 1;
    }

    // Используем метод исключения Гаусса, чтобы преобразовать матрицу
    for (int i = 0; i < rows_; i++) {
      // Ищем опорный элемент
      int pivot = i;
      for (int j = i + 1; j < rows_; j++) {
        if (abs(mat[j][i]) > abs(mat[pivot][i])) {
          pivot = j;
        }
      }
      if (pivot != i) {
        // Меняем местами строки, чтобы поместить опорный элемент по диагонали
        swap(mat.data_[i], mat.data_[pivot]);
        swap(result.data_[i], result.data_[pivot]);
      }
      if (mat[i][i] == 0) {
        cout << "\nНевозможно найти обратную матрицу\n";
        return Matrix(0, 0);
      }
      // Делим строку на опорный элемент
      double pivot_inv = 1.0 / mat[i][i];
      mat[i][i] = 1;
      for (int j = i + 1; j < cols_; j++) {
        mat[i][j] *= pivot_inv;
      }
      for (int j = 0; j < cols_; j++) {
        result[i][j] *= pivot_inv;
      }
      // Удаляем опорный элемент
      for (int j = 0; j < rows_; j++) {
        if (j != i) {
          double factor = mat[j][i];
          mat[j][i] = 0;
          for (int k = i + 1; k < cols_; k++) {
            mat[j][k] -= mat[i][k] * factor;
          }
          for (int k = 0; k < cols_; k++) {
            result[j][k] -= result[i][k] * factor;
          }
        }
      }
    }
    return result;
  }

  // Деление матриц
  Matrix operator/(const Matrix& other) {
    if (cols_ != other.rows_) {
      cout << "\nНесовместимые размеры матрицы для деления\n";
      return Matrix(0, 0);
    }

    Matrix other_inv = const_cast<Matrix&>(other).inverse();
    if (other_inv.rows_ == 0) {
      cout << "\nДеление невозможно\n";
      return Matrix(0, 0);
    }

    return (*this) * other_inv;
  }

  int get_size(){
    int size = 1;
    if (rows_ == 0 && cols_ == 0)
    size = 0;
    return size;
  }

 private:
  int rows_;
  int cols_;
  double** data_;
};

void print_matrix(Matrix matrix, int m, int n) {
  if (matrix.get_size() == 0) {
    cout << "Нулевая матрица";
  } else {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << '\n';
    }
  }
}

int main() {
  int a;
  int b;
  cout << "Введите размер матриц\n";
  cout << "m = ";
  cin >> a;
  cout << "n = ";
  cin >> b;
  Matrix m1(a, b);

  for (int i = 0; i < a; i++) {  // Заполняем матрицы
    for (int j = 0; j < b; j++) {
      cout << "Введите элемент [" << i << "]" << "[" << j << "] = ";
      cin >> m1[i][j];
    }
  }

  int a1, b1;
  cout << "Введите размер матриц\n";
  cout << "m = ";
  cin >> a1;
  cout << "n = ";
  cin >> b1;
  Matrix m2(a1, b1);
    for (int i = 0; i < a1; i++) {  // Заполняем матрицы
    for (int j = 0; j < b1; j++) {
      cout << "Введите элемент [" << i << "]" << "[" << j << "] = ";
      cin >> m2[i][j];
    }
  }
  cout << "Matrix 1: \n";
  print_matrix(m1, a, b);
  cout << "Matrix 2: \n";
  print_matrix(m2, a1, b1);

  Matrix m = m1 + m2;
  cout << "==SUM==\n";
  print_matrix(m, a, b);

  m = m1 - m2;
  cout << "==SUB==\n";
  print_matrix(m, a, b);

  m = m1 * m2;
  cout << "==MUL==\n";
  print_matrix(m, a, b);

  m = m1 / m2;
  cout << "==DIV==\n";
  cout << "Matrix 1: \n";

  m = m1.inverse();
  cout << "INVERSE matrix\n";
  cout << "Matrix 1: \n";

  return 0;
}

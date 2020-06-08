#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

class Matrix {
public:
	Matrix(){
		matrix = {};
		num_rows_ = num_cols_ = 0;
	}
	Matrix(int num_rows, int num_cols) {
		Reset(num_rows, num_cols);
	}
	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("out_of_range");
		}
		num_rows_ = num_rows;
		num_cols_ = num_cols;
		matrix.assign(num_rows_, vector<int>(num_cols_));
	}
	int At(int row, int col) const {
		return matrix.at(row).at(col);
	}
	int& At(int row, int col) {
		return matrix[row][col];
	}
	int GetNumRows() const {
		return num_rows_;
	}
	int GetNumColumns() const {
		return num_cols_;
	}
	bool isEmpty() const {
		return num_rows_ == 0 || num_cols_ == 0;
	}
private:
	vector<vector<int>> matrix;
	int num_rows_, num_cols_;
};

istream& operator>>(istream& in, Matrix& m) {
	int rows, cols;
	in >> rows >> cols;
	m.Reset(rows, cols);

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			in >> m.At(row, col);
		}
	}
	return in;
}

ostream& operator<<(ostream& out, const Matrix& m) {
	int rows = m.GetNumRows();
	int cols = m.GetNumColumns();
	out << rows << ' ' << cols << endl;

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			out << m.At(row, col) << ' ';
		}
		out << endl;
	}
	return out;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.isEmpty() && rhs.isEmpty()) {
		return true;
	}
	if (lhs.GetNumRows() != rhs.GetNumRows() ||
		lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	} else {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
		return true;
	}
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.isEmpty() && rhs.isEmpty()) {
		return {}; //сумма пустых матриц пустая матрица
	}
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("invalid_argument");
	}
	int rows = lhs.GetNumRows();
	int cols = lhs.GetNumColumns();
	Matrix result(rows, cols);
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}

/* tests
2 2
1 0
0 1
2 2
3 4
5 6

3 4
1 2 3 0
4 5 6 0
7 8 9 1
3 4
-1 -2 -3 0
-4 -5 -6 0
-7 -8 -8 -1

4 2
1 2
1 2
1 2
1 2
4 2
-1 -2
0 0
-1 -2
0 0

0 0
0 0

0 3
0 3

0 3
0 5

 */

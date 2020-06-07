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
	}
	Matrix(int num_rows, int num_cols) {
		Reset(num_rows, num_cols);
	}
	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("");
		}
		vector<vector<int>> temp(num_rows, vector<int>(num_cols));
		matrix = temp;
	}
	int At(int row, int col) const {
		if (row > GetNumRows() - 1 || row < 0 ||
			col > GetNumColumns() - 1 || col < 0) {
			throw out_of_range("");
		}
		return matrix[row][col];
	}
	int& At(int row, int col) {
		if (row > GetNumRows() - 1 || row < 0 ||
			col > GetNumColumns() - 1 || col < 0) {
			throw out_of_range("");
		}
		return matrix[row][col];
	}
	int GetNumRows() const {
		return matrix.size();
	}
	int GetNumColumns() const {
		if (matrix.size() == 0) { //если число строк = 0 (таблица пустая), то и число столбцов = 0
			return 0;
		} else {
			return matrix[0].size();
		}
	}
	void SetVal(int row, int col, int new_value) {
		if (row > GetNumRows() - 1 || row < 0 ||
			col > GetNumColumns() - 1 || col < 0) {
			throw out_of_range("");
		}
		if (row < matrix.size() && col < matrix[0].size()) {
			matrix[row][col] = new_value;
		} else {
			throw out_of_range("");
		}
	}
private:
	vector<vector<int>> matrix;
};

istream& operator>>(istream& s, Matrix& m) {
	int rows, cols;
	s >> rows >> cols;
	m.Reset(rows, cols);

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			int value;
			s >> value;
			m.SetVal(i, j, value);
		}
	}
	return s;
}

ostream& operator<<(ostream& s, const Matrix& m) {
	int rows = m.GetNumRows();
	int cols = m.GetNumColumns();
	s << rows << ' ' << cols << endl;

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			s << m.At(i, j) << ' ';
		}
		s << endl;
	}
	return s;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() == 0 && rhs.GetNumRows() == 0 &&
		lhs.GetNumColumns() == 0 && rhs.GetNumColumns() == 0) {
		return true;
	}
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
		int i, j;
		for (i = 0; i < lhs.GetNumRows(); ++i) {
			for (j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {

	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("");
	}
	int rows = lhs.GetNumRows();
	int cols = lhs.GetNumColumns();
	Matrix result(rows, cols);
	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			result.SetVal(i, j, lhs.At(i, j) + rhs.At(i, j));
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

#include "ComplexMatrix.h"


ComplexMatrix::ComplexMatrix()
{
	_matrix = std::vector<std::vector<ComplexNumber>>(0);
	_rows = _columns = 0;
}

ComplexMatrix::ComplexMatrix(const ComplexMatrix& matrix)
{
	_matrix = std::vector<std::vector<ComplexNumber>>(matrix._matrix);
	_rows = matrix._rows;
	_columns = matrix._columns;
}

ComplexMatrix::ComplexMatrix(std::vector<std::vector<ComplexNumber>> matrix)
{
	for (int i = 0; i < matrix.size() - 1; i++)
		if(matrix[i].size() != matrix[i + 1].size())
			throw std::logic_error("Incorrect matrix.");

	_matrix = std::vector<std::vector<ComplexNumber>>(matrix);
	_rows = matrix.size();
	_columns = matrix[0].size();
}

ComplexMatrix& ComplexMatrix::operator=(const ComplexMatrix & matrix)
{
	if (this == &matrix)
		return *this;

	_matrix = std::vector<std::vector<ComplexNumber>>(matrix._matrix);
	_rows = matrix._rows;
	_columns = matrix._columns;
	return *this;
}

ComplexMatrix ComplexMatrix::operator*(const ComplexMatrix & matrix) const
{
	if (_columns != matrix._rows) // умножение возможно, если число столбцов первой матрицы равно числу строк второй матрицы
		throw std::logic_error("Error in multiplication of matrixes.");

	ComplexMatrix result;
	result._matrix = std::vector<std::vector<ComplexNumber>>(_rows);

	for (int i = 0; i < _rows; i++)
		result._matrix[i] = std::vector<ComplexNumber>(matrix._columns);

	result._rows = _rows;
	result._columns = matrix._columns;

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < matrix._columns; j++)
			for (int k = 0; k < _columns; k++)
				result._matrix[i][j] = result._matrix[i][j] + _matrix[i][k] * matrix._matrix[k][j];

	return result;
}

ComplexMatrix ComplexMatrix::operator*(const ComplexNumber & num) const
{
	ComplexMatrix result(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			result._matrix[i][j] = result._matrix[i][j] * num;

	return result;
}

ComplexMatrix operator*(const ComplexNumber & num, const ComplexMatrix & matrix)
{
	return matrix * num;
}

ComplexMatrix ComplexMatrix::operator+(const ComplexMatrix & matrix) const
{
	if (_rows != matrix._rows || _columns != matrix._columns)
		throw std::logic_error("Error in addition of matrixes.");

	ComplexMatrix result(*this);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _columns; j++)
			result._matrix[i][j] = _matrix[i][j] + matrix._matrix[i][j];

	return result;
}

ComplexMatrix ComplexMatrix::operator~()
{
	if (_columns != _rows)
		throw std::logic_error("Error in transportation of matrix.");

	ComplexMatrix result(*this);

	for (int i = 0; i < _columns; i++)
		for (int j = 0; j < i; j++)
		{
			result._matrix[i][j] = _matrix[j][i];
			result._matrix[j][i] = _matrix[i][j];
		}

	return result;
}

ComplexNumber ComplexMatrix::operator()(unsigned int npos, unsigned int mpos) const
{
	if (npos >= _rows || mpos >= _columns)
		throw std::out_of_range("Error: bad index.");

	return _matrix[npos][mpos];
}

ComplexMatrix::~ComplexMatrix()
{
	for (int i = 0; i < _rows; i++)
		_matrix[i].clear();

	_matrix.clear();
}

std::ofstream & operator<<(std::ofstream & ofs, const ComplexMatrix & matrix)
{
	for (int i = 0; i < matrix._rows; i++)
	{
		for (int j = 0; j < matrix._columns; j++)
			ofs << matrix._matrix[i][j] << "  ";
		ofs << "\n";
	}

	return ofs;
}

std::ifstream & operator>>(std::ifstream & ifs, ComplexMatrix & matrix)
{
	std::string str;
	int n = 0, m = 0;
	std::vector<ComplexNumber> current;
	ComplexNumber num;
	std::vector<std::vector<ComplexNumber>> matr;
	while (getline(ifs, str))
	{
		if (str == "")
			break;
		current = ComplexNumber::GetNumbersFromString(str);
		if (matr.size() != 0 && current.size() != matr[0].size())
			throw std::logic_error("Incorrect matrix in file");
		matr.push_back(current);
	}
	matrix._matrix = matr;
	if (matr.size() != 0)
	{
		matrix._rows = matr.size();
		matrix._columns = matr[0].size();
	}
	else
	{
		matrix._rows = 0;
		matrix._columns = 0;
	}
	
	return ifs;
}
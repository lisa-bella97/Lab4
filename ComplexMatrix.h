#ifndef _COMPLEXMATRIX_H_
#define _COMPLEXMATRIX_H_
#include "ComplexNumber.h"
#include <stdexcept>
#include <vector>

class ComplexMatrix
{
private:
	std::vector<std::vector<ComplexNumber>> _matrix; 
	unsigned int _rows; 
	unsigned int _columns; 
public:
	ComplexMatrix();
	ComplexMatrix(const ComplexMatrix& matrix);
	ComplexMatrix(std::vector<std::vector<ComplexNumber>> matrix);
	ComplexMatrix& operator=(const ComplexMatrix & matrix);
	ComplexMatrix operator*(const ComplexMatrix & matrix) const;
	ComplexMatrix operator*(const ComplexNumber & num) const;
	friend ComplexMatrix operator*(const ComplexNumber & num, const ComplexMatrix & matrix);
	ComplexMatrix operator+(const ComplexMatrix & matrix) const;
	ComplexMatrix operator~();
	ComplexNumber operator()(unsigned int npos, unsigned int mpos) const;
	friend std::ofstream & operator<<(std::ofstream & ofs, const ComplexMatrix & matrix);
	friend std::ifstream & operator>>(std::ifstream & ifs, ComplexMatrix & matrix);
	~ComplexMatrix();
};
#endif

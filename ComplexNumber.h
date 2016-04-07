#ifndef _COMPLEXNUMBER_H_
#define _COMPLEXNUMBER_H_

#include <fstream>
#include <string>
#include <vector>

class ComplexNumber
{
private:
	double _real; 
	double _imaginary; 
public:
	ComplexNumber() : _real(0.0), _imaginary(0.0) { }
	ComplexNumber(double r, double im) : _real(r), _imaginary(im) { }
	ComplexNumber(const ComplexNumber& num) : _real(num._real), _imaginary(num._imaginary) { }
	static std::vector<ComplexNumber> GetNumbersFromString(std::string source); 
	ComplexNumber& operator=(const ComplexNumber & number);
	ComplexNumber operator+(const ComplexNumber & number) const;
	ComplexNumber operator*(const ComplexNumber & number) const;
	ComplexNumber operator*(double x) const;
	friend ComplexNumber operator*(double x, const ComplexNumber & number);
	friend std::ofstream & operator<<(std::ofstream & ofs, const ComplexNumber & number);
	friend std::ifstream & operator>>(std::ifstream & ifs, ComplexNumber & number);
};

#endif

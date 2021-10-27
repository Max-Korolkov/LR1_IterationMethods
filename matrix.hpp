#include <vector>
#include <iostream>

#pragma once

template<typename T>
class Matrix
{
public:
	Matrix();
	Matrix(const size_t _rows, const size_t _cols);
	Matrix(std::initializer_list<std::initializer_list<T>> list);
	~Matrix();

	size_t Rows() const;
	size_t Columns() const;

	void Print() const;
	T Determinant() const;

	const T* operator[](size_t row) const;
	const T& operator()(size_t row, size_t col) const;
	T* operator[](size_t row);
	T& operator()(size_t row, size_t col);

private:
	size_t rows;
	size_t cols;
	std::vector<T> data;
};

template<typename T>
Matrix<T>::Matrix() :
	rows(0),
	cols(0),
	data()
{}

template<typename T>
Matrix<T>::Matrix(const size_t _rows, const size_t _cols) :
	rows(_rows),
	cols(_cols),
	data(_rows * _cols)
{}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) :
	rows(list.size()),
	cols(0)
{
	for (auto row : list) {
		int currCol = 0;
		for (auto &elem : row) {
			data.push_back(elem);
			++currCol;
		}
		if (currCol != cols) {
			cols == 0 ? cols = currCol : throw std::invalid_argument("invalid initializer list");
		}
	}
}

template<typename T>
Matrix<T>::~Matrix()
{ data.clear(); }

template<typename T>
size_t Matrix<T>::Rows() const
{ return rows; }

template<typename T>
size_t Matrix<T>::Columns() const
{ return cols; }

template<typename T>
void Matrix<T>::Print() const
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << data[i * cols + j] << " ";
		}
		std::cout << "\n";
	}
}

template<typename T>
const T* Matrix<T>::operator[](size_t row) const
{ return &data[row * cols]; }

template<typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const
{ return data[row * cols + col]; }

template<typename T>
T* Matrix<T>::operator[](size_t row)
{ return &data[row * cols]; }

template<typename T>
T& Matrix<T>::operator()(size_t row, size_t col)
{ return data[row * cols + col]; }

template<typename T>
T Matrix<T>::Determinant() const
{
	T res = 0;
	if (rows != cols) {
		throw std::runtime_error("not a square matrix");
	}
	if (rows == 1) {
		res = (*this)(0,0);
	} else if (rows == 2) {
		res = (*this)(0,0) * (*this)(1,1) - (*this)(0,1) * (*this)(1,0);
	} else {
		int sign = rows % 2 == 0 ? -1 : 1;
		// пройдем по всем стобцам последней строки
		for (size_t j = 0; j < cols; ++j) {
			// Найдем минор матрицы
			Matrix<T> minor(rows - 1, cols - 1);
			for(size_t rowMinor = 0; rowMinor < rows - 1; ++rowMinor) {
				for (size_t colMinor = 0; colMinor < cols - 1; ++colMinor) {
					minor[rowMinor][colMinor] = (*this)(rowMinor, colMinor < j ? colMinor : colMinor + 1);
				}
			}
			res += sign * (*this)(rows - 1, j) * minor.Determinant();
			sign = -sign;
		}
	}
	return res;
}

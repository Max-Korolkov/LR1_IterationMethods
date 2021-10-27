#include "Matrix.hpp"

int main()
{
	Matrix<double> a{ {0.1, 0.33, 7, 0}, {2.1, 0.9, 3, 6}, {1.7, 9.8, 3.4, 1}, {-5, 0.2, -3.6, 9} };
	a.Print();
	std::cout << "\nDeterminant = " << a.Determinant() << std::endl;
	return 0;
}
// Empty line

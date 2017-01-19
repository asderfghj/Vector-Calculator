#ifndef _MATRICES_H_
#define _MATRICES_H_
#include "vector.h"

class Matrix 
{
	private:
		double m_matrix[4][4];
	public:
		Matrix();
		double GetMatrix(int _x, int _y);
		double SetMatrix(int _x, int _y, double _i);
		void PrintMatrix(void);
		~Matrix();


};

Matrix MatAdd(Matrix _mat1, Matrix _mat2);//see line 63 in matricies.cpp
Matrix MatSub(Matrix _mat1, Matrix _mat2);//see line 85 in matricies.cpp
Matrix MatSMulti (Matrix &_mat, double _scalar);//see line 107 in matricies.cpp
Matrix MatSDiv(Matrix &_mat, double _scalar);//see line 128 in matricies.cpp
Vector4 MatVecMulti(Matrix _mat, Vector4 _vector);//see line 149 in matricies.cpp
Matrix MatMatMulti(Matrix _mat, Matrix _mat2);//see line 203 in matricies.cpp
double RowBCol(Matrix _mat, Matrix _mat2, int _x, int _y);//see line 225 in matricies.cpp

#endif
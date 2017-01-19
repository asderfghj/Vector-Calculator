#include "matrices.h"
#include "vector.h"
#include <iostream>

/*Matrix class functions*/
Matrix::Matrix()
{
	int i, j;
	for(i = 0; i <= 3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			m_matrix[i][j] = 0.0;
		}
	
	}

}

Matrix::~Matrix()
{
}

double Matrix::GetMatrix(int _x, int _y)
{
	return m_matrix[_x][_y];

}

double Matrix::SetMatrix(int _x, int _y, double _i)
{
	m_matrix[_x][_y] = _i;
	return _i;

}

void Matrix::PrintMatrix(void)
{
	int i, j;

	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			if(j == 3)
			{
			std::cout << GetMatrix(j, i) <<std::endl;
			}
			else
			{
				std::cout << GetMatrix(j, i)<<"	";
			}
		}
	
	}


}
/*END matrix class functions*/

/*external matrix functions*/

/*
	FUNCTION:		MatAdd()
	PARAMETERS:		_mat1, the first matrix in the addition
					_mat2, the second matrix in the addition
	RETURNS:		pMat, the product of the two matricies
	DESCRIPTION:	a function that adds two matricies together using a for 
					loop
*/
Matrix MatAdd (Matrix _mat1, Matrix _mat2)
{
	int i, j;
	Matrix pMat;
	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			pMat.SetMatrix(i,j,(_mat1.GetMatrix(i,j)+_mat2.GetMatrix(i,j)));
		}
	}
	return pMat;
}

/*
	FUNCTION:		MatSub()
	PARAMETERS:		_mat1, the first matrix in the addition
					_mat2, the second matrix in the addition
	RETURNS:		pMat, the product of the two matricies
	DESCRIPTION:	a function that subtracts 1 matrix from another 
					using a for loop
*/
Matrix MatSub (Matrix _mat1, Matrix _mat2)
{
	int i, j;
	Matrix pMat;
	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			pMat.SetMatrix(i,j,(_mat1.GetMatrix(i,j)-_mat2.GetMatrix(i,j)));
		}
	}
	return pMat;
}

/*
	FUNCTION:		MatSMulti()
	PARAMETERS:		_mat, the matrix to be multiplied
					_scalar, the value which the matrix will be multiplied by
	RETURNS:		_mat, the old matrix multiplied
	DESCRIPTION:	a function that multiplies a matrix by
					a scale value
*/
Matrix MatSMulti (Matrix &_mat, double _scalar)
{
	int i, j;
	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			_mat.SetMatrix(i,j,(_mat.GetMatrix(i,j)*_scalar));
		}
	}
	return _mat;
}

/*
	FUNCTION:		MatSDiv()
	PARAMETERS:		_mat, the matrix to be divided
					_scalar, the value which the matrix will be divided by
	RETURNS:		_mat, the old matrix divided
	DESCRIPTION:	a function that divides a matrix by
					a scale value
*/
Matrix MatSDiv (Matrix &_mat, double _scalar)
{
	int i, j;
	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			_mat.SetMatrix(i,j,(_mat.GetMatrix(i,j)/_scalar));
		}
	}
	return _mat;
}

/*
	FUNCTION:		MatVecMulti()
	PARAMETERS:		_mat, the matrix to be used
					_vector, thevector to be used
	RETURNS:		product, the new vector that have been mutiplied by the matrix
	DESCRIPTION:	a function that multiplies a vector
					by a matrix
*/
Vector4 MatVecMulti (Matrix _mat, Vector4 _vector)
{
	Matrix tempMat;
	Vector4 product;
	int i, j;
	for(i = 0; i<=3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			switch(j)
			{
				case 0:
				{
					tempMat.SetMatrix(j, i, (_mat.GetMatrix(j,i) * _vector.Getx()));
					break;

				}
				case 1:
				{
					tempMat.SetMatrix(j, i, (_mat.GetMatrix(j,i) * _vector.Gety()));
					break;
				}
				case 2:
				{
					tempMat.SetMatrix(j, i, (_mat.GetMatrix(j,i) * _vector.Getz()));
					break;
				}
				case 3:
				{
					tempMat.SetMatrix(j, i, (_mat.GetMatrix(j,i) * _vector.Getw()));
					break;
				}
			
			}
		}
	}
	tempMat.PrintMatrix();
	std::cout << std::endl;
	product.Setx(tempMat.GetMatrix(0,0) + tempMat.GetMatrix(1,0) + tempMat.GetMatrix(2,0) + tempMat.GetMatrix(3,0));
	product.Sety(tempMat.GetMatrix(0,1) + tempMat.GetMatrix(1,1) + tempMat.GetMatrix(2,1) + tempMat.GetMatrix(3,1));
	product.Setz(tempMat.GetMatrix(0,2) + tempMat.GetMatrix(1,2) + tempMat.GetMatrix(2,2) + tempMat.GetMatrix(3,2));
	product.Setw(tempMat.GetMatrix(0,3) + tempMat.GetMatrix(1,3) + tempMat.GetMatrix(2,3) + tempMat.GetMatrix(3,3));
	return product;

}

/*
	FUNCTION:		MatMatMulti()
	PARAMETERS:		_mat, the first matrix to be multiplied
					_mat2, the second matrix to be multiplied
	RETURNS:		finMat, the product of the two matrices
	DESCRIPTION:	a function that multiplies two matricies
					together
*/
Matrix MatMatMulti(Matrix _mat, Matrix _mat2)
{
	Matrix finMat;
	int i, j;
	for(i = 0; i <= 3; i++)
	{
		for(j = 0; j <= 3; j++)
		{
			finMat.SetMatrix(j, i, RowBCol(_mat, _mat2, j, i));
		}
	}
	return finMat;
}

/*
	FUNCTION:		RowBCol()
	PARAMETERS:		_mat, the first matrix to be multiplied
					_mat2, the second matrix to be multiplied
					_x, the current x pointer
					_y, the current y pointer
	RETURNS:		retVal, the value that is returned
	DESCRIPTION:	a function that works out a single value of the matrix multiplication
*/
double RowBCol(Matrix _mat, Matrix _mat2, int _x, int _y)
{
	double retVal;
	switch(_x)
	{
		case 0:
		{
			retVal = ((_mat.GetMatrix(_x, _y) * _mat2.GetMatrix(_x, 0)) + 
					  (_mat.GetMatrix(_x+1, _y) * _mat2.GetMatrix(_x, 1)) + 
					  (_mat.GetMatrix(_x+2, _y) * _mat2.GetMatrix(_x, 2)) + 
					  (_mat.GetMatrix(_x+3, _y) * _mat2.GetMatrix(_x, 3)));
			break;
		}
		case 1:
		{
			retVal = ((_mat.GetMatrix(_x-1, _y) * _mat2.GetMatrix(_x, 0)) +
					  (_mat.GetMatrix(_x, _y) * _mat2.GetMatrix(_x, 1)) +
					  (_mat.GetMatrix(_x+1, _y) * _mat2.GetMatrix(_x, 2)) +
					  (_mat.GetMatrix(_x+2, _y) * _mat2.GetMatrix(_x, 3)));
			break;
		}
		case 2:
		{
			retVal = ((_mat.GetMatrix(_x-2, _y) * _mat2.GetMatrix(_x, 0)) +
					  (_mat.GetMatrix(_x-1, _y) * _mat2.GetMatrix(_x, 1)) +
					  (_mat.GetMatrix(_x, _y) * _mat2.GetMatrix(_x, 2)) +
					  (_mat.GetMatrix(_x+1, _y) * _mat2.GetMatrix(_x, 3)));
			break;
		}
		case 3:
		{
			retVal = ((_mat.GetMatrix(_x-3, _y) * _mat2.GetMatrix(_x, 0)) +
					  (_mat.GetMatrix(_x-2, _y) * _mat2.GetMatrix(_x, 1)) +
					  (_mat.GetMatrix(_x-1, _y) * _mat2.GetMatrix(_x, 2)) +
					  (_mat.GetMatrix(_x, _y) * _mat2.GetMatrix(_x, 3)));
			break;
		}
	}
	return retVal;
}

/*END external matrix functions*/
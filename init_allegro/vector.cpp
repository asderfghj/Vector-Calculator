#include "vector.h"

/*internal class functions*/

Vector4::Vector4()
{
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
	m_w = 0.0;

}

Vector4::~Vector4()
{
}

double Vector4::Getx()
{
	return m_x;
}

double Vector4::Setx(double _x)
{
	m_x = _x;
	return m_x;
}

double Vector4::Gety()
{
	return m_y;
}

double Vector4::Sety(double _y)
{
	m_y = _y;
	return m_y;
}

double Vector4::Getz()
{
	return m_z;
}

double Vector4::Setz(double _z)
{
	m_z = _z;
	return m_z;
}

double Vector4::Getw()
{
	return m_w;
}

double Vector4::Setw(double _w)
{
	m_w = _w;
	return m_w;
}

/*END internal class functions*/

/*vector*/

/*
	FUNCTION:		MatMulti()
	PARAMETERS:		_vector, the vector to be multiplied
					_scalar, the scalar value to multiply the vector by
	RETURNS:		_vector, the vector modifyed
	DESCRIPTION:	A function that multiplies a vector by a scalar value
*/
Vector4 VecMulti(Vector4 &_vector, double _scalar)
{
	double x = _vector.Getx();
	double y = _vector.Gety();
	double z = _vector.Getz();
	double w = _vector.Getw();

	_vector.Setx(x*_scalar);
	_vector.Sety(y*_scalar);
	_vector.Setz(z*_scalar);
	_vector.Setw(w*_scalar);
	
	return _vector;
}

/*
	FUNCTION:		MatDiv()
	PARAMETERS:		_vector, the vector to be divided
					_scalar, the scalar value to multiply the vector by
	RETURNS:		_vector, the vector modifyed
	DESCRIPTION:	A function that divides a vector by a scalar value
*/
Vector4 VecDiv(Vector4 &_vector, double _scalar)
{
	double x = _vector.Getx();
	double y = _vector.Gety();
	double z = _vector.Getz();
	double w = _vector.Getw();

	_vector.Setx(x/_scalar);
	_vector.Sety(y/_scalar);
	_vector.Setz(z/_scalar);
	_vector.Setw(w/_scalar);
	
	return _vector;
}

/*
	FUNCTION:		DotPr()
	PARAMETERS:		_vec1, the first vector
					_vec2, the second vector
	RETURNS:		the dot product of the two vectors
	DESCRIPTION:	A function that calculates the dot product of two vectors
*/
double DotPr(Vector4 &_vec1, Vector4 &_vec2)
{
	double x1 = _vec1.Getx();
	double y1 = _vec1.Gety();
	double z1 = _vec1.Getz();
	double w1 = _vec1.Setw(1);
	double x2 = _vec2.Getx();
	double y2 = _vec2.Gety();
	double z2 = _vec2.Getz();
	double w2 = _vec2.Setw(1);

	double x = x1 * x2;
	double y = y1 * y2;
	double z = z1 * z2;
	
	return x + y + z;
}

/*
	FUNCTION:		CrossPr()
	PARAMETERS:		_vec1, the first vector
					_vec2, the second vector
	RETURNS:		product, the cross product of the two vectors
	DESCRIPTION:	A function that calculates the cross product of two vectors
*/
Vector4 CrossPr (Vector4 &_vec1, Vector4 &_vec2)
{
	Vector4 product;
	double x1 = _vec1.Getx();
	double y1 = _vec1.Gety();
	double z1 = _vec1.Getz();
	double w1 = _vec1.Setw(1);
	double x2 = _vec2.Getx();
	double y2 = _vec2.Gety();
	double z2 = _vec2.Getz();
	double w2 = _vec2.Setw(1);

	double x = (y1*z2)-(z1*y2);
	double y = (z1*x2)-(x1*z2);
	double z = (x1*y2)-(y1*x2);

	product.Setx(x);
	product.Sety(y);
	product.Setz(z);

	return product;
}

/*
	FUNCTION:		VecAdd()
	PARAMETERS:		_vec1, the first vector
					_vec2, the second vector
	RETURNS:		product, addition of two vectors
	DESCRIPTION:	A function that adds two vectors together
*/
Vector4 VecAdd(Vector4 &_vec1, Vector4 &_vec2)
{
	Vector4 product;
	product.Setx(_vec1.Getx() + _vec2.Getx());
	product.Sety(_vec1.Gety() + _vec2.Gety());
	product.Setz(_vec1.Getz() + _vec2.Getz());
	product.Setw(_vec1.Getw() + _vec2.Getw());
	return product;
}

/*
	FUNCTION:		VecSub()
	PARAMETERS:		_vec1, the first vector
					_vec2, the second vector
	RETURNS:		product, subtraction of two vectors
	DESCRIPTION:	A function that subtracts 1 vector from another
*/
Vector4 VecSub(Vector4 &_vec1, Vector4 &_vec2)
{
	Vector4 product;
	product.Setx(_vec1.Getx() - _vec2.Getx());
	product.Sety(_vec1.Gety() - _vec2.Gety());
	product.Setz(_vec1.Getz() - _vec2.Getz());
	product.Setw(_vec1.Getw() - _vec2.Getw());
	return product;
}
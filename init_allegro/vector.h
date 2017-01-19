#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector4 
{
	private:
		double m_x;//vector co-ordinates
		double m_y;
		double m_z;
		double m_w;
	public:
		Vector4();
		double Getx();//getters and setters for co-ordinates
		double Setx(double _x);
		double Gety();
		double Sety(double _y);
		double Getz();
		double Setz(double _z);
		double Getw();
		double Setw(double _w);
		~Vector4();
};

Vector4 VecMulti(Vector4 &_vector, double _scalar);//see line 66 on vector.cpp
Vector4 VecDiv(Vector4 &_vector, double _scalar);//see line 88 on vector.cpp
double DotPr(Vector4 &_vec1, Vector4 &_vec2);//see line 110 on vector.cpp
Vector4 CrossPr (Vector4 &_vec1, Vector4 &_vec2);//see line 135 on vector.cpp
Vector4 VecAdd(Vector4 &_vec1, Vector4 &_vec2);//see line 165 on vector.cpp
Vector4 VecSub(Vector4 &_vec1, Vector4 &_vec2);//see line 182 on vector.cpp


#endif
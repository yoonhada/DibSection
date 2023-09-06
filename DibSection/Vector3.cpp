#include "stdafx.h"

CVector3::~CVector3(void)
{}

CVector3::CVector3(FLOAT _x, FLOAT _y, FLOAT _z)
: x(_x) 
, y(_y) 
, z(_z) 
{
}

//CVector3::CVector3(CPoint2 &rhs)
//: x(rhs.x) 
//, y(rhs.y) 
//, z(1) 
//{
//}

CVector3 CVector3::operator-() const
{
	return CVector3(-x, -y, -z);
}

CVector3 CVector3::operator+(const CVector3& rhs) const
{
	return CVector3(x + rhs.x, y + rhs.y, z + rhs.z); 
}

CVector3 CVector3::operator-(const CVector3& rhs) const
{
	return CVector3(x - rhs.x, y - rhs.y, z - rhs.z); 
}

CVector3 CVector3::operator*(const FLOAT scalar) const
{
	return CVector3(x * scalar, y * scalar, z * scalar); 
}

CVector3 CVector3::operator/(const FLOAT scalar) const
{
	return CVector3(x / scalar, y / scalar, z / scalar); 
}

CVector3 operator*(const FLOAT scalar, const CVector3& rhs)
{
	return CVector3(rhs.x * scalar, rhs.y * scalar, rhs.z * scalar);
}
//
//CVector3 CVector3::operator*(const CMatrix3& rhs) const
//{
//	CVector3 vertor;
//	vertor.x = x * rhs.x[0] + y * rhs.y[0] + z * rhs.z[0];
//	vertor.y = x * rhs.x[1] + y * rhs.y[1] + z * rhs.z[1];
//	vertor.z = x * rhs.x[2] + y * rhs.y[2] + z * rhs.z[2];
//
//	return vertor;
//}
//
//CVector3 CVector3::operator*(const CMatrix4& rhs) const
//{
//	CVector3 vertor;
//	vertor.x = x * rhs.x[0] + y * rhs.y[0] + z * rhs.z[0];
//	vertor.y = x * rhs.x[1] + y * rhs.y[1] + z * rhs.z[1];
//	vertor.z = x * rhs.x[2] + y * rhs.y[2] + z * rhs.z[2];
//
//	return vertor;
//}

FLOAT CVector3::operator*(const CVector3& rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

CVector3 CVector3::operator^(const CVector3& rhs) const
{
	CVector3 vertor;
	vertor.x = y * rhs.z - z * rhs.y;
	vertor.y = z * rhs.x - x * rhs.z;
	vertor.z = x * rhs.y - y * rhs.x;

	return vertor;
}

CVector3 CVector3::operator+=(const CVector3& rhs) 
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

CVector3 CVector3::operator-=(const CVector3& rhs) 
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

CVector3 CVector3::operator*=(const FLOAT scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector3 CVector3::operator/=(const FLOAT scalar)
{
	if(scalar == 0)
		return *this;

	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

void CVector3::Normalize(void)
{
	FLOAT f = 1.0f / sqrt(x * x + y * y + z * z);

	x *= f;
	y *= f;
	z *= f;
}

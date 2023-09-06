#include "stdafx.h"

CVector4::CVector4(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _w)
: x(_x)
, y(_y)
, z(_z)
, w(_w)
{
}

CVector4::~CVector4(void)
{}

CVector4::CVector4(CVector3 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = 1.0f;
}

CVector4 CVector4::operator-() const
{
	return CVector4(-x, -y, -z, -w);
}

CVector4 CVector4::operator+(const CVector4& rhs) const
{
	return CVector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); 
}

CVector4 CVector4::operator-(const CVector4& rhs) const
{
	return CVector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); 
}

CVector4 CVector4::operator*(const FLOAT scalar) const
{
	return CVector4(x * scalar, y * scalar, z * scalar, w * scalar); 
}

CVector4 CVector4::operator/(const FLOAT scalar) const
{
	return CVector4(x / scalar, y / scalar, z / scalar, w / scalar); 
}

CVector4 operator*(const FLOAT scalar, const CVector4& rhs)
{
	return CVector4(rhs.x * scalar, rhs.y * scalar, rhs.z * scalar, rhs.w * scalar);
}

CVector4 CVector4::operator*(const CMatrix4& rhs) const
{
	CVector4 vertor;
	vertor.x = x * rhs.m_f[0][0] + y * rhs.m_f[0][1] + z * rhs.m_f[0][2] + w * rhs.m_f[0][3];
	vertor.y = x * rhs.m_f[1][0] + y * rhs.m_f[1][1] + z * rhs.m_f[1][2] + w * rhs.m_f[1][3];
	vertor.z = x * rhs.m_f[2][0] + y * rhs.m_f[2][1] + z * rhs.m_f[2][2] + w * rhs.m_f[2][3];
	vertor.w = x * rhs.m_f[3][0] + y * rhs.m_f[3][1] + z * rhs.m_f[3][2] + w * rhs.m_f[3][3];

	return vertor;
}

FLOAT CVector4::operator*(const CVector4& rhs) const
{
	return (x * rhs.x + y * rhs.y + z * rhs.z);
}

CVector4 CVector4::operator^(const CVector4& rhs) const
{
	CVector4 vertor;
	vertor.x = y * rhs.z - z * rhs.y;
	vertor.y = z * rhs.x - x * rhs.z;
	vertor.z = x * rhs.y - y * rhs.x;

	return vertor;
}

BOOL CVector4::operator==(const CVector4& rhs) 
{
	return ( x == rhs.x && y == rhs.y && z == rhs.z );
}

CVector4 CVector4::operator+=(const CVector4& rhs) 
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

CVector4 CVector4::operator-=(const CVector4& rhs) 
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

CVector4 CVector4::operator*=(const FLOAT scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector4 CVector4::operator/=(const FLOAT scalar)
{
	if(scalar == 0)
		return *this;

	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

void CVector4::Normalize(void)
{
	FLOAT f = 1.0f / sqrt(x * x + y * y + z * z);

	x *= f;
	y *= f;
	z *= f;
}

void CVector4::PerspectiveDivide()
{
	w = 1 / w;

	x *= w;
	y *= w;
	z *= w;
}

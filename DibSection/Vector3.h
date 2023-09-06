#pragma once

class CVector3
{
public:
	FLOAT x;
	FLOAT y;
	FLOAT z;

	CVector3(FLOAT = 0, FLOAT = 0, FLOAT = 0);
	//CVector3(CPoint2 &);
	~CVector3();

	CVector3 operator-(void) const;

	CVector3 operator+(const CVector3&) const;
	CVector3 operator-(const CVector3&) const;

	CVector3 operator+=(const CVector3&);
	CVector3 operator-=(const CVector3&);

	CVector3 operator^(const CVector3&) const;
	FLOAT operator*(const CVector3&) const;

	CVector3 operator*(const FLOAT scalar) const;
	CVector3 operator/(const FLOAT scalar) const;
	CVector3 operator*=(const FLOAT scalar);
	CVector3 operator/=(const FLOAT scalar);

	//CVector3 operator*(const Matrix3& m) const;
	//CVector3 operator*(const Matrix4& m) const;

	void Normalize(void);
};
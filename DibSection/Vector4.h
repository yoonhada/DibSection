#pragma once

class CVector4
{
public:
	CVector4(FLOAT = 0, FLOAT = 0, FLOAT = 0, FLOAT = 1);
	CVector4(CVector3&);
	virtual ~CVector4(void);

	CVector4 operator-() const;
	CVector4 operator+(const CVector4&) const;
	CVector4 operator-(const CVector4&) const;
	CVector4 operator*(const FLOAT) const;
	CVector4 operator/(const FLOAT) const;
	friend CVector4 operator*(const FLOAT, const CVector4&);


	CVector4 operator*(const CMatrix4&) const;

	FLOAT operator*(const CVector4&) const;	
	CVector4 operator^(const CVector4&) const;

	BOOL operator==(const CVector4&);
	CVector4 operator+=(const CVector4&);
	CVector4 operator-=(const CVector4&);
	CVector4 operator*=(const FLOAT);
	CVector4 operator/=(const FLOAT);

	void Normalize(void);
	void PerspectiveDivide();

//private:
	FLOAT x, y, z, w;
};

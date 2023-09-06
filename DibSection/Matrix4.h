#pragma once

class CVector4;

class CMatrix4
{
public:
	CMatrix4(void);
	~CMatrix4(void);
	CMatrix4(FLOAT, FLOAT, FLOAT, FLOAT, 
			 FLOAT, FLOAT, FLOAT, FLOAT, 
			 FLOAT, FLOAT, FLOAT, FLOAT, 
			 FLOAT, FLOAT, FLOAT, FLOAT);

	//void operator+=(const CMatrix4 &);
	//void operator-=(const CMatrix4 &);
	//CMatrix4 operator+(const CMatrix4 &) const;
	//CMatrix4 operator-(const CMatrix4 &) const;
	void operator*=(const CMatrix4 &);
	void operator*=(const FLOAT );
	CMatrix4 operator*(const CMatrix4 &) const;
	CVector4 operator*(const CVector4 &) const;
	//CMatrix4 operator*(const FLOAT ) const;
	//friend CMatrix4 operator*(const FLOAT , const CMatrix4 &);
	void Identity();
	void Transpose();
	void Inverse();

	FLOAT m_f[4][4];
};

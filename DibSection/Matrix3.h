#pragma once

class CMatrix3
{
public:
	CMatrix3(void);
	~CMatrix3(void);
	CMatrix3(FLOAT, FLOAT, FLOAT, 
			 FLOAT, FLOAT, FLOAT, 
			 FLOAT, FLOAT, FLOAT);

	//void operator=(const CMatrix3 &);
	void operator+=(const CMatrix3 &);
	void operator-=(const CMatrix3 &);
	CMatrix3 operator+(const CMatrix3 &) const;
	CMatrix3 operator-(const CMatrix3 &) const;
	CMatrix3 operator*(const CMatrix3 &) const;
	CMatrix3 operator*(const FLOAT ) const;

	void operator*=(const CMatrix3 &) ;
	void operator*=(const FLOAT );
	friend CMatrix3 operator*(const FLOAT , const CMatrix3 &);

	void Identity();
	void Transpose();
	void Inverse();

	FLOAT m_f[3][3];
};

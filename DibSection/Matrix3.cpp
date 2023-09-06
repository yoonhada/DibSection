#include "stdafx.h"

CMatrix3::CMatrix3(void)
{
}

CMatrix3::~CMatrix3(void)
{
}

CMatrix3::CMatrix3(FLOAT f00, FLOAT f01, FLOAT f02, 
				   FLOAT f10, FLOAT f11, FLOAT f12, 
				   FLOAT f20, FLOAT f21, FLOAT f22)
{
	m_f[0][0] = f00;
	m_f[0][1] = f01;
	m_f[0][2] = f02;
	m_f[1][0] = f10;
	m_f[1][1] = f11;
	m_f[1][2] = f12;
	m_f[2][0] = f20;
	m_f[2][1] = f21;
	m_f[2][2] = f22;
}

void CMatrix3::operator+=(const CMatrix3 &matrix)
{
	m_f[0][0] += matrix.m_f[0][0];
	m_f[0][1] += matrix.m_f[0][1];
	m_f[0][2] += matrix.m_f[0][2];
	m_f[1][0] += matrix.m_f[1][0];
	m_f[1][1] += matrix.m_f[1][1];
	m_f[1][2] += matrix.m_f[1][2];
	m_f[2][0] += matrix.m_f[2][0];
	m_f[2][1] += matrix.m_f[2][1];
	m_f[2][2] += matrix.m_f[2][2];
}

void CMatrix3::operator-=(const CMatrix3 &matrix)
{
	m_f[0][0] -= matrix.m_f[0][0];
	m_f[0][1] -= matrix.m_f[0][1];
	m_f[0][2] -= matrix.m_f[0][2];
	m_f[1][0] -= matrix.m_f[1][0];
	m_f[1][1] -= matrix.m_f[1][1];
	m_f[1][2] -= matrix.m_f[1][2];
	m_f[2][0] -= matrix.m_f[2][0];
	m_f[2][1] -= matrix.m_f[2][1];
	m_f[2][2] -= matrix.m_f[2][2];
}

CMatrix3 CMatrix3::operator+(const CMatrix3 &matrix) const
{
	return CMatrix3( m_f[0][0] + matrix.m_f[0][0], m_f[0][1] + matrix.m_f[0][1], m_f[0][2] + matrix.m_f[0][2], 
					 m_f[1][0] + matrix.m_f[1][0], m_f[1][1] + matrix.m_f[1][1], m_f[1][2] + matrix.m_f[1][2], 
					 m_f[2][0] + matrix.m_f[2][0], m_f[2][1] + matrix.m_f[2][1], m_f[2][2] + matrix.m_f[2][2]);
}

CMatrix3 CMatrix3::operator-(const CMatrix3 &matrix) const
{
	return CMatrix3( m_f[0][0] - matrix.m_f[0][0], m_f[0][1] - matrix.m_f[0][1], m_f[0][2] - matrix.m_f[0][2], 
					 m_f[1][0] - matrix.m_f[1][0], m_f[1][1] - matrix.m_f[1][1], m_f[1][2] - matrix.m_f[1][2], 
					 m_f[2][0] - matrix.m_f[2][0], m_f[2][1] - matrix.m_f[2][1], m_f[2][2] - matrix.m_f[2][2]);
}

void CMatrix3::operator*=(const CMatrix3 &matrix) 
{
	CMatrix3 temp;

	temp.m_f[0][0] = m_f[0][0] * matrix.m_f[0][0] + m_f[0][1] * matrix.m_f[1][0] + m_f[0][2] * matrix.m_f[2][0];
	temp.m_f[0][1] = m_f[0][0] * matrix.m_f[0][1] + m_f[0][1] * matrix.m_f[1][1] + m_f[0][2] * matrix.m_f[2][1];
	temp.m_f[0][2] = m_f[0][0] * matrix.m_f[0][2] + m_f[0][1] * matrix.m_f[1][2] + m_f[0][2] * matrix.m_f[2][2];

	temp.m_f[1][0] = m_f[1][0] * matrix.m_f[0][0] + m_f[1][1] * matrix.m_f[1][0] + m_f[1][2] * matrix.m_f[2][0];
	temp.m_f[1][1] = m_f[1][0] * matrix.m_f[0][1] + m_f[1][1] * matrix.m_f[1][1] + m_f[1][2] * matrix.m_f[2][1];
	temp.m_f[1][2] = m_f[1][0] * matrix.m_f[0][2] + m_f[1][1] * matrix.m_f[1][2] + m_f[1][2] * matrix.m_f[2][2];

	temp.m_f[2][0] = m_f[2][0] * matrix.m_f[0][0] + m_f[2][1] * matrix.m_f[1][0] + m_f[2][2] * matrix.m_f[2][0];
	temp.m_f[2][1] = m_f[2][0] * matrix.m_f[0][1] + m_f[2][1] * matrix.m_f[1][1] + m_f[2][2] * matrix.m_f[2][1];
	temp.m_f[2][2] = m_f[2][0] * matrix.m_f[0][2] + m_f[2][1] * matrix.m_f[1][2] + m_f[2][2] * matrix.m_f[2][2];

	m_f[0][0] = temp.m_f[0][0];
	m_f[0][1] = temp.m_f[0][1];
	m_f[0][2] = temp.m_f[0][2];

	m_f[1][0] = temp.m_f[1][0];
	m_f[1][1] = temp.m_f[1][1];
	m_f[1][2] = temp.m_f[1][2];

	m_f[2][0] = temp.m_f[2][0];
	m_f[2][1] = temp.m_f[2][1];
	m_f[2][2] = temp.m_f[2][2];
}

CMatrix3 CMatrix3::operator*(const CMatrix3 &matrix) const
{
	CMatrix3 temp;

	temp.m_f[0][0] = m_f[0][0] * matrix.m_f[0][0] + m_f[0][1] * matrix.m_f[1][0] + m_f[0][2] * matrix.m_f[2][0];
	temp.m_f[0][1] = m_f[0][0] * matrix.m_f[0][1] + m_f[0][1] * matrix.m_f[1][1] + m_f[0][2] * matrix.m_f[2][1];
	temp.m_f[0][2] = m_f[0][0] * matrix.m_f[0][2] + m_f[0][1] * matrix.m_f[1][2] + m_f[0][2] * matrix.m_f[2][2];

	temp.m_f[1][0] = m_f[1][0] * matrix.m_f[0][0] + m_f[1][1] * matrix.m_f[1][0] + m_f[1][2] * matrix.m_f[2][0];
	temp.m_f[1][1] = m_f[1][0] * matrix.m_f[0][1] + m_f[1][1] * matrix.m_f[1][1] + m_f[1][2] * matrix.m_f[2][1];
	temp.m_f[1][2] = m_f[1][0] * matrix.m_f[0][2] + m_f[1][1] * matrix.m_f[1][2] + m_f[1][2] * matrix.m_f[2][2];

	temp.m_f[2][0] = m_f[2][0] * matrix.m_f[0][0] + m_f[2][1] * matrix.m_f[1][0] + m_f[2][2] * matrix.m_f[2][0];
	temp.m_f[2][1] = m_f[2][0] * matrix.m_f[0][1] + m_f[2][1] * matrix.m_f[1][1] + m_f[2][2] * matrix.m_f[2][1];
	temp.m_f[2][2] = m_f[2][0] * matrix.m_f[0][2] + m_f[2][1] * matrix.m_f[1][2] + m_f[2][2] * matrix.m_f[2][2];

	return temp;
}

void CMatrix3::operator*=(const FLOAT scalar)
{
	m_f[0][0] *= scalar;
	m_f[0][1] *= scalar;
	m_f[0][2] *= scalar;

	m_f[1][0] *= scalar;
	m_f[1][1] *= scalar;
	m_f[1][2] *= scalar;

	m_f[2][0] *= scalar;
	m_f[2][1] *= scalar;
	m_f[2][2] *= scalar;
}

CMatrix3 CMatrix3::operator*(const FLOAT scalar) const
{
	CMatrix3 temp;

	temp.m_f[0][0] = m_f[0][0] * scalar;
	temp.m_f[0][1] = m_f[0][1] * scalar;
	temp.m_f[0][2] = m_f[0][2] * scalar;

	temp.m_f[1][0] = m_f[1][0] * scalar;
	temp.m_f[1][1] = m_f[1][1] * scalar;
	temp.m_f[1][2] = m_f[1][2] * scalar;

	temp.m_f[2][0] = m_f[2][0] * scalar;
	temp.m_f[2][1] = m_f[2][1] * scalar;
	temp.m_f[2][2] = m_f[2][2] * scalar;

	return temp;
}

CMatrix3 operator*(const FLOAT scalar, const CMatrix3 &matrix)
{
	CMatrix3 temp;

	temp.m_f[0][0] = matrix.m_f[0][0] * scalar;
	temp.m_f[0][1] = matrix.m_f[0][1] * scalar;
	temp.m_f[0][2] = matrix.m_f[0][2] * scalar;

	temp.m_f[1][0] = matrix.m_f[1][0] * scalar;
	temp.m_f[1][1] = matrix.m_f[1][1] * scalar;
	temp.m_f[1][2] = matrix.m_f[1][2] * scalar;

	temp.m_f[2][0] = matrix.m_f[2][0] * scalar;
	temp.m_f[2][1] = matrix.m_f[2][1] * scalar;
	temp.m_f[2][2] = matrix.m_f[2][2] * scalar;

	return temp;
}

void CMatrix3::Identity()
{
	m_f[0][0] = 1.0f;
	m_f[0][1] = 0.0f;
	m_f[0][2] = 0.0f;

	m_f[1][0] = 0.0f;
	m_f[1][1] = 1.0f;
	m_f[1][2] = 0.0f;

	m_f[2][0] = 0.0f;
	m_f[2][1] = 0.0f;
	m_f[2][2] = 1.0f;
}

void CMatrix3::Transpose()
{
	FLOAT temp;

	temp  = m_f[1][0]; 
	m_f[1][0] = m_f[0][1];
	m_f[0][1] = temp;

	temp  = m_f[2][0]; 
	m_f[2][0] = m_f[0][2];
	m_f[0][2] = temp;

	temp  = m_f[1][2]; 
	m_f[1][2] = m_f[2][1];
	m_f[2][1] = temp;
}

void CMatrix3::Inverse()
{
	FLOAT Det = m_f[0][0] * (m_f[1][1] * m_f[2][2] - m_f[1][2] * m_f[2][1]) - 
				m_f[0][1] * (m_f[1][0] * m_f[2][2] - m_f[1][2] * m_f[2][0]) + 
				m_f[0][2] * (m_f[1][0] * m_f[2][1] - m_f[1][1] * m_f[2][0]);
	FLOAT InvDet = 1.0f / Det;

	CMatrix3 temp;

	temp.m_f[0][0] = (m_f[1][1] * m_f[2][2] - m_f[1][2] * m_f[2][1]) * InvDet; 
	temp.m_f[0][1] = (m_f[0][2] * m_f[2][1] - m_f[0][1] * m_f[2][2]) * InvDet; 
	temp.m_f[0][2] = (m_f[0][1] * m_f[1][2] - m_f[0][2] * m_f[1][1]) * InvDet; 

	temp.m_f[1][0] = (m_f[1][2] * m_f[2][0] - m_f[1][0] * m_f[2][2]) * InvDet; 
	temp.m_f[1][1] = (m_f[0][0] * m_f[2][2] - m_f[0][2] * m_f[2][0]) * InvDet; 
	temp.m_f[1][2] = (m_f[0][2] * m_f[1][0] - m_f[0][0] * m_f[1][2]) * InvDet; 

	temp.m_f[2][0] = (m_f[1][0] * m_f[2][1] - m_f[1][1] * m_f[2][0]) * InvDet; 
	temp.m_f[2][1] = (m_f[0][1] * m_f[2][0] - m_f[0][0] * m_f[2][1]) * InvDet; 
	temp.m_f[2][2] = (m_f[0][0] * m_f[1][1] - m_f[0][1] * m_f[1][0]) * InvDet;

	*this = temp; 
}
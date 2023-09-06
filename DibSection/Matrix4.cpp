#include "stdafx.h"

CMatrix4::CMatrix4()
{
	this->Identity();
}

CMatrix4::CMatrix4(FLOAT f00, FLOAT f01, FLOAT f02, FLOAT f03, 
				   FLOAT f10, FLOAT f11, FLOAT f12, FLOAT f13, 
				   FLOAT f20, FLOAT f21, FLOAT f22, FLOAT f23, 
				   FLOAT f30, FLOAT f31, FLOAT f32, FLOAT f33)
{
	m_f[0][0] = f00;	m_f[0][1] = f01;	m_f[0][2] = f02;	m_f[0][3] = f03;
	m_f[1][0] = f10;	m_f[1][1] = f11;	m_f[1][2] = f12;	m_f[1][3] = f13;
	m_f[2][0] = f20;	m_f[2][1] = f21;	m_f[2][2] = f22;	m_f[2][3] = f23;
	m_f[3][0] = f30;	m_f[3][1] = f31;	m_f[3][2] = f32;	m_f[3][3] = f33;
}

CMatrix4::~CMatrix4()
{
}

//void CMatrix4::operator+=(const CMatrix4 &matrix)
//{
//	m_f[0][0] += matrix.m_f[0][0];
//	m_f[0][1] += matrix.m_f[0][1];
//	m_f[0][2] += matrix.m_f[0][2];
//	m_f[0][3] += matrix.m_f[0][3];
//
//	m_f[1][0] += matrix.m_f[1][0];
//	m_f[1][1] += matrix.m_f[1][1];
//	m_f[1][2] += matrix.m_f[1][2];
//	m_f[1][3] += matrix.m_f[1][3];
//	
//	m_f[2][0] += matrix.m_f[2][0];
//	m_f[2][1] += matrix.m_f[2][1];
//	m_f[2][2] += matrix.m_f[2][2];
//	m_f[2][3] += matrix.m_f[2][3];
//	
//	m_f[3][0] += matrix.m_f[3][0];
//	m_f[3][1] += matrix.m_f[3][1];
//	m_f[3][2] += matrix.m_f[3][2];
//	m_f[3][3] += matrix.m_f[3][3];
//}

//void CMatrix4::operator-=(const CMatrix4 &matrix)
//{
//	m_f[0][0] -= matrix.m_f[0][0];
//	m_f[0][1] -= matrix.m_f[0][1];
//	m_f[0][2] -= matrix.m_f[0][2];
//	m_f[0][3] -= matrix.m_f[0][3];
//	
//	m_f[1][0] -= matrix.m_f[1][0];
//	m_f[1][1] -= matrix.m_f[1][1];
//	m_f[1][2] -= matrix.m_f[1][2];
//	m_f[1][3] -= matrix.m_f[1][3];
//	
//	m_f[2][0] -= matrix.m_f[2][0];
//	m_f[2][1] -= matrix.m_f[2][1];
//	m_f[2][2] -= matrix.m_f[2][2];
//	m_f[2][3] -= matrix.m_f[2][3];
//	
//	m_f[3][0] -= matrix.m_f[3][0];
//	m_f[3][1] -= matrix.m_f[3][1];
//	m_f[3][2] -= matrix.m_f[3][2];
//	m_f[3][3] -= matrix.m_f[3][3];
//}

//CMatrix4 CMatrix4::operator+(const CMatrix4 &matrix) const 
//{
//	return CMatrix4(m_f[0][0] + matrix.m_f[0][0], m_f[0][1] + matrix.m_f[0][1], m_f[0][2] + matrix.m_f[0][2], m_f[0][3] + matrix.m_f[0][3], 
//					m_f[1][0] + matrix.m_f[1][0], m_f[1][1] + matrix.m_f[1][1], m_f[1][2] + matrix.m_f[1][2], m_f[1][3] + matrix.m_f[1][3], 
//					m_f[2][0] + matrix.m_f[2][0], m_f[2][1] + matrix.m_f[2][1], m_f[2][2] + matrix.m_f[2][2], m_f[2][3] + matrix.m_f[2][3], 
//					m_f[3][0] + matrix.m_f[3][0], m_f[3][1] + matrix.m_f[3][1], m_f[3][2] + matrix.m_f[3][2], m_f[3][3] + matrix.m_f[3][3]);
//}
//
//CMatrix4 CMatrix4::operator-(const CMatrix4 &matrix) const
//{
//	return CMatrix4(m_f[0][0] - matrix.m_f[0][0], m_f[0][1] - matrix.m_f[0][1], m_f[0][2] - matrix.m_f[0][2], m_f[0][3] - matrix.m_f[0][3], 
//					m_f[1][0] - matrix.m_f[1][0], m_f[1][1] - matrix.m_f[1][1], m_f[1][2] - matrix.m_f[1][2], m_f[1][3] - matrix.m_f[1][3], 
//					m_f[2][0] - matrix.m_f[2][0], m_f[2][1] - matrix.m_f[2][1], m_f[2][2] - matrix.m_f[2][2], m_f[2][3] - matrix.m_f[2][3], 
//					m_f[3][0] - matrix.m_f[3][0], m_f[3][1] - matrix.m_f[3][1], m_f[3][2] - matrix.m_f[3][2], m_f[3][3] - matrix.m_f[3][3]);
//}
//
void CMatrix4::operator*=(const CMatrix4 &matrix)
{
	CMatrix4 m;

	m.m_f[0][0] = m_f[0][0] * matrix.m_f[0][0] + m_f[0][1] * matrix.m_f[1][0] + m_f[0][2] * matrix.m_f[2][0] + m_f[0][3] * matrix.m_f[3][0];
	m.m_f[0][1] = m_f[0][0] * matrix.m_f[0][1] + m_f[0][1] * matrix.m_f[1][1] + m_f[0][2] * matrix.m_f[2][1] + m_f[0][3] * matrix.m_f[3][1];
	m.m_f[0][2] = m_f[0][0] * matrix.m_f[0][2] + m_f[0][1] * matrix.m_f[1][2] + m_f[0][2] * matrix.m_f[2][2] + m_f[0][3] * matrix.m_f[3][2];
	m.m_f[0][3] = m_f[0][0] * matrix.m_f[0][3] + m_f[0][1] * matrix.m_f[1][3] + m_f[0][2] * matrix.m_f[2][3] + m_f[0][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[1][0] = m_f[1][0] * matrix.m_f[0][0] + m_f[1][1] * matrix.m_f[1][0] + m_f[1][2] * matrix.m_f[2][0] + m_f[1][3] * matrix.m_f[3][0];
	m.m_f[1][1] = m_f[1][0] * matrix.m_f[0][1] + m_f[1][1] * matrix.m_f[1][1] + m_f[1][2] * matrix.m_f[2][1] + m_f[1][3] * matrix.m_f[3][1];
	m.m_f[1][2] = m_f[1][0] * matrix.m_f[0][2] + m_f[1][1] * matrix.m_f[1][2] + m_f[1][2] * matrix.m_f[2][2] + m_f[1][3] * matrix.m_f[3][2];
	m.m_f[1][3] = m_f[1][0] * matrix.m_f[0][3] + m_f[1][1] * matrix.m_f[1][3] + m_f[1][2] * matrix.m_f[2][3] + m_f[1][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[2][0] = m_f[2][0] * matrix.m_f[0][0] + m_f[2][1] * matrix.m_f[1][0] + m_f[2][2] * matrix.m_f[2][0] + m_f[2][3] * matrix.m_f[3][0];
	m.m_f[2][1] = m_f[2][0] * matrix.m_f[0][1] + m_f[2][1] * matrix.m_f[1][1] + m_f[2][2] * matrix.m_f[2][1] + m_f[2][3] * matrix.m_f[3][1];
	m.m_f[2][2] = m_f[2][0] * matrix.m_f[0][2] + m_f[2][1] * matrix.m_f[1][2] + m_f[2][2] * matrix.m_f[2][2] + m_f[2][3] * matrix.m_f[3][2];
	m.m_f[2][3] = m_f[2][0] * matrix.m_f[0][3] + m_f[2][1] * matrix.m_f[1][3] + m_f[2][2] * matrix.m_f[2][3] + m_f[2][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[3][0] = m_f[3][0] * matrix.m_f[0][0] + m_f[3][1] * matrix.m_f[1][0] + m_f[3][2] * matrix.m_f[2][0] + m_f[3][3] * matrix.m_f[3][0];
	m.m_f[3][1] = m_f[3][0] * matrix.m_f[0][1] + m_f[3][1] * matrix.m_f[1][1] + m_f[3][2] * matrix.m_f[2][1] + m_f[3][3] * matrix.m_f[3][1];
	m.m_f[3][2] = m_f[3][0] * matrix.m_f[0][2] + m_f[3][1] * matrix.m_f[1][2] + m_f[3][2] * matrix.m_f[2][2] + m_f[3][3] * matrix.m_f[3][2];
	m.m_f[3][3] = m_f[3][0] * matrix.m_f[0][3] + m_f[3][1] * matrix.m_f[1][3] + m_f[3][2] * matrix.m_f[2][3] + m_f[3][3] * matrix.m_f[3][3];

	m_f[0][0] = m.m_f[0][0];
	m_f[0][1] = m.m_f[0][1];
	m_f[0][2] = m.m_f[0][2];
	m_f[0][3] = m.m_f[0][3];
										
	m_f[1][0] = m.m_f[1][0];
	m_f[1][1] = m.m_f[1][1];
	m_f[1][2] = m.m_f[1][2];
	m_f[1][3] = m.m_f[1][3];
										
	m_f[2][0] = m.m_f[2][0];
	m_f[2][1] = m.m_f[2][1];
	m_f[2][2] = m.m_f[2][2];
	m_f[2][3] = m.m_f[2][3];
										
	m_f[3][0] = m.m_f[3][0];
	m_f[3][1] = m.m_f[3][1];
	m_f[3][2] = m.m_f[3][2];
	m_f[3][3] = m.m_f[3][3];
}

CMatrix4 CMatrix4::operator*(const CMatrix4 &matrix) const 
{
	CMatrix4 m;

	m.m_f[0][0] = m_f[0][0] * matrix.m_f[0][0] + m_f[0][1] * matrix.m_f[1][0] + m_f[0][2] * matrix.m_f[2][0] + m_f[0][3] * matrix.m_f[3][0];
	m.m_f[0][1] = m_f[0][0] * matrix.m_f[0][1] + m_f[0][1] * matrix.m_f[1][1] + m_f[0][2] * matrix.m_f[2][1] + m_f[0][3] * matrix.m_f[3][1];
	m.m_f[0][2] = m_f[0][0] * matrix.m_f[0][2] + m_f[0][1] * matrix.m_f[1][2] + m_f[0][2] * matrix.m_f[2][2] + m_f[0][3] * matrix.m_f[3][2];
	m.m_f[0][3] = m_f[0][0] * matrix.m_f[0][3] + m_f[0][1] * matrix.m_f[1][3] + m_f[0][2] * matrix.m_f[2][3] + m_f[0][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[1][0] = m_f[1][0] * matrix.m_f[0][0] + m_f[1][1] * matrix.m_f[1][0] + m_f[1][2] * matrix.m_f[2][0] + m_f[1][3] * matrix.m_f[3][0];
	m.m_f[1][1] = m_f[1][0] * matrix.m_f[0][1] + m_f[1][1] * matrix.m_f[1][1] + m_f[1][2] * matrix.m_f[2][1] + m_f[1][3] * matrix.m_f[3][1];
	m.m_f[1][2] = m_f[1][0] * matrix.m_f[0][2] + m_f[1][1] * matrix.m_f[1][2] + m_f[1][2] * matrix.m_f[2][2] + m_f[1][3] * matrix.m_f[3][2];
	m.m_f[1][3] = m_f[1][0] * matrix.m_f[0][3] + m_f[1][1] * matrix.m_f[1][3] + m_f[1][2] * matrix.m_f[2][3] + m_f[1][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[2][0] = m_f[2][0] * matrix.m_f[0][0] + m_f[2][1] * matrix.m_f[1][0] + m_f[2][2] * matrix.m_f[2][0] + m_f[2][3] * matrix.m_f[3][0];
	m.m_f[2][1] = m_f[2][0] * matrix.m_f[0][1] + m_f[2][1] * matrix.m_f[1][1] + m_f[2][2] * matrix.m_f[2][1] + m_f[2][3] * matrix.m_f[3][1];
	m.m_f[2][2] = m_f[2][0] * matrix.m_f[0][2] + m_f[2][1] * matrix.m_f[1][2] + m_f[2][2] * matrix.m_f[2][2] + m_f[2][3] * matrix.m_f[3][2];
	m.m_f[2][3] = m_f[2][0] * matrix.m_f[0][3] + m_f[2][1] * matrix.m_f[1][3] + m_f[2][2] * matrix.m_f[2][3] + m_f[2][3] * matrix.m_f[3][3];
																										  								 	
	m.m_f[3][0] = m_f[3][0] * matrix.m_f[0][0] + m_f[3][1] * matrix.m_f[1][0] + m_f[3][2] * matrix.m_f[2][0] + m_f[3][3] * matrix.m_f[3][0];
	m.m_f[3][1] = m_f[3][0] * matrix.m_f[0][1] + m_f[3][1] * matrix.m_f[1][1] + m_f[3][2] * matrix.m_f[2][1] + m_f[3][3] * matrix.m_f[3][1];
	m.m_f[3][2] = m_f[3][0] * matrix.m_f[0][2] + m_f[3][1] * matrix.m_f[1][2] + m_f[3][2] * matrix.m_f[2][2] + m_f[3][3] * matrix.m_f[3][2];
	m.m_f[3][3] = m_f[3][0] * matrix.m_f[0][3] + m_f[3][1] * matrix.m_f[1][3] + m_f[3][2] * matrix.m_f[2][3] + m_f[3][3] * matrix.m_f[3][3];

	return m;
}

CVector4 CMatrix4::operator*(const CVector4 &vector) const 
{
	CVector4 vectorRet;

	vectorRet.x = vector.x * m_f[0][0] + vector.y * m_f[0][1] + vector.z * m_f[0][2] + vector.w * m_f[0][3]; 
	vectorRet.y = vector.x * m_f[1][0] + vector.y * m_f[1][1] + vector.z * m_f[1][2] + vector.w * m_f[1][3]; 
	vectorRet.z = vector.x * m_f[2][0] + vector.y * m_f[2][1] + vector.z * m_f[2][2] + vector.w * m_f[2][3]; 
	vectorRet.w = vector.x * m_f[3][0] + vector.y * m_f[3][1] + vector.z * m_f[3][2] + vector.w * m_f[3][3];

	return vectorRet; 
}

void CMatrix4::operator*=(const FLOAT fScalar)
{
	m_f[0][0] *= fScalar;
	m_f[0][1] *= fScalar; 
	m_f[0][2] *= fScalar;
	m_f[0][3] *= fScalar;
			
	m_f[1][0] *= fScalar;
	m_f[1][1] *= fScalar;
	m_f[1][2] *= fScalar;
	m_f[1][3] *= fScalar;
			
	m_f[2][0] *= fScalar;
	m_f[2][1] *= fScalar;
	m_f[2][2] *= fScalar;
	m_f[2][3] *= fScalar;
			
	m_f[3][0] *= fScalar;
	m_f[3][1] *= fScalar;
	m_f[3][2] *= fScalar;
	m_f[3][3] *= fScalar;
}

//CMatrix4 CMatrix4::operator*(const FLOAT fScalar) const 
//{
//	CMatrix4 m;
//
//	m.m_f[0][0] = m_f[0][0] * fScalar;
//	m.m_f[0][1] = m_f[0][1] * fScalar; 
//	m.m_f[0][2] = m_f[0][2] * fScalar;
//	m.m_f[0][3] = m_f[0][3] * fScalar;
//				  			 
//	m.m_f[1][0] = m_f[1][0] * fScalar;
//	m.m_f[1][1] = m_f[1][1] * fScalar;
//	m.m_f[1][2] = m_f[1][2] * fScalar;
//	m.m_f[1][3] = m_f[1][3] * fScalar;
//				  			 
//	m.m_f[2][0] = m_f[2][0] * fScalar;
//	m.m_f[2][1] = m_f[2][1] * fScalar;
//	m.m_f[2][2] = m_f[2][2] * fScalar;
//	m.m_f[2][3] = m_f[2][3] * fScalar;
//				  			 
//	m.m_f[3][0] = m_f[3][0] * fScalar;
//	m.m_f[3][1] = m_f[3][1] * fScalar;
//	m.m_f[3][2] = m_f[3][2] * fScalar;
//	m.m_f[3][3] = m_f[3][3] * fScalar;
//
//	return m;
//}
//
//CMatrix4 operator*(const FLOAT fScalar, const CMatrix4 &matrix)
//{
//	CMatrix4 m;
//	m.m_f[0][0] = matrix.m_f[0][0] * fScalar;
//	m.m_f[0][1] = matrix.m_f[0][1] * fScalar; 
//	m.m_f[0][2] = matrix.m_f[0][2] * fScalar;
//	m.m_f[0][3] = matrix.m_f[0][3] * fScalar;
//				  					 
//	m.m_f[1][0] = matrix.m_f[1][0] * fScalar;
//	m.m_f[1][1] = matrix.m_f[1][1] * fScalar;
//	m.m_f[1][2] = matrix.m_f[1][2] * fScalar;
//	m.m_f[1][3] = matrix.m_f[1][3] * fScalar;
//				  					 
//	m.m_f[2][0] = matrix.m_f[2][0] * fScalar;
//	m.m_f[2][1] = matrix.m_f[2][1] * fScalar;
//	m.m_f[2][2] = matrix.m_f[2][2] * fScalar;
//	m.m_f[2][3] = matrix.m_f[2][3] * fScalar;
//				  					 
//	m.m_f[3][0] = matrix.m_f[3][0] * fScalar;
//	m.m_f[3][1] = matrix.m_f[3][1] * fScalar;
//	m.m_f[3][2] = matrix.m_f[3][2] * fScalar;
//	m.m_f[3][3] = matrix.m_f[3][3] * fScalar;
//
//	return m;
//}

void CMatrix4::Identity()
{
	m_f[0][0] = 1.0f;
	m_f[0][1] = 0.0f;
	m_f[0][2] = 0.0f;
	m_f[0][3] = 0.0f;
				
	m_f[1][0] = 0.0f;
	m_f[1][1] = 1.0f;
	m_f[1][2] = 0.0f;
	m_f[1][3] = 0.0f;
				
	m_f[2][0] = 0.0f;
	m_f[2][1] = 0.0f;
	m_f[2][2] = 1.0f;
	m_f[2][3] = 0.0f;
				
	m_f[3][0] = 0.0f;
	m_f[3][1] = 0.0f;
	m_f[3][2] = 0.0f;
	m_f[3][3] = 1.0f;
};

void CMatrix4::Transpose()
{
	FLOAT temp;
	
	temp = m_f[0][0]; 
	m_f[0][0] = m_f[0][0];
	m_f[0][0] = temp;

	temp = m_f[2][0]; 
	m_f[2][0] = m_f[0][2];
	m_f[0][2] = temp;

	temp = m_f[0][2]; 
	m_f[0][2] = m_f[2][0];
	m_f[2][0] = temp;

	temp = m_f[3][0]; 
	m_f[3][0] = m_f[0][3];
	m_f[0][3] = temp;

	temp = m_f[2][3]; 
	m_f[2][3] = m_f[3][2];
	m_f[3][2] = temp;

	temp = m_f[0][3]; 
	m_f[0][3] = m_f[3][0];
	m_f[3][0] = temp;
};

void CMatrix4::Inverse()
{
};
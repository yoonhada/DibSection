#include "stdafx.h"

CTrans::CTrans(int nWidth, int nHeight)
: m_nWidth(nWidth)
, m_nHeight(nHeight)
{
	m_nRotate[0] = m_nRotate[1] = m_nRotate[2] = 0;
	m_vertorCamera = CVector4(0, 0, 100, 0);
	m_vertorTarget = CVector4(0, 0, 0, 0);
	m_fZn = m_vertorCamera.z - 10;
	m_fZf = m_vertorCamera.z - 1000;
}

CTrans::~CTrans(void)
{
}

void CTrans::Clear()
{
	m_vertorCamera = CVector4(0, 0, 100, 0);
	m_vertorTarget = CVector4(0, 0, 0, 0);
	m_fZn = m_vertorCamera.z - 10;
	m_fZf = m_vertorCamera.z - 1000;
}

void CTrans::TransModel2World(CNode* pNode, CMatrix4 & matrix)
{
	float fCosX = cos( pNode->m_nRotate[AXISX] * RADIAN );
	float fCosY = cos( pNode->m_nRotate[AXISY] * RADIAN );
	float fCosZ = cos( pNode->m_nRotate[AXISZ] * RADIAN );
	float fSinX = sin( pNode->m_nRotate[AXISX] * RADIAN );
	float fSinY = sin( pNode->m_nRotate[AXISY] * RADIAN );
	float fSinZ = sin( pNode->m_nRotate[AXISZ] * RADIAN );

	CMatrix4 matrixS(
		pNode->m_fScale[AXISX], 0, 0, 0, 
		0, pNode->m_fScale[AXISY], 0, 0, 
		0, 0, pNode->m_fScale[AXISZ], 0, 
		0, 0, 0, 1);
	CMatrix4 matrixRx(
		1, 0, 0, 0, 
		0, fCosX, -fSinX, 0, 
		0, fSinX, fCosX, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixRy(
		fCosY, 0, fSinY, 0, 
		0, 1, 0, 0, 
		-fSinY, 0, fCosY, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixRz(
		fCosZ, -fSinZ, 0, 0, 
		fSinZ, fCosZ, 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixT(
		1, 0, 0, pNode->m_fTrans[AXISX], 
		0, 1, 0, pNode->m_fTrans[AXISY], 
		0, 0, 1, pNode->m_fTrans[AXISZ], 
		0, 0, 0, 1);

	matrix = matrixT * matrixRz * matrixRy * matrixRx * matrixS;
}

void CTrans::TransWorld2View(int nType, CMatrix4& matrix)
{
	if( 0 == nType )
		EulerAngel( matrix );
	else 
		LockAt( matrix );
}

void CTrans::EulerAngel( CMatrix4 &matrix )
{
	float fCosX = cos(m_nRotate[AXISX] * RADIAN);
	float fCosY = cos(m_nRotate[AXISY] * RADIAN);
	float fCosZ = cos(m_nRotate[AXISZ] * RADIAN);
	float fSinX = sin(m_nRotate[AXISX] * RADIAN);
	float fSinY = sin(m_nRotate[AXISY] * RADIAN);
	float fSinZ = sin(m_nRotate[AXISZ] * RADIAN);

	CMatrix4 matrixRx(
		1, 0, 0, 0, 
		0, fCosX, fSinX, 0, 
		0, -fSinX, fCosX, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixRy(
		fCosY, 0, -fSinY, 0, 
		0, 1, 0, 0, 
		fSinY, 0, fCosY, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixRz(
		fCosZ, fSinZ, 0, 0, 
		-fSinZ, fCosZ, 0, 0, 
		0, 0, 1, 0, 
		0, 0, 0, 1);
	CMatrix4 matrixT(
		1, 0, 0, -m_vertorCamera.x, 
		0, 1, 0, -m_vertorCamera.y, 
		0, 0, 1, -m_vertorCamera.z, 
		0, 0, 0, 1);

	matrix = matrixRx * matrixRy * matrixRz * matrixT;
}

void CTrans::LockAt( CMatrix4 &matrix )
{
	CVector4 vertorDir = m_vertorTarget - m_vertorCamera;
	CVector4 vertorNDir = vertorDir;
	vertorNDir.Normalize();

	CVector4 vertorUp = CVector4(0, 1, 0, 0);
	vertorUp = vertorUp - (vertorUp * vertorNDir) * vertorNDir;
	CVector4 vertorSide = vertorDir^vertorUp;
	CVector4 vertorNSide = vertorSide;
	vertorNSide.Normalize();

	CVector4 vertorNUp = vertorSide^vertorDir;
	vertorNUp.Normalize();

	matrix = CMatrix4(
		vertorNSide.x, vertorNUp.x, vertorNDir.x, -m_vertorCamera.x, 
		vertorNSide.y, vertorNUp.y, vertorNDir.y, -m_vertorCamera.y, 
		vertorNSide.z, vertorNUp.z, vertorNDir.z, -m_vertorCamera.z, 
		0.0f,			   0.0f,			0.0f,			  1.0f);
}

void CTrans::TransView2Projection( CMatrix4& matrix )
{
	float d = m_vertorCamera.z - m_fZn;
	float a = (1.0f * m_nWidth) / (1.0f * m_nHeight);

	matrix.m_f[0][0] = d / a;
	matrix.m_f[1][1] = d;
	matrix.m_f[2][2] = (m_fZn + m_fZf) / (m_fZn - m_fZf);
	matrix.m_f[2][3] = (2.0f * m_fZn * m_fZf) / (m_fZn - m_fZf);
	matrix.m_f[3][2] = -1;
	matrix.m_f[3][3] = 0;
}

void CTrans::TransProjection2Ndc(CMatrix4& matrix, CMatrix4& matrixT)
{
	float fw = 1 / matrix.m_f[3][3];
	matrixT *= fw;
}

void CTrans::TransNdc2Screen( CMatrix4& matrix )
{
	float fw = static_cast<float>( m_nWidth ) / 2;
	float fh = static_cast<float>( m_nHeight ) / 2;

	matrix.m_f[0][0] = fw;
	matrix.m_f[0][3] = fw;
	matrix.m_f[1][1] = -fh;
	matrix.m_f[1][3] = fh;
	matrix.m_f[2][2] = 0.5f;
	matrix.m_f[2][3] = 0.5f;
}
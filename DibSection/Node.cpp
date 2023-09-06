#include "stdafx.h"

CNode::CNode() 
: m_pVertexList(0)
, m_pCulling(0)
, m_pTransformedList(0)
, m_pIndexList(0)
, _pNext(0)
{
	m_fScale[AXISX] = m_fScale[AXISY] = m_fScale[AXISZ] = 1.0f;
	m_nRotate[AXISX] = m_nRotate[AXISY] = m_nRotate[AXISZ] = 0;
	m_fTrans[AXISX] = m_fTrans[AXISY] = m_fTrans[AXISZ] = 0.0f;
}

CNode::~CNode()
{
	if(m_pCulling)			delete [] m_pCulling;
	if(m_pVertexList)		delete [] m_pVertexList;
	if(m_pTransformedList)	delete [] m_pTransformedList;
	if(m_pIndexList)		delete [] m_pIndexList;	
};

void CNode::Curring(int nType, const CMatrix4 &matrix, const CTrans * pTrans, BOOL bType)
{
	for(int i = 0; i < m_nVertex; ++i){
		m_pTransformedList[i] = m_pVertexList[i];
		m_pTransformedList[i].pos = matrix * m_pTransformedList[i].pos;
	}

	CVector4 vector1, vector2, vector3; 
	CVector4 vectorCross;
	
	if( bType )
	{
		for(int i = 0; i < m_nIndex; i++)
		{	
			vector1 = (m_pTransformedList[m_pIndexList[i * 3 + 0]]).pos;
			vector2 = (m_pTransformedList[m_pIndexList[i * 3 + 1]]).pos;
			vector3 = (m_pTransformedList[m_pIndexList[i * 3 + 2]]).pos;

			vectorCross = (vector2 - vector1) ^ (vector3 - vector1);

			if ( vectorCross.z <= 0.0f )
				m_pCulling[i] = TRUE;
			else
				m_pCulling[i] = FALSE;

		}	
	}
	else
	{
		for(int i = 0; i < m_nIndex; i++)
			m_pCulling[i] = FALSE;
	}
}

void CNode::Project(const CMatrix4 &matrix)
{
	CVector4 vector1, vector2, vector3; 

	for(int i = 0; i < m_nVertex; ++i){
		m_pTransformedList[i].pos = matrix * m_pTransformedList[i].pos;
	}

	//for(int i = 0; i < m_nIndex; i++){
	//	vector1 = (m_pTransformedList[m_pIndexList[i * 3 + 0]]).pos;
	//	vector2 = (m_pTransformedList[m_pIndexList[i * 3 + 1]]).pos;
	//	vector3 = (m_pTransformedList[m_pIndexList[i * 3 + 2]]).pos;


	//	//if(vector1.x < -1 && vector2.x < -1 && vector3.x < -1)
	//	//	m_pCulling[i] = true;

	//	//if(vector1.z > 1 && vector2.z > 1 && vector3.z > 1)
	//	//	m_pCulling[i] = true;
	//	//if(vector1.z < 0 && vector2.z < 0 && vector3.z < 0)
	//	//	m_pCulling[i] = true;
	//}
}

void CNode::Screen(int nType, const CMatrix4 &matrix)
{
	for(int i = 0; i < m_nVertex; ++i){
		//if(nType >= PROJECT){
		//	//m_pTransformedList[i].pos = matrix * m_pTransformedList[i].pos;
		//	m_pTransformedList[i].pos.x = (matrix.m_f[0][3]) + m_pTransformedList[i].pos.x * (matrix.m_f[0][0]);
		//	m_pTransformedList[i].pos.y = (matrix.m_f[1][3]) - m_pTransformedList[i].pos.y * (matrix.m_f[1][1]);

		//}else{
			m_pTransformedList[i].pos.x += (matrix.m_f[0][3]);
			m_pTransformedList[i].pos.y = (matrix.m_f[1][3]) - m_pTransformedList[i].pos.y ;
		//}
	}
}

void CNode::SetTrans(int nAxis, int nValue)	
{
	m_fTrans[nAxis] += nValue; 
}

void CNode::SetRotate(int nAxis, int nValue)	
{
	m_nRotate[nAxis] = (m_nRotate[nAxis] + nValue) % 360; 
}

void CNode::SetScale(int nAxis, float fValue)	
{ 
	if(m_fScale[nAxis] + fValue <= 0)		
		return; 
	m_fScale[nAxis] += fValue; 
}
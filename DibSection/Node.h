#pragma once

class CNode
{
public:	
	INT m_nVertex;
	BOOL * m_pCulling;
	CVertex * m_pVertexList;
	CVertex * m_pTransformedList;

	INT m_nIndex;
	INT * m_pIndexList;

	INT m_nRotate[3];
	FLOAT m_fTrans[3];
	FLOAT m_fScale[3];

	CNode * _pNext;

public:	
	CNode();
	virtual ~CNode();

	void Curring(int, const CMatrix4 &, const CTrans*, BOOL = TRUE);
	void Project(const CMatrix4 &);
	void Screen(INT, const CMatrix4 &);
	void SetTrans(INT, INT);
	void SetRotate(INT, INT);
	void SetScale(INT, FLOAT);
};
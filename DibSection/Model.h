#pragma once
#include "Vertor4.h"
enum _AXIS{AXISX, AXISY, AXISZ};

class Model
{
public:	
	Model() 
		: m_pVertexList(0)
		, m_pTransformedList(0)
		, m_pColorList(0)
		, m_pIndexList(0)
		, _pNext(0)
	{
		m_fScale[AXISX] = m_fScale[AXISY] = m_fScale[AXISZ] = 1.0f;
		m_nRotate[AXISX] = m_nRotate[AXISY] = m_nRotate[AXISZ] = 0;
		m_fTrans[AXISX] = m_fTrans[AXISY] = m_fTrans[AXISZ] = 0.0f;
	}
	~Model(){
		if(m_pVertexList){
		delete [] m_pVertexList;
		delete [] m_pTransformedList;
		delete [] m_pColorList;
		delete [] m_pIndexList;
		}
	};
	//void TransMatrix(CMatrix4& matrix);
	void Trans(const CMatrix4&);

	int m_nVertex;
	float m_fTrans[3];
	int m_nRotate[3];	
	float m_fScale[3];
	void SetTrans(int nAxis, float fValue)
	{
		m_fTrans[nAxis] += fValue;
	}
	void SetRotate(int nAxis, int nValue)
	{
		m_nRotate[nAxis] = (m_nRotate[nAxis] + nValue) % 360;
	}
	void SetScale(int nAxis, float fValue)
	{
		if(m_fScale[nAxis] + fValue <= 0)		return;
		m_fScale[nAxis] += fValue;
	}

	int m_nIndex;
	int * m_pIndexList;
	COLORREF * m_pColorList;

	CVertor4 * m_pVertexList;
	CVertor4 * m_pTransformedList;

	Model * _pNext;
};

class CModel
{
private:
	Model * m_pHead;
	Model * m_pCurr;
	Model * m_pTail;

public:
	CModel(void);
	virtual ~CModel(void);

	Model * GetHead()	{ return m_pHead; }
	Model * GetCurr()	{ return m_pCurr; }
	Model * MoveHead();
	Model * MoveNext();

	// List
	void InsertHead(Model*);
	void RemoveHead();
	
	// Member
	void Pyramid(float=0, float=0, float=0);
	void Diamond(float=0, float=0, float=0);
};
#include "stdafx.h"
#include "Model.h"

CModel::CModel(void)
{
	m_pHead = m_pCurr = m_pTail = 0;

	Pyramid();
	Diamond(0.0f, 0.0f, 200.0f);
	Diamond(-173.205f, 0.0f,-100.0f);
	Diamond(173.205f, 0.0f,-100.0f);
}

CModel::~CModel(void)
{
	while(GetHead())
		RemoveHead();
}

void Model::Trans(const CMatrix4 &matrix)
{
	for(int i = 0; i < m_nVertex; ++i){
		m_pTransformedList[i] = m_pVertexList[i] * matrix;
	}
}

void CModel::Pyramid(float fTx, float fTy, float fTz)
{
	Model * pModel = new Model;

	enum {O, X, Y, Z, T, M, B, U, END};

	pModel->m_nVertex = END;
	pModel->m_pVertexList = new CVertor4[END];
	pModel->m_pTransformedList = new CVertor4[END];

	pModel->m_pVertexList[O] = CVertor4(     0.0f,   0.0f,   0.0f);
	pModel->m_pVertexList[X] = CVertor4(   100.0f,   0.0f,   0.0f);
	pModel->m_pVertexList[Y] = CVertor4(     0.0f, 100.0f,   0.0f);
	pModel->m_pVertexList[Z] = CVertor4(     0.0f,   0.0f, 100.0f);
	pModel->m_pVertexList[T] = CVertor4(     0.0f,   0.0f, 200.0f);
	pModel->m_pVertexList[M] = CVertor4(-173.205f,   0.0f,-100.0f);	// 300.0f * 0.577350269f;
	pModel->m_pVertexList[B] = CVertor4( 173.205f,   0.0f,-100.0f);	// 300.0f * 0.577350269f;
	pModel->m_pVertexList[U] = CVertor4(     0.0f, 200.0f,   0.0f);

	pModel->m_fTrans[AXISX] = fTx;
	pModel->m_fTrans[AXISY] = fTy;
	pModel->m_fTrans[AXISZ] = fTz;

	pModel->m_nIndex = 7;
	pModel->m_pColorList = new COLORREF[7];
	pModel->m_pIndexList = new int[pModel->m_nIndex * 3];

	int arrTmp[21] = {
		O, X, O,
		O, Y, O,
		O, Z, O,
		T, M, B,
		U, T, M,
		U, M, B,
		U, B, T
	};

	for(int i = 0; i < pModel->m_nIndex * 3; ++i){
		pModel->m_pIndexList[i] = arrTmp[i];
	}

	pModel->m_pColorList[0] = RGB(255, 0, 0);
	pModel->m_pColorList[1] = RGB(0, 255, 0);
	pModel->m_pColorList[2] = RGB(0, 0, 255);
	for(int i = 3; i < 7; ++i)
		pModel->m_pColorList[i] = RGB(rand()%255, rand()%255, rand()%255);

	InsertHead(pModel);
}

void CModel::Diamond(float fTx, float fTy, float fTz)
{
	Model * pModel = new Model;

	enum {O, X, Y, Z, U, UC0, UC1, UC2, UC3, UC4, UC5, UC6, UC7, UUC, END};

	pModel->m_nVertex = END;
	pModel->m_pVertexList = new CVertor4[END];
	pModel->m_pTransformedList = new CVertor4[END];

	pModel->m_pVertexList[O]   = CVertor4(  0.0f,   0.0f,   0.0f);
	pModel->m_pVertexList[X]   = CVertor4( 20.0f,   0.0f,   0.0f);
	pModel->m_pVertexList[Y]   = CVertor4(  0.0f,  20.0f,   0.0f);
	pModel->m_pVertexList[Z]   = CVertor4(  0.0f,   0.0f,  20.0f);
	pModel->m_pVertexList[U]   = CVertor4( -35.4f,   0.0f,  0.0f);
	pModel->m_pVertexList[UC0] = CVertor4(   0.0f,   0.0f, 50.0f);
	pModel->m_pVertexList[UC1] = CVertor4(   0.0f,  35.4f, 35.4f);
	pModel->m_pVertexList[UC2] = CVertor4(   0.0f,  50.0f,  0.0f);
	pModel->m_pVertexList[UC3] = CVertor4(   0.0f,  35.4f,-35.4f);
	pModel->m_pVertexList[UC4] = CVertor4(   0.0f,   0.0f,-50.0f);
	pModel->m_pVertexList[UC5] = CVertor4(   0.0f, -35.4f,-35.4f);
	pModel->m_pVertexList[UC6] = CVertor4(   0.0f, -50.0f,  0.0f);
	pModel->m_pVertexList[UC7] = CVertor4(   0.0f, -35.4f, 35.4f);
	pModel->m_pVertexList[UUC] = CVertor4(  35.4f,   0.0f,  0.0f);

	pModel->m_fTrans[AXISX] = fTx;
	pModel->m_fTrans[AXISY] = fTy;
	pModel->m_fTrans[AXISZ] = fTz;

	pModel->m_nIndex = 19;
	pModel->m_pColorList = new COLORREF[19];
	pModel->m_pIndexList = new int[pModel->m_nIndex * 3];
	int arrTmp[57] = {  
		O, X, O,		// 0
		O, Y, O,		// 1
		O, Z, O,		// 2
		U, UC0, UC1,	// 0
		U, UC1, UC2,	// 1
		U, UC2, UC3,	// 2
		U, UC3, UC4,	// 3
		U, UC4, UC5,	// 4
		U, UC5, UC6,	// 5
		U, UC6, UC7,	// 6
		U, UC7, UC0,	// 7
		UUC, UC0, UC1,	// 8
		UUC, UC1, UC2,	// 9
		UUC, UC2, UC3,	// 0
		UUC, UC3, UC4,	// 1
		UUC, UC4, UC5,	// 2
		UUC, UC5, UC6,	// 3
		UUC, UC6, UC7,	// 4
		UUC, UC7, UC0	// 5
	};

	for(int i = 0; i < pModel->m_nIndex * 3; ++i){
		pModel->m_pIndexList[i] = arrTmp[i];
	}

	pModel->m_pColorList[0] = RGB(255, 0, 0);
	pModel->m_pColorList[1] = RGB(0, 255, 0);
	pModel->m_pColorList[2] = RGB(0, 0, 255);
	for(int i = 3; i < 19; ++i)
		pModel->m_pColorList[i] = RGB(rand()%255, rand()%255, rand()%255);

	InsertHead(pModel);
}

Model * CModel::MoveHead()
{
	m_pCurr = m_pHead; 

	return m_pCurr;
}

Model * CModel::MoveNext()	
{
	if(m_pCurr != 0)
		m_pCurr = m_pCurr->_pNext;	

	return m_pCurr; 
}

void CModel::InsertHead(Model * pModel)
{
	if(m_pHead == 0){
		m_pHead = pModel;
		m_pTail = pModel;		
	}else{
		pModel->_pNext = m_pHead;
		m_pHead = pModel;
	}

	m_pCurr = m_pHead;
}

void CModel::RemoveHead()
{
	if(m_pHead != 0){
		m_pCurr = m_pHead;
		m_pHead = m_pHead->_pNext;

		delete m_pCurr;
	}
}

#include "stdafx.h"

CModelList::CModelList(void)
{
	m_listNode.clear();
	m_nTempVertex = m_nTempIndex = 0;
}

CModelList::~CModelList(void)
{
	Clear();
}

void CModelList::Clear()
{
	std::list<CNode *>::iterator it;
	for (it = m_listNode.begin(); it != m_listNode.end();)
	{
		delete *it;
		it = m_listNode.erase( it );
	}

	m_listNode.clear();
}

void CModelList::Insert( CNode * pNode )
{
	m_listNode.push_front( pNode );
	it = m_listNode.begin();
}

void CModelList::Remove()
{
	if ( m_listNode.empty() )
		return;

	delete *it;
	m_listNode.remove( *it );

	it = m_listNode.begin();
}

CNode* CModelList::GetHead()
{
	if ( m_listNode.empty() )
	{
		return NULL;
	}

	it = m_listNode.begin();
	return *it;
}

CNode* CModelList::GetCurr()
{
	if ( m_listNode.empty())
	{
		return NULL;
	}

	return *it;
}

CNode* CModelList::GetNext()
{
	if ( m_listNode.empty())
	{
		return NULL;
	}

	it++;

	if ( it == m_listNode.end() )
	{
		it = m_listNode.begin();
		
		return NULL;
	}

	return *it;
}

CNode* CModelList::MoveHead()
{
	if ( m_listNode.empty())
	{
		return NULL;
	}

	itRutin = m_listNode.begin();
	return *itRutin;
}

CNode* CModelList::MoveNext()
{
	itRutin++;
	if ( itRutin == m_listNode.end() )
	{
		itRutin = m_listNode.begin();

		return NULL;
	}

	return *itRutin;
}

void CModelList::LoadModel(int nModelNo, float fRadius, int nLatitude, int nLongitude, int nRecur, bool bRand)
{
	CNode * pNode = new CNode;
	
	switch( nModelNo )
	{
	case HEXAGON:
		this->Hexagon( pNode, fRadius );
		break;
	case PYRAMID:
		this->Pyramid( pNode, fRadius );
		break;
	case DIAMOND:
		this->Diamond( pNode, fRadius );
		break;
	case GLOBE:
		this->GlobeSphere( pNode, fRadius, nLatitude, nLongitude);
		break;
	case GEOSPHERE:
		this->GeoSphere( pNode, fRadius, nRecur);
		break;
	default:
		return;
	}

	if(bRand == false){
		pNode->m_fTrans[0] = (float)(rand() % 600 - 300);
		pNode->m_fTrans[1] = (float)(rand() % 600 - 300);
		pNode->m_fTrans[2] = (float)(rand() % 600 - 300);
		pNode->m_fScale[0] = pNode->m_fScale[1] = pNode->m_fScale[2] = (float)(rand() % 10 * 0.1 + 0.2);
		pNode->m_nRotate[0] = rand() % 360;
		pNode->m_nRotate[1] = rand() % 360;
		pNode->m_nRotate[2] = rand() % 360;
	}

	Insert( pNode );
}

void CModelList::RandomModel()
{
	FLOAT fRadius;
	INT nRecur;

	for(int i = 0; i < 5; ++i)
	{
		fRadius		 = ( rand() % 100 ) + 100.0f;
		nRecur		 = ( rand() % 3 ) + 3;
		
		LoadModel( i, fRadius, 18, 36, nRecur, false);
	}
}

void CModelList::Pyramid(CNode * pNode, FLOAT fRadius)
{	
	const FLOAT fQR = fRadius * 0.25f;
	const FLOAT fR03 = fRadius * 0.333333f;
	const FLOAT fn1R = fRadius * 0.942809f;
	const FLOAT fn2R = fRadius * 0.816497f;
	const FLOAT fn3R = fRadius * 0.471405f;

	//enum {O, X, Y, Z, U, T, M, B, END};
	enum { U, T, M, B, END };
	
	pNode->m_nVertex = END;
	pNode->m_pVertexList = new CVertex[pNode->m_nVertex];
	pNode->m_pTransformedList = new CVertex[pNode->m_nVertex];
	//pNode->m_pVertexList[O].pos = CVector4( 0.0f,   0.0f, 0.0f);	pNode->m_pVertexList[O].color = CVector4(   0.0f,   0.0f,   0.0f );
	//pNode->m_pVertexList[X].pos = CVector4(  fQR,   0.0f, 0.0f);	pNode->m_pVertexList[X].color = CVector4( 255.0f,   0.0f,   0.0f );
	//pNode->m_pVertexList[Y].pos = CVector4( 0.0f,    fQR, 0.0f);	pNode->m_pVertexList[Y].color = CVector4(   0.0f, 255.0f,   0.0f );
	//pNode->m_pVertexList[Z].pos = CVector4( 0.0f,   0.0f,  fQR);	pNode->m_pVertexList[Z].color = CVector4(   0.0f,   0.0f, 255.0f );

	pNode->m_pVertexList[U].pos = CVector4( 0.0f,fRadius, 0.0f);	pNode->m_pVertexList[U].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[T].pos = CVector4( 0.0f,  -fR03, fn1R);	pNode->m_pVertexList[T].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[M].pos = CVector4(-fn2R,  -fR03,-fn3R);	pNode->m_pVertexList[M].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[B].pos = CVector4( fn2R,  -fR03,-fn3R);	pNode->m_pVertexList[B].color = CVector4( 255.0f, 255.0f, 255.0f  );
	
	pNode->m_nIndex = 4;
	pNode->m_pCulling = new BOOL[pNode->m_nIndex];
	pNode->m_pIndexList = new INT[pNode->m_nIndex * 3];

	int arrTmp[] = {
		//O, X, O,
		//O, Y, O,
		//O, Z, O,
		T, M, B,
		U, M, T,
		U, T, B,
		U, B, M
	};

	for(int i = 0; i < pNode->m_nIndex * 3; ++i){
		pNode->m_pIndexList[i] = arrTmp[i];
	}
}

void CModelList::Diamond(CNode * pNode, float fRadius)
{
	const FLOAT fAxis = fRadius * 0.2f;
	const FLOAT fS45  = fRadius * 0.7071f;
	//enum {O, X, Y, Z, D, C0, C1, C2, C3, C4, C5, C6, C7, U, END};
	enum { D, C0, C1, C2, C3, C4, C5, C6, C7, U, END };

	pNode->m_nVertex = END;
	pNode->m_pVertexList = new CVertex[pNode->m_nVertex];
	pNode->m_pTransformedList = new CVertex[pNode->m_nVertex];

	//pNode->m_pVertexList[O].pos   = CVector4(  0.0f,    0.0f,    0.0f);	pNode->m_pVertexList[O].color  = CVector4(  0.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[X].pos   = CVector4( fAxis,    0.0f,    0.0f);	pNode->m_pVertexList[X].color  = CVector4(255.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[Y].pos   = CVector4(  0.0f,   fAxis,    0.0f);	pNode->m_pVertexList[Y].color  = CVector4(  0.0f, 255.0f,   0.0f);
	//pNode->m_pVertexList[Z].pos   = CVector4(  0.0f,    0.0f,   fAxis);	pNode->m_pVertexList[Z].color  = CVector4(  0.0f,   0.0f, 255.0f);
	pNode->m_pVertexList[D].pos   = CVector4( -fS45,    0.0f,    0.0f);	pNode->m_pVertexList[D].color  = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C0].pos  = CVector4(  0.0f,    0.0f, fRadius);	pNode->m_pVertexList[C0].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C1].pos  = CVector4(  0.0f,    fS45,    fS45);	pNode->m_pVertexList[C1].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C2].pos  = CVector4(  0.0f, fRadius,    0.0f);	pNode->m_pVertexList[C2].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C3].pos  = CVector4(  0.0f,    fS45,   -fS45);	pNode->m_pVertexList[C3].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C4].pos  = CVector4(  0.0f,    0.0f,-fRadius);	pNode->m_pVertexList[C4].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C5].pos  = CVector4(  0.0f,   -fS45,   -fS45);	pNode->m_pVertexList[C5].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C6].pos  = CVector4(  0.0f,-fRadius,    0.0f);	pNode->m_pVertexList[C6].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[C7].pos  = CVector4(  0.0f,   -fS45,    fS45);	pNode->m_pVertexList[C7].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[U].pos   = CVector4(  fS45,    0.0f,    0.0f);	pNode->m_pVertexList[U].color =  CVector4( 255.0f, 255.0f, 255.0f  );

	pNode->m_nIndex = 16;
	pNode->m_pCulling = new BOOL[pNode->m_nIndex];
	pNode->m_pIndexList = new INT[pNode->m_nIndex * 3];
	int arrTmp[] = {  
		//O, X, O,		// 0
		//O, Y, O,		// 1
		//O, Z, O,		// 2
		D, C1, C0,	// 0
		D, C2, C1,	// 1
		D, C3, C2,	// 2
		D, C4, C3,	// 3
		D, C5, C4,	// 4
		D, C6, C5,	// 5
		D, C7, C6,	// 6
		D, C0, C7,	// 7
		U, C0, C1,	// 8
		U, C1, C2,	// 9
		U, C2, C3,	// 0
		U, C3, C4,	// 1
		U, C4, C5,	// 2
		U, C5, C6,	// 3
		U, C6, C7,	// 4
		U, C7, C0	// 5
	};

	for(int i = 0; i < pNode->m_nIndex * 3; ++i){
		pNode->m_pIndexList[i] = arrTmp[i];
	}
}

void CModelList::Hexagon(CNode * pNode, float fRadius)
{
	float fAxis = fRadius * 0.2f;
	//enum {O, X, Y, Z, LDF, RDF, LUF, RUF, LDB, RDB, LUB, RUB, END};
	enum { LDF, RDF, LUF, RUF, LDB, RDB, LUB, RUB, END };

	pNode->m_nVertex = END;
	pNode->m_pVertexList = new CVertex[pNode->m_nVertex];
	pNode->m_pTransformedList = new CVertex[pNode->m_nVertex];

	//pNode->m_pVertexList[O].pos   = CVector4(  0.0f,   0.0f,   0.0f);		pNode->m_pVertexList[O].color   = CVector4(  0.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[X].pos   = CVector4( fAxis,   0.0f,   0.0f);		pNode->m_pVertexList[X].color   = CVector4(255.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[Y].pos   = CVector4(  0.0f,  fAxis,   0.0f);		pNode->m_pVertexList[Y].color   = CVector4(  0.0f, 255.0f,   0.0f);
	//pNode->m_pVertexList[Z].pos   = CVector4(  0.0f,   0.0f,  fAxis);		pNode->m_pVertexList[Z].color   = CVector4(  0.0f,   0.0f, 255.0f);
	pNode->m_pVertexList[LDF].pos = CVector4(-fRadius,-fRadius, fRadius);	pNode->m_pVertexList[LDF].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[RDF].pos = CVector4( fRadius,-fRadius, fRadius);	pNode->m_pVertexList[RDF].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[LUF].pos = CVector4(-fRadius, fRadius, fRadius);	pNode->m_pVertexList[LUF].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[RUF].pos = CVector4( fRadius, fRadius, fRadius);	pNode->m_pVertexList[RUF].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[LDB].pos = CVector4(-fRadius,-fRadius,-fRadius);	pNode->m_pVertexList[LDB].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[RDB].pos = CVector4( fRadius,-fRadius,-fRadius);	pNode->m_pVertexList[RDB].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[LUB].pos = CVector4(-fRadius, fRadius,-fRadius);	pNode->m_pVertexList[LUB].color = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[RUB].pos = CVector4( fRadius, fRadius,-fRadius);	pNode->m_pVertexList[RUB].color = CVector4( 255.0f, 255.0f, 255.0f  );

	pNode->m_nIndex = 12;
	pNode->m_pCulling = new BOOL[pNode->m_nIndex];
	pNode->m_pIndexList = new INT[pNode->m_nIndex * 3];

	int arrTmp[] = {  
		//O, X, O,		// 0
		//O, Y, O,		// 1
		//O, Z, O,		// 2
		RDF, RUF, LUF,	// 0
		RDF, LUF, LDF,	// 1
		RDB, RUB, RUF,	// 2
		RDB, RUF, RDF,	// 3
		LDB, LUB, RUB,	// 4
		LDB, RUB, RDB,	// 5
		LDF, LUF, LUB,	// 6
		LDF, LUB, LDB,	// 7
		RUF, RUB, LUB,	// 8
		RUF, LUB, LUF,	// 9
		RDB, RDF, LDF,	// 0
		RDB, LDF, LDB,	// 1
	};

	for(int i = 0; i < pNode->m_nIndex * 3; ++i){
		pNode->m_pIndexList[i] = arrTmp[i];
	}
}

void CModelList::GlobeSphere(CNode * pNode, float fRadius, int nLatitude, int nLongitude)
{
	const float fAxis = fRadius * 0.2f;

	int nIndex = 0;

	float fTheta = 180.0f / (nLatitude - 1);
	float fDelta = 360.0f / (nLongitude);

	pNode->m_nVertex = nLatitude * nLongitude + 4;
	pNode->m_pVertexList = new CVertex[pNode->m_nVertex];
	pNode->m_pTransformedList = new CVertex[pNode->m_nVertex];

	//enum {O, X, Y, Z, END};
	enum { END };
	//pNode->m_pVertexList[O].pos   = CVector4(  0.0f,   0.0f,   0.0f);		pNode->m_pVertexList[O].color   = CVector4(  0.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[X].pos   = CVector4( fAxis,   0.0f,   0.0f);		pNode->m_pVertexList[X].color   = CVector4(255.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[Y].pos   = CVector4(  0.0f,  fAxis,   0.0f);		pNode->m_pVertexList[Y].color   = CVector4(  0.0f, 255.0f,   0.0f);
	//pNode->m_pVertexList[Z].pos   = CVector4(  0.0f,   0.0f,  fAxis);		pNode->m_pVertexList[Z].color   = CVector4(  0.0f,   0.0f, 255.0f);

	float fX, fY, fZ;
	nIndex = END;
	for(int i = 0; i < nLatitude; ++i){		
		for(int j = 0; j < nLongitude; ++j){
			fX = cos(fDelta * j * RADIAN) * sin(fTheta * i * RADIAN);
			fY = /*cos(fDelta * j * RADIAN) * */cos(fTheta * i * RADIAN);
			fZ = sin(fDelta * j * RADIAN) * sin(fTheta * i * RADIAN);
			pNode->m_pVertexList[nIndex].pos.x = fRadius * fX;
			pNode->m_pVertexList[nIndex].pos.y = fRadius * fY;
			pNode->m_pVertexList[nIndex].pos.z = fRadius * fZ;
			pNode->m_pVertexList[nIndex].color = CVector4( 255.0f, 255.0f, 255.0f  );
			nIndex++;
		}
	}

	//pNode->m_nIndex = (nLongitude) * 2 * (nLatitude - 1) + 3;
	pNode->m_nIndex = (nLongitude) * 2 * (nLatitude - 1);
	pNode->m_pCulling = new BOOL[pNode->m_nIndex];
	pNode->m_pIndexList = new INT[pNode->m_nIndex * 3];

	//int arrTmp[] = {  
	//	O, X, O,		// 0
	//	O, Y, O,		// 1
	//	O, Z, O,		// 2
	//};

	//for(int i = 0; i < 9; ++i)
	//	pNode->m_pIndexList[i] = arrTmp[i];

	int nSV = END;
	nIndex = 0;
	for(int i = 0; i < nLatitude - 1; ++i){		
		for(int j = 0; j < nLongitude; ++j){			
			if(j  == nLongitude-1){								
				pNode->m_pIndexList[nIndex  ] = nSV;
				pNode->m_pIndexList[nIndex+1] = nSV + nLongitude;
				pNode->m_pIndexList[nIndex+2] = nSV + 1;
				pNode->m_pIndexList[nIndex+3] = nSV;
				pNode->m_pIndexList[nIndex+4] = nSV + 1;
				pNode->m_pIndexList[nIndex+5] = nSV - nLongitude + 1;
			}
			else{
				pNode->m_pIndexList[nIndex  ] = nSV;
				pNode->m_pIndexList[nIndex+1] = nSV + nLongitude;
				pNode->m_pIndexList[nIndex+2] = nSV + nLongitude + 1;
				pNode->m_pIndexList[nIndex+3] = nSV;
				pNode->m_pIndexList[nIndex+4] = nSV + nLongitude + 1;
				pNode->m_pIndexList[nIndex+5] = nSV + 1;
			}
			nSV++;	
			nIndex += 6;
		}
	}
}

void CModelList::GeoSphere(CNode * pNode, float fRadius, int nRecount )
{
	const float fAxis = fRadius * 0.2f;
	int nIndex = 0;
	int nPow = static_cast<int>( pow( 4.0f, nRecount ) );

	pNode->m_nVertex = nPow + 4;
	pNode->m_pVertexList = new CVertex[pNode->m_nVertex];
	pNode->m_pTransformedList = new CVertex[pNode->m_nVertex];

	//enum {O, X, Y, Z, END};
	enum { END };
	//pNode->m_pVertexList[O].pos   = CVector4(  0.0f,   0.0f,   0.0f);		pNode->m_pVertexList[O].color   = CVector4(  0.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[X].pos   = CVector4( fAxis,   0.0f,   0.0f);		pNode->m_pVertexList[X].color   = CVector4(255.0f,   0.0f,   0.0f);
	//pNode->m_pVertexList[Y].pos   = CVector4(  0.0f,  fAxis,   0.0f);		pNode->m_pVertexList[Y].color   = CVector4(  0.0f, 255.0f,   0.0f);
	//pNode->m_pVertexList[Z].pos   = CVector4(  0.0f,   0.0f,  fAxis);		pNode->m_pVertexList[Z].color   = CVector4(  0.0f,   0.0f, 255.0f);
	
	m_nTempVertex = END;
	pNode->m_pVertexList[m_nTempVertex].pos = CVector4(      0.0f,      0.0f,     -1.0f);	pNode->m_pVertexList[m_nTempVertex++].color   = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[m_nTempVertex].pos = CVector4(      0.0f,-0.942809f, 0.333333f);	pNode->m_pVertexList[m_nTempVertex++].color   = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[m_nTempVertex].pos = CVector4(-0.816497f, 0.471405f, 0.333333f);	pNode->m_pVertexList[m_nTempVertex++].color   = CVector4( 255.0f, 255.0f, 255.0f  );
	pNode->m_pVertexList[m_nTempVertex].pos = CVector4( 0.816497f, 0.471405f, 0.333333f);	pNode->m_pVertexList[m_nTempVertex++].color   = CVector4( 255.0f, 255.0f, 255.0f  );

	nRecount--;
	//pNode->m_nIndex = nPow + 3;
	pNode->m_nIndex = nPow;
	pNode->m_pCulling = new BOOL[pNode->m_nIndex];
	pNode->m_pIndexList = new INT[pNode->m_nIndex * 3];

	//int arrTmp[] = {  
	//	O, X, O,		// 0
	//	O, Y, O,		// 1
	//	O, Z, O,		// 2
	//};

	//for(int i = 0; i < 9; ++i)
	//	pNode->m_pIndexList[i] = arrTmp[i];

	m_nTempIndex = 0;
	DivideTriangle( pNode, END + 0, END + 1, END + 2, nRecount );
	DivideTriangle( pNode, END + 0, END + 2, END + 3, nRecount );
	DivideTriangle( pNode, END + 0, END + 3, END + 1, nRecount );
	DivideTriangle( pNode, END + 1, END + 3, END + 2, nRecount );

	for (int i = END; i < pNode->m_nVertex; ++i)
	{
		pNode->m_pVertexList[i].pos.x *= fRadius;
		pNode->m_pVertexList[i].pos.y *= fRadius;
		pNode->m_pVertexList[i].pos.z *= fRadius;
	}
}

void CModelList::DivideTriangle(CNode * pNode, int nTop, int nMid, int nBot, int nRecount)
{
	if ( nRecount > 0 )
	{
		int nV[3];
		nV[0] = m_nTempVertex++;
		nV[1] = m_nTempVertex++;
		nV[2] = m_nTempVertex++;

		pNode->m_pVertexList[nV[0]].pos = CVector4( 
			( pNode->m_pVertexList[nTop].pos.x + pNode->m_pVertexList[nMid].pos.x ) * 0.5f, 
			( pNode->m_pVertexList[nTop].pos.y + pNode->m_pVertexList[nMid].pos.y ) * 0.5f, 
			( pNode->m_pVertexList[nTop].pos.z + pNode->m_pVertexList[nMid].pos.z ) * 0.5f );		
		pNode->m_pVertexList[nV[0]].color = CVector4( 255.0f, 255.0f, 255.0f  );
		pNode->m_pVertexList[nV[1]].pos = CVector4( 
			( pNode->m_pVertexList[nTop].pos.x + pNode->m_pVertexList[nBot].pos.x ) * 0.5f, 
			( pNode->m_pVertexList[nTop].pos.y + pNode->m_pVertexList[nBot].pos.y ) * 0.5f, 
			( pNode->m_pVertexList[nTop].pos.z + pNode->m_pVertexList[nBot].pos.z ) * 0.5f );		
		pNode->m_pVertexList[nV[1]].color = CVector4( 255.0f, 255.0f, 255.0f  );
		pNode->m_pVertexList[nV[2]].pos = CVector4( 
			( pNode->m_pVertexList[nMid].pos.x + pNode->m_pVertexList[nBot].pos.x ) * 0.5f, 
			( pNode->m_pVertexList[nMid].pos.y + pNode->m_pVertexList[nBot].pos.y ) * 0.5f, 
			( pNode->m_pVertexList[nMid].pos.z + pNode->m_pVertexList[nBot].pos.z ) * 0.5f );		
		pNode->m_pVertexList[nV[2]].color = CVector4( 255.0f, 255.0f, 255.0f  );
		pNode->m_pVertexList[nV[0]].pos.Normalize();
		pNode->m_pVertexList[nV[1]].pos.Normalize();
		pNode->m_pVertexList[nV[2]].pos.Normalize();

		DivideTriangle( pNode,  nTop, nV[1], nV[0], nRecount-1 );
		DivideTriangle( pNode, nV[1],  nBot, nV[2], nRecount-1 );
		DivideTriangle( pNode, nV[0], nV[2],  nMid, nRecount-1 );
		DivideTriangle( pNode, nV[0], nV[1], nV[2], nRecount-1 );
	}
	else
	{
		pNode->m_pIndexList[m_nTempIndex++] = nTop;
		pNode->m_pIndexList[m_nTempIndex++] = nMid;
		pNode->m_pIndexList[m_nTempIndex++] = nBot;
	}
}
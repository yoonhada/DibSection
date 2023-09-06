#include "stdafx.h"

CDraw3D::CDraw3D(CMemory * pWndData)
	: m_pWndData(pWndData)
{
}

CDraw3D::~CDraw3D(void)
{}

int CDraw3D::GetOffSet(const CVertex& vertex, const int nWidth)
{
	return static_cast<int>(vertex.pos.x) * 3 + static_cast<int>(vertex.pos.y) * GetBytePerScanLine(nWidth);
}

int CDraw3D::GetOffSet(const int nPosX, const int nPosY, const int nWidth)
{
	return nPosX * 3 + nPosY * GetBytePerScanLine(nWidth);
}

int CDraw3D::GetBytePerScanLine(int nWidth)	
{ 
	return (nWidth * 3 + 3) & ~3; 
}

void CDraw3D::Draw(int x, int y, int r, int g, int b)
{
	int nOffsetNor = GetOffSet(x, y, m_pWndData->GetWidth());
	if( GetOffSet(0, y, m_pWndData->GetWidth()) >= nOffsetNor || 
		GetOffSet(0, y + 1, m_pWndData->GetWidth()) <= nOffsetNor || 
		0 > y || y >= m_pWndData->GetHeight())
		return;

	*(m_pWndData->GetBits() + nOffsetNor + 0) = b;
	*(m_pWndData->GetBits() + nOffsetNor + 1) = g;
	*(m_pWndData->GetBits() + nOffsetNor + 2) = r;
}

void CDraw3D::Draw(const CVertex& vertex1, const CVertex& vertex2, const CVector4& color)
{
	int r = static_cast<int>(color.x + 0.5f);
	int g = static_cast<int>(color.y + 0.5f);
	int b = static_cast<int>(color.z + 0.5f);
	int t = 0x8000;
	int x1 = static_cast<int>(vertex1.pos.x);
	int y1 = static_cast<int>(vertex1.pos.y);
	int x2 = static_cast<int>(vertex2.pos.x);
	int y2 = static_cast<int>(vertex2.pos.y);

	int nDeltaX = x2 - x1;
	int nDeltaY = y2 - y1;

	Draw(x1, y1, r, g, b);

	if (nDeltaX != 0 && abs(nDeltaX) >= abs(nDeltaY)) {
		int m = (nDeltaY << 16) / nDeltaX;
		t += y1 << 16;
		nDeltaX = (nDeltaX < 0) ? -1 : 1;
		m *= nDeltaX;
		while (x1 != x2) {
			x1 += nDeltaX;
			t += m;
			Draw(x1, t >> 16, r, g, b);
		}
	} else if (nDeltaY != 0 && abs(nDeltaX) < abs(nDeltaY)) {
		int m = (nDeltaX << 16) / nDeltaY;
		t += x1 << 16;
		nDeltaY = (nDeltaY < 0) ? -1 : 1;
		m *= nDeltaY ;
		while (y1 != y2) {
			y1 += nDeltaY;
			t += m;
			Draw(t >> 16, y1, r, g, b);
		}
	}
}

void CDraw3D::Triangle( CNode * pNode )
{
	CVertex vertex1, vertex2, vertex3;

	for(int i = 0; i < pNode->m_nIndex; i++)
	{
		if(pNode->m_pCulling[i] == TRUE)
			continue;

		vertex1 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 0]];
		vertex2 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 1]];
		vertex3 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 2]];

		Draw( vertex1, vertex2, vertex1.color );
		Draw( vertex2, vertex3, vertex1.color );
		Draw( vertex3, vertex1, vertex1.color );
	}
}

void CDraw3D::Flat( CNode * pNode )
{
	CVertex vertex1, vertex2, vertex3;

	for(int i = 0; i < pNode->m_nIndex; i++)
	{
		if(pNode->m_pCulling[i] == TRUE)
			continue;

		vertex1 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 0]];
		vertex2 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 1]];
		vertex3 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 2]];

		Draw( vertex1, vertex2, vertex1.color );
		Draw( vertex2, vertex3, vertex1.color );
		Draw( vertex3, vertex1, vertex1.color );
	}
}

void CDraw3D::Goroud( CNode * pNode )
{
	CVertex vertex1, vertex2, vertex3;

	for(int i = 0; i < pNode->m_nIndex; i++)
	{
		if(pNode->m_pCulling[i] == TRUE)
			continue;

		vertex1 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 0]];
		vertex2 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 1]];
		vertex3 = pNode->m_pTransformedList[pNode->m_pIndexList[i * 3 + 2]];

		Draw( vertex1, vertex2, vertex1.color );
		Draw( vertex2, vertex3, vertex2.color );
		Draw( vertex3, vertex1, vertex3.color );
	}
}

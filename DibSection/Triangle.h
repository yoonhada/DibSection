#pragma once

class CTriangle : public CDrawModify
{
public:
	CTriangle( CMemory * );
	virtual ~CTriangle();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );

protected:
	enum { TOP, MID, BOT };
	enum { TOP2MID, TOP2BOT, MID2BOT };
	VOID SortTri( CPoint2 * );
	VOID Swap( CPoint2 &, CPoint2 & );

	CPoint2 m_oTemp;
};
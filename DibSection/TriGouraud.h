#pragma once

class CTriGouraud : public CTriangle
{
public:
	CTriGouraud( CMemory * );
	virtual ~CTriGouraud();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};
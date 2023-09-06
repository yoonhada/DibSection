#pragma once

class CTriFlat : public CTriangle
{
public:
	CTriFlat( CMemory * );
	virtual ~CTriFlat();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};

#pragma once

class CSpBezier3 : public CDrawModify
{
public:
	CSpBezier3( CMemory * );
	virtual ~CSpBezier3();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
};
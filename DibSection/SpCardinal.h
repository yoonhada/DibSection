#pragma once

class CSpCardinal : public CDrawModify
{
public:
	CSpCardinal( CMemory * );
	virtual ~CSpCardinal();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
};
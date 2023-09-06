#pragma once

class CSpHermit : public CDrawModify
{
public:
	CSpHermit( CMemory * );
	virtual ~CSpHermit();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};
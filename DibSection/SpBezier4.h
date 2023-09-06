#pragma once

class CSpBezier4 : public CDrawModify
{
public:
	CSpBezier4( CMemory * );
	virtual ~CSpBezier4();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};
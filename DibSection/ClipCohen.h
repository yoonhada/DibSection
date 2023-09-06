#pragma once

class CClipCohen : public CDrawModify
{
public:
	CClipCohen( CMemory * );
	virtual ~CClipCohen();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );

private:
	enum { TOP = 0x1, BOTTOM = 0x2, RIGHT = 0x4, LEFT = 0x8 };

	BOOL GetOutCode( const CPoint2& );
};
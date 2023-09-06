#pragma once

class CDrawPixel : public CDraw
{
public:
	CDrawPixel( CMemory * );
	CDrawPixel( CMemory *, INT );
	virtual ~CDrawPixel();

	virtual VOID Paint();
	virtual VOID Draw( const CPoint2& );

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};
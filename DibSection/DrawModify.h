#pragma once

class CDrawModify : public CDraw
{
public:
	CDrawModify( CMemory * );
	CDrawModify( CMemory *, INT );
	virtual ~CDrawModify();

	virtual VOID Paint();
	virtual VOID DrawGuide( );
	virtual VOID DrawGuide( const CPoint2& );
	virtual VOID DrawGuide( const CPoint2&, const CPoint2& );
	virtual VOID Draw( const CPoint2& );
	virtual VOID Line();
	virtual VOID Line( const CPoint2&, const CPoint2&, BOOL = TRUE );
	virtual VOID LineRate( const CPoint2&, const CPoint2& );

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );

protected:
	BOOL m_bAddGuidePos;
};
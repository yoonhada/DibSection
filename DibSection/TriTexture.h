#pragma once

class CTriTexture : public CDrawModify
{
public:
	CTriTexture( CMemory * );
	virtual ~CTriTexture();

	virtual VOID Clear();

	virtual VOID Paint();
	virtual VOID DrawGuideLine( );

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );

private:
	enum { TOP2MID, TOP2BOT, MID2BOT };
	VOID DrawTexture( const CPoint2&, const CPoint2&, const CPoint2& );

	BOOL	m_bMove;
	CPoint2 m_oMousePos;
};
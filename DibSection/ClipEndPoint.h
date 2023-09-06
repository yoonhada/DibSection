#pragma once

class CClipEndPoint : public CDrawModify
{
public:
	CClipEndPoint( CMemory * );
	virtual ~CClipEndPoint();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );
};
#pragma once

class CClipParametric : public CDrawModify
{
public:
	CClipParametric( CMemory * );
	virtual ~CClipParametric();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CPoint2& );
	virtual VOID OnMove( const CPoint2& );
	virtual VOID OnUp( const CPoint2& );

private:
	BOOL ClipPoint( const CPoint2& );
	BOOL CLIPt( INT, INT, FLOAT&, FLOAT& );
};
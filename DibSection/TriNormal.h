#pragma once

class CTriNormal : public CDrawModify
{
public:
	CTriNormal( CMemory * );
	virtual ~CTriNormal();

	virtual VOID Clear();

	virtual VOID Paint();

	virtual VOID OnDown( const CVector2& );
};
#pragma once

//
class CLineEFA : public CDrawPixel
{
public:
	CLineEFA( CMemory * );
	virtual ~CLineEFA();

	virtual VOID Paint();
};
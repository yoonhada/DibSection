#pragma once

// Midpoint Line Algorithm
class CLineMLA : public CDrawPixel
{
public:
	CLineMLA( CMemory * );
	virtual ~CLineMLA();

	virtual VOID Paint();
};
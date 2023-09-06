#pragma once

// Basic Incremental Algorithm
class CLineDDA : public CDrawPixel
{
public:
	CLineDDA( CMemory * );
	virtual ~CLineDDA();

	virtual VOID Paint();
};
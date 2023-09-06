#pragma once

// 8-Way Symmetry
class CCircle : public CDrawPixel
{
public:
	CCircle( CMemory * );
	virtual ~CCircle(void);

	virtual VOID Paint();
};

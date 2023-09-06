#pragma once

class CDraw3D
{
private:

protected:
	CMemory * m_pWndData;

public:
	CDraw3D(CMemory * pWndData);
	virtual ~CDraw3D(void);

	// Get
	int GetBytePerScanLine(int);
	int GetOffSet(const CVertex&, const int);
	int GetOffSet(const int, const int, const int);

	// Method
	virtual void Draw(int, int, int, int, int);
	virtual void Draw(const CVertex&, const CVertex&, const CVector4&);

	void Triangle(CNode *);
	void Flat(CNode *);
	void Goroud(CNode *);

};
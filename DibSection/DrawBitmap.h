#pragma once

class CDrawBitmap : public CDraw
{
public:
	CDrawBitmap( CMemory *, INT, INT );
	virtual ~CDrawBitmap(void);

	virtual VOID Paint();
	virtual VOID Draw( const CPoint2& );

	virtual VOID OnDown( const CPoint2& )			{};
	virtual VOID OnMove( const CPoint2& )			{};
	virtual VOID OnUp( const CPoint2& )			{};

	// Get
	BYTE *	GetImages()				{ return m_pImage; }
	INT		GetSize()				{ return m_nSize; }
	INT		GetWidth()				{ return m_nWidth; }
	INT		GetHeight()				{ return m_nHeight; }
	INT		GetScanLine()			{ return m_nBytePerScanLine; }

private:
	INT m_nSize;
	INT m_nWidth;
	INT m_nHeight;
	INT m_nBytePerScanLine;

	BYTE * m_pImage;
	BYTE * m_pBackup;

	BOOL m_isDraw;
};
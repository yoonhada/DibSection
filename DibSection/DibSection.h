#pragma once

class CMemory;

class CDibSection
{
private:
	CMemory	*	m_pMemory;
	HBITMAP		m_hOldBitMap;

	BOOL m_bDrawInable;

public:
	CDibSection( CMemory* );
	virtual ~CDibSection();

	// Method
	VOID Clear();
	VOID Create();
	VOID Destory();
	VOID Render();
	VOID Update();

	VOID OnMove( const CPoint2& );
	VOID OnDown( const CPoint2& );
	VOID OnUp( const CPoint2& );

	BOOL LoadBitmapEx( HWND );
	/*


	HWND		m_hWnd;
	HDC			m_hScrDC;
	HDC			m_hMemDC;
	BYTE *		m_pBits;

	INT			m_nWidth;
	INT			m_nHeight;
	INT			m_nBytePerScanLine;

public:
	CDibSection( HWND );
	virtual ~CDibSection();

	// Get
	HDC GetMemDC()				{ return m_hMemDC; }
	INT GetWidth()				{ return m_nWidth; }
	INT GetHeight()				{ return m_nHeight; }
	BYTE * GetBits()			{ return m_pBits; }

	// Set

	// Method
	VOID Clear();
	VOID Create();
	VOID Destory();
	VOID Render();
	VOID Update();
	*/
};

#pragma once

class CNode;
class CDraw;
class CDraw3D;
class CDrawBitmap;
class CModelList;

class CMemory
{
public:
	enum {  FORGROUND, BACKGROUND };
	enum {  NONE, 
			CLINEDDA, CLINEMLA, CLINEDSA, CLINEEFA, 
			CCIRCLE, CCIRCLEMIDP, CCIRCLESECORDER, 
			CSPCARDINAL, CSPHERMIT, CSPBEZIER3, CSPBEZIER4, 
			CCLIPENDPOINT, CCLIPCOHEN, CCLIPPARAMETRIC, 
			CTRIANGLE, CTRIFLAT, CTRIGOURAUD, CTRITEXTURE, 
			END };


	CMemory( HWND );
	virtual ~CMemory();

	VOID Clear();
	VOID Create();
	VOID Destory();
	VOID Render();
	VOID Update();

	// Get
	INT GetWidth()  const	{ return m_nWidth; }
	INT GetHeight() const	{ return m_nHeight; }
	BYTE * GetBits() const	{ return m_pBits; }

	HDC GetMemDC()			{ return m_hMemDC; }
	HDC GetScrDC()			{ return m_hScrDC; }
	RECT GetRect() const	{ return m_rect; }

	COLORREF GetColor(int nType) const;

	CDraw * GetDraw() const		{ return m_pDraw; }
	CDraw3D * GetDraw3D() const { return m_pDraw3D; }
	CDrawBitmap * GetDrawBit()	{ return m_pBitMap; }


	CModelList * GetList()				{ return m_pList; }


	// Set
	VOID SetBits( BYTE * pBits )		{ m_pBits = pBits; }

	VOID SetColor( INT, COLORREF );

	VOID SetDraw( CDraw * pDraw )		{ m_pDraw = pDraw; }
	VOID SetDraw( CDrawBitmap *, BOOL );
	VOID SetDraw( INT nSelect )			{ m_pDraw = m_ppDrawMenu[nSelect]; }

private:
	INT			m_nWidth;
	INT			m_nHeight;
	BYTE *		m_pBits;

	HDC			m_hScrDC;
	HDC			m_hMemDC; 
	RECT		m_rect;
	COLORREF 	m_colorBackGround;
	COLORREF	m_colorForGround;

	CDraw *		m_pDraw;
	CDraw3D *	m_pDraw3D;
	CDraw **	m_ppDrawMenu;
	CDrawBitmap * m_pBitMap;

	CModelList * m_pList;
};

#pragma once

class CNode;

class CDraw
{
public:
	CDraw( CMemory * );
	CDraw( CMemory * , INT );
	virtual ~CDraw();

	// Get
	INT GetBytePerScanLine( const INT );
	INT GetOffset( const INT, const INT, const INT );
	INT GetIndex()						{ return m_listVector.size(); }
	CPoint2& GetVector();
	CPoint2& GetVector( INT );

	// Set
	VOID AddVector( const CPoint2& );
	VOID SetVector( const CPoint2&, BOOL = TRUE );
	VOID UpdateVector( const CPoint2& );
	VOID MoveVector( const CPoint2& );
	const CPoint2 DeleteVector( const CPoint2& );
	VOID Drawing( BOOL bDraw )			{ m_bDrawing = bDraw; }

	// Method
	BOOL IsDraw()						{ return m_bDrawing; }
	BOOL IsSamePosition( const CPoint2& );
	BOOL FindPosition( const CPoint2& );
	INT GetSizeVector()					{ return m_listVector.size(); }
	VOID ClearVector();

	//virtual
	virtual VOID Clear()				{}
	virtual VOID Paint() = 0;
	virtual VOID Draw( const CPoint2& ) = 0;

	virtual VOID OnDown( const CPoint2& ) = 0;
	virtual VOID OnMove( const CPoint2& ) = 0;
	virtual VOID OnUp( const CPoint2& ) = 0;

protected:
	enum { GUIDELINE = 5 };
	enum { RE, GR, BL };
	const INT m_nPoint;
	CMemory * m_pMemory;

	std::list < CPoint2 > m_listVector;
	std::list < CPoint2 >::iterator m_iter;
	std::list < CPoint2 >::reverse_iterator m_riter;
	CPoint2 ** m_ppVector;
	CPoint2 m_vectorRECT[2];

private:
	BOOL m_bDrawing;
};

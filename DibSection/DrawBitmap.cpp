#include "stdafx.h"
#include "DrawBitmap.h"

CDrawBitmap::CDrawBitmap( CMemory * pMemory, INT nWidth, INT nHeight )
: CDraw( pMemory, 1 )
, m_nSize( nWidth * nHeight * 3 )
, m_nWidth( nWidth )
, m_nHeight( nHeight )
, m_isDraw( FALSE )
{
	m_nBytePerScanLine = GetBytePerScanLine( nWidth );

	m_pImage = new BYTE[ m_nSize ];
	memset( m_pImage, 0, m_nSize );
	m_pBackup = NULL;

	SetVector( CPoint2(0, 0) );
	SetVector( CPoint2(0, 0) );
}

CDrawBitmap::~CDrawBitmap()
{
	SAFE_DELETE( m_pImage );
}

VOID CDrawBitmap::Paint()
{
	Draw( GetVector() );
}

VOID CDrawBitmap::Draw( const CPoint2& oPos )
{
	BYTE * pBits;
	BYTE * pTempImage;

	int nScanLine = GetBytePerScanLine( m_pMemory->GetWidth() );
	int nInterval = m_nBytePerScanLine * ( m_nHeight - 1 );

	pBits = m_pMemory->GetBits();
	pTempImage = m_pImage + nInterval;
	//pBits += ( nScanLine * nCurrY );
	for( int i = 0; i < m_nHeight; ++i )
	{
		//memcpy( ( pBits + nCurrX * 3 ), pTempImage, m_nBytePerScanLine );
		memcpy( pBits, pTempImage, m_nBytePerScanLine );
		pTempImage -= m_nBytePerScanLine;
		pBits += nScanLine;
	}
}
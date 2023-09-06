#include "stdafx.h"
#include "DrawPixel.h"

CDrawPixel::CDrawPixel( CMemory * pMemory )
: CDraw( pMemory, 1 )
{
}

CDrawPixel::CDrawPixel( CMemory * pMemory, INT nPoint)
: CDraw( pMemory, nPoint )
{
}

CDrawPixel::~CDrawPixel()
{
}

VOID CDrawPixel::Paint()
{
	Draw( GetVector() );
}

VOID CDrawPixel::Draw( const CPoint2& oPos )
{
	if( m_vectorRECT[0].x < oPos.x && oPos.x < m_vectorRECT[1].x &&
		m_vectorRECT[0].y < oPos.y && oPos.y < m_vectorRECT[1].y )
	{
		INT nOffset = GetOffset( oPos.x, oPos.y, m_pMemory->GetWidth() );

		if ( IsDraw() )
		{
			*( m_pMemory->GetBits() + nOffset + 0 )	^= oPos.fb;
			*( m_pMemory->GetBits() + nOffset + 1 ) ^= oPos.fg;
			*( m_pMemory->GetBits() + nOffset + 2 )	^= oPos.fr;
		}
		else
		{
			*( m_pMemory->GetBits() + nOffset + 0 )	= oPos.fb;
			*( m_pMemory->GetBits() + nOffset + 1 ) = oPos.fg;
			*( m_pMemory->GetBits() + nOffset + 2 )	= oPos.fr;
		}
	}
}

VOID CDrawPixel::OnDown( const CPoint2& oPos )
{
	SetVector( oPos );
	SetVector( oPos );
	Paint();
	Drawing( TRUE );
}

VOID CDrawPixel::OnMove( const CPoint2& oPos )
{
	Paint();
	SetVector( oPos, FALSE );
	Paint();
}

VOID CDrawPixel::OnUp( const CPoint2& oPos )
{
	Drawing( FALSE );
	SetVector( oPos );
	Paint();

	ClearVector();
}
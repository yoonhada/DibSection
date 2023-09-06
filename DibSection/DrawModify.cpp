#include "stdafx.h"
#include "DrawModify.h"

CDrawModify::CDrawModify( CMemory * pMemory )
: CDraw( pMemory, 1 )
, m_bAddGuidePos( FALSE )
{
}

CDrawModify::CDrawModify( CMemory * pMemory, INT nPoint)
: CDraw( pMemory, nPoint )
, m_bAddGuidePos( FALSE )
{
}

CDrawModify::~CDrawModify()
{
}

VOID CDrawModify::Paint()
{
	Draw( GetVector() );
}

VOID CDrawModify::Draw( const CPoint2& oPos )
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

VOID CDrawModify::Line()
{
	CPoint2 oPosStart;
	CPoint2 oPosEnd;

	std::list < CPoint2 >::iterator it = m_listVector.begin();
	oPosEnd = *it;
	for ( it = m_listVector.begin(); it != m_listVector.end(); it++ )
	{
		oPosStart = *it;
		it++;
		oPosEnd = *it;

		Line( oPosStart, oPosEnd );
	}

}

VOID CDrawModify::Line( const CPoint2& oPosStart, const CPoint2& oPosEnd, BOOL bBgColor )
{
	CPoint2 oPos = oPosStart;
	if ( bBgColor )		oPos.SetColor( oPos.GetColor( CMemory::BACKGROUND ) );

	BOOL yLonger = FALSE;
	INT nLongLen = oPosEnd.x - oPos.x;
	INT nShortLen = oPosEnd.y - oPos.y;

	if ( abs( nShortLen ) > abs( nLongLen ) ) 
	{
		INT swap = nShortLen;
		nShortLen = nLongLen;
		nLongLen = swap;				
		yLonger = true;
	}

	INT nIncr;
	if ( nLongLen  ==  0 )	nIncr = 0;
	else					nIncr = ( nShortLen << 16 ) / nLongLen;

	if ( yLonger )
	{
		if ( nLongLen > 0 ) 
		{
			nLongLen += oPos.y;

			for ( INT i = 0x8000 + ( oPos.x << 16 ); oPos.y <= nLongLen; ++oPos.y ) 
			{
				oPos.x = i >> 16;
				Draw( oPos );
				i += nIncr;
			}
			return;
		}

		nLongLen += oPos.y;
		for ( INT i = 0x8000 + ( oPos.x << 16 ); oPos.y >= nLongLen; --oPos.y ) 
		{
			oPos.x = i >> 16;
			Draw( oPos );
			i -= nIncr;
		}

		return;
	}

	if ( nLongLen > 0 ) 
	{
		nLongLen += oPos.x;
		for ( INT i = 0x8000 + ( oPos.y << 16 ); oPos.x <= nLongLen; ++oPos.x ) 
		{
			oPos.y = i >> 16;
			Draw( oPos );
			i += nIncr;
		}

		return;
	}

	nLongLen += oPos.x;
	for ( INT i = 0x8000 + ( oPos.y << 16 ); oPos.x >= nLongLen; --oPos.x ) 
	{
		oPos.y = i >> 16;
		Draw( oPos );
		i -= nIncr;
	}

	return;
}

VOID CDrawModify::LineRate( const CPoint2& oPosStart, const CPoint2& oPosEnd )
{
	CPoint2 oPos = oPosStart;

	INT nR, nG, nB;
	INT nDeltaX = oPosEnd.x - oPosStart.x;

	if ( nDeltaX != 0)		
	{
		INT nDeltaR = ( ( oPosEnd.fr - oPosStart.fr ) << 16 ) / nDeltaX;
		INT nDeltaG = ( ( oPosEnd.fg - oPosStart.fg ) << 16 ) / nDeltaX;
		INT nDeltaB = ( ( oPosEnd.fb - oPosStart.fb ) << 16 ) / nDeltaX;
		INT nIncre  = ( nDeltaX > 0 ) ? 1 : -1;

		nR = 0x8000 + ( oPosStart.fr << 16 );
		nG = 0x8000 + ( oPosStart.fg << 16 );
		nB = 0x8000 + ( oPosStart.fb << 16 );

		for ( int i = 0; i < abs( nDeltaX ); ++i )
		{
			oPos.x += nIncre;
			nR += ( nDeltaR * nIncre );
			nG += ( nDeltaG * nIncre );
			nB += ( nDeltaB * nIncre );

			oPos.SetColor( RGB( ( nR >> 16 ), ( nG >> 16 ), ( nB >> 16 ) ) );
			Draw( oPos );
		}
	}
}

VOID CDrawModify::DrawGuide( const CPoint2& oPos )
{
	const int nMax = GUIDELINE << 1;
	CPoint2 oGuidePos = oPos;
	oGuidePos.fr = ( oPos.br + oPos.br ) >> 1;
	oGuidePos.fg = ( oPos.bg + oPos.bg ) >> 1;
	oGuidePos.fb = ( oPos.bb + oPos.bb ) >> 1;

	for ( int i = 0; i < nMax; ++i )
	{
		oGuidePos.x = oPos.x - GUIDELINE + i;
		oGuidePos.y = oPos.y - GUIDELINE;
		Draw( oGuidePos );
		oGuidePos.x = oPos.x + GUIDELINE;
		oGuidePos.y = oPos.y - GUIDELINE + i;
		Draw( oGuidePos );
		oGuidePos.x = oPos.x + GUIDELINE - i;
		oGuidePos.y = oPos.y + GUIDELINE;
		Draw( oGuidePos );
		oGuidePos.x = oPos.x - GUIDELINE;
		oGuidePos.y = oPos.y + GUIDELINE - i;
		Draw( oGuidePos );
	}
}

VOID CDrawModify::DrawGuide( )
{
	std::list < CPoint2 >::iterator It;
	
	for ( It = m_listVector.begin(); It != m_listVector.end(); It++ )
	{
		DrawGuide( *It );
	}
}

VOID CDrawModify::DrawGuide( const CPoint2& oPosLT, const CPoint2& oPosRB )
{
	if ( oPosLT.x == oPosRB.x && oPosLT.y == oPosRB.y )
		return;
	
	CPoint2 oPos = oPosLT;
	oPos.fr = oPos.br;
	oPos.fg = oPos.bg;
	oPos.fb = oPos.bb;

	INT nDeltaX = oPosRB.x - oPosLT.x;
	INT nDeltaY = oPosRB.y - oPosLT.y;
	INT nStepX = ( nDeltaX < 0 ) ? -1 : 1;
	INT nStepY = ( nDeltaY < 0 ) ? -1 : 1;

	for (INT i = 0; i < abs( nDeltaX ); ++i )
	{
		oPos.x = oPosLT.x + ( i * nStepX );
		oPos.y = oPosLT.y;
		Draw( oPos );
		oPos.x = oPosRB.x - ( i * nStepX );
		oPos.y = oPosRB.y;
		Draw( oPos );
	}

	for (INT i = 0; i < abs( nDeltaY ); ++i )
	{
		oPos.x = oPosLT.x;
		oPos.y = oPosLT.y + ( i * nStepY );
		Draw( oPos );
		oPos.x = oPosRB.x;
		oPos.y = oPosRB.y - ( i * nStepY );
		Draw( oPos );
	}
}

VOID CDrawModify::OnDown( const CPoint2& oPos )
{
	if ( IsSamePosition( oPos ) )
	{
		Drawing( TRUE );
		DrawGuide();
		Paint();
		UpdateVector( oPos );
		Paint();
		DrawGuide();
	}
	else
	{
		CPoint2 oGuidePos;
		if ( GetSizeVector() >= m_nPoint )
		{
			Drawing( TRUE );
			DrawGuide();
			Paint();
			Drawing( FALSE );
			Paint();

			ClearVector();
			m_bAddGuidePos = FALSE;
		}

		SetVector( oPos );
		if ( GetSizeVector() == 2 && m_bAddGuidePos == FALSE )
		{
			m_bAddGuidePos = TRUE;

			oGuidePos = oPos;
			oGuidePos.x = ( GetVector( 0 ).x + oPos.x ) >> 1;
			oGuidePos.y = ( GetVector( 0 ).y + oPos.y ) >> 1; 

			std::list < CPoint2 >::iterator It;
			It = m_listVector.begin();
			++It;
			m_listVector.insert( It, oGuidePos );			
		}

		Drawing( TRUE );
		Paint();
		DrawGuide( oPos );
		DrawGuide( oGuidePos );
	}
}

VOID CDrawModify::OnMove( const CPoint2& oPos )
{
	DrawGuide();
	Paint();
	UpdateVector( oPos );
	Paint();
	DrawGuide();
}

VOID CDrawModify::OnUp( const CPoint2& oPos )
{
	DrawGuide();
	Paint();
	UpdateVector( oPos );
	Paint();
	DrawGuide();
	Drawing( FALSE );
}
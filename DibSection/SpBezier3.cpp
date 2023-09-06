#include "stdafx.h"
#include "SpBezier3.h"

CSpBezier3::CSpBezier3( CMemory * pMemory )
: CDrawModify( pMemory, 3 )
{
}

CSpBezier3::~CSpBezier3()
{
}

VOID CSpBezier3::Clear()
{
	Drawing( TRUE );
	DrawGuide();
	Paint();
	Drawing( FALSE );
	Paint();

	ClearVector();
	m_bAddGuidePos = FALSE;
}

VOID CSpBezier3::Paint()
{
	if ( GetSizeVector() <= 1 )
	{
		return;
	}

	CPoint2 oPosF = GetVector( 0 );
	CPoint2 oPosC = GetVector( 1 );
	CPoint2 oPosE = GetVector( 2 );
	CPoint2 oOld, oPos = oPosF;

	for ( float f = 0.0f; f < 1.0f; f += 0.001f )
	{
		oPos.x = static_cast<INT>( ( 1.0f - f ) * ( 1.0f - f ) * oPosF.x + 2.0f * f * ( 1.0f - f ) * oPosC.x + f * f * oPosE.x );
		oPos.y = static_cast<INT>( ( 1.0f - f ) * ( 1.0f - f ) * oPosF.y + 2.0f * f * ( 1.0f - f ) * oPosC.y + f * f * oPosE.y );

		if ( !( oOld.x == oPos.x && oOld.y == oPos.y ) )
		{
			CDrawModify::Draw( oPos );
			oOld = oPos;
		}
	}
}

VOID CSpBezier3::OnDown( const CPoint2& oPos )
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
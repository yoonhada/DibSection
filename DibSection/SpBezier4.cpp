#include "stdafx.h"
#include "SpBezier4.h"

CSpBezier4::CSpBezier4( CMemory * pMemory )
: CDrawModify( pMemory, 4 )
{
}

CSpBezier4::~CSpBezier4()
{
}

VOID CSpBezier4::Clear()
{
	if ( GetSizeVector() < 2 )		{ return; }
	
	Drawing( TRUE );
	Line();
	DrawGuide();
	Paint();
	Drawing( FALSE );
	Paint();

	ClearVector();
	m_bAddGuidePos = FALSE;
}

VOID CSpBezier4::Paint()
{
	if ( GetSizeVector() <= 2 )
	{
		return;
	}

	CPoint2 oPos0 = GetVector( 0 );
	CPoint2 oGui0 = GetVector( 1 );
	CPoint2 oGui1 = GetVector( 2 );
	CPoint2 oPos1 = GetVector( 3 );
	CPoint2 oOld, oPos = oPos0;

	for ( FLOAT f = 0.0f; f < 1.0f; f += 0.001f )
	{
		oPos.x = static_cast<INT>( ( 1.0f - f ) * ( 1.0f - f ) * ( 1.0f - f ) * oPos0.x + 3.0f * f * ( 1.0f - f ) * ( 1.0f - f ) * oPos1.x + 3.0f * f * f * ( 1.0f - f ) * oGui0.x + f * f * oGui1.x );		
		oPos.y = static_cast<INT>( ( 1.0f - f ) * ( 1.0f - f ) * ( 1.0f - f ) * oPos0.y + 3.0f * f * ( 1.0f - f ) * ( 1.0f - f ) * oPos1.y + 3.0f * f * f * ( 1.0f - f ) * oGui0.y + f * f * oGui1.y );

		if ( !( oOld.x == oPos.x && oOld.y == oPos.y ) )
		{
			CDrawModify::Draw( oPos );
			oOld = oPos;
		}
	}
}

VOID CSpBezier4::OnDown( const CPoint2& oPos )
{
	if ( IsSamePosition( oPos ) )
	{
		m_bAddGuidePos = TRUE;
		Drawing( TRUE );
		Line();
		DrawGuide();
		Paint();
		UpdateVector( oPos );
		Paint();
		DrawGuide();
		Line();
	}
	else
	{
		if ( GetSizeVector() >= m_nPoint )
		{
			Drawing( TRUE );
			Line();
			DrawGuide();
			Paint();
			Drawing( FALSE );
			Paint();

			ClearVector();
			m_bAddGuidePos = FALSE;
		}

		
		CPoint2 oGuidePos = oPos;
		if ( oGuidePos.y < ( m_pMemory->GetHeight() >> 1 ) )	oGuidePos.y += 100;
		else													oGuidePos.y -= 100;

		Drawing( TRUE );
		if ( GetSizeVector() )
		{
			Line();
		}

		SetVector( oPos );
		SetVector( oGuidePos );

		Paint();
		DrawGuide( oPos );
		DrawGuide( oGuidePos );
		Line();
	}
}

VOID CSpBezier4::OnMove( const CPoint2& oPos )
{
	Line();
	DrawGuide();
	Paint();
	
	if( m_bAddGuidePos == FALSE ) 
	{
		CPoint2 oGuidePos = oPos;
		if ( oGuidePos.y < ( m_pMemory->GetHeight() >> 1 ) )	oGuidePos.y += 100;
		else													oGuidePos.y -= 100;
		UpdateVector( oGuidePos );
		m_riter++;
		UpdateVector( oPos );
		m_riter--;
	}
	else
	{
		UpdateVector( oPos );
	}

	Paint();
	DrawGuide();
	Line();
}

VOID CSpBezier4::OnUp( const CPoint2& oPos )
{
	Drawing( FALSE );
	m_bAddGuidePos = FALSE;
}
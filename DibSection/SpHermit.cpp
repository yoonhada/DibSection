#include "stdafx.h"
#include "SpHermit.h"

CSpHermit::CSpHermit( CMemory * pMemory )
: CDrawModify( pMemory, 4 )
{
}

CSpHermit::~CSpHermit()
{
}

VOID CSpHermit::Clear()
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

VOID CSpHermit::Paint()
{
	if ( GetSizeVector() <= 2 )
	{
		return;
	}

	CPoint2 oPos0 = GetVector( 0 );
	CPoint2 oGui0 = GetVector( 1 );
	CPoint2 oPos1 = GetVector( 2 );
	CPoint2 oGui1 = GetVector( 3 );
	CPoint2 oOld, oPos = oPos0;

	FLOAT f3, f2;
	for ( FLOAT f = 0.0f; f < 1.0f; f += 0.001f )
	{
		f3 = f * f * f;
		f2 = f * f;
		
		oPos.x = static_cast<INT>( ( 2.0f * f3 - 3.0f * f2 + 1 ) * oPos0.x + ( -2.0f * f3 + 3.0f * f2 ) * oPos1.x + ( f3 - 2.0f * f2 + f ) * oGui0.x + ( f3 - 1.0f * f2 ) * oGui1.x );
		oPos.y = static_cast<INT>( ( 2.0f * f3 - 3.0f * f2 + 1 ) * oPos0.y + ( -2.0f * f3 + 3.0f * f2 ) * oPos1.y + ( f3 - 2.0f * f2 + f ) * oGui0.y + ( f3 - 1.0f * f2 ) * oGui1.y );

		if ( !( oOld.x == oPos.x && oOld.y == oPos.y ) )
		{
			CDrawModify::Draw( oPos );
			oOld = oPos;
		}
	}
}

VOID CSpHermit::OnDown( const CPoint2& oPos )
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

VOID CSpHermit::OnMove( const CPoint2& oPos )
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

VOID CSpHermit::OnUp( const CPoint2& oPos )
{
	Drawing( FALSE );
	m_bAddGuidePos = FALSE;
}
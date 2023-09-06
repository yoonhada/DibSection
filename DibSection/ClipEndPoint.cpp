#include "stdafx.h"
#include "ClipEndPoint.h"

CClipEndPoint::CClipEndPoint( CMemory * pMemory )
: CDrawModify( pMemory, 4 )
{
}

CClipEndPoint::~CClipEndPoint()
{
}

VOID CClipEndPoint::Clear()
{
	if ( GetSizeVector() < 2 )	{ return; }

	Drawing( TRUE );
	DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	if ( GetSizeVector() == 2 )		{ DrawGuide(); }
	Drawing( FALSE );
	ClearVector();
}

VOID CClipEndPoint::Paint()
{
	m_vectorRECT[0] = GetVector( 0 );
	m_vectorRECT[1] = GetVector( 1 );
	CPoint2 oPosS = GetVector( 2 );
	CPoint2 oPosE = GetVector( 3 );

	Line( oPosS, oPosE, FALSE );

	m_vectorRECT[0] = CPoint2( 0, 0 );
	m_vectorRECT[1] = CPoint2( m_pMemory->GetWidth(), m_pMemory->GetHeight() );
}

VOID CClipEndPoint::OnDown( const CPoint2& oPos )
{
	int nSize = GetSizeVector();

	Drawing( TRUE );

	if ( nSize == 0 )		
	{
		SetVector( oPos );
		SetVector( oPos );

		DrawGuide();
		DrawGuide( oPos, oPos );
	}
	else if ( nSize == 2 )	
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();

		if ( IsSamePosition( oPos ) )
		{
			UpdateVector( oPos );
			DrawGuide();
			DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		}
		else
		{
			DrawGuide( GetVector( 0 ), GetVector( 1 ) );

			SetVector( oPos );
			SetVector( oPos );
			Paint();
		}

	}
	else if ( nSize == 4 )
	{
		m_listVector.pop_back();
		m_listVector.pop_back();
		SetVector( oPos );
		SetVector( oPos );
		Paint();
	}
}

VOID CClipEndPoint::OnMove( const CPoint2& oPos )
{
	int nSize = GetSizeVector();

	if ( nSize == 2 )			
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();
		UpdateVector( oPos );
		DrawGuide();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	}
	else if ( nSize == 4 )
	{
		Paint();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		UpdateVector( oPos );
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		Paint();
	}
}

VOID CClipEndPoint::OnUp( const CPoint2& oPos )
{
	int nSize = GetSizeVector();
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );

	if ( nSize == 2 )
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();
		INT nSwap;
		if( oPosLT.x > oPosRB.x )
		{
			nSwap = oPosLT.x;
			oPosLT.x = oPosRB.x;
			oPosRB.x = nSwap;
		}
		if( oPosLT.y > oPosRB.y )
		{
			nSwap = oPosLT.y;
			oPosLT.y = oPosRB.y;
			oPosRB.y = nSwap;
		}
		m_listVector.pop_front();
		m_listVector.pop_front();
		m_listVector.push_front( oPosRB );
		m_listVector.push_front( oPosLT );

		DrawGuide();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	}
	else if ( nSize == 4 )
	{
		Paint();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		UpdateVector( oPos );
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );

		Drawing( FALSE );
		Paint();
	}
}
#include "stdafx.h"
#include "ClipParametric.h"

CClipParametric::CClipParametric( CMemory * pMemory )
: CDrawModify( pMemory, 4 )
{
}

CClipParametric::~CClipParametric()
{
}

VOID CClipParametric::Clear()
{
	if ( GetSizeVector() < 2 )	{ return; }

	Drawing( TRUE );
	DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	if ( GetSizeVector() == 2 )		{ DrawGuide(); }
	Drawing( FALSE );
	ClearVector();
}

VOID CClipParametric::Paint()
{
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );
	CPoint2 oPosS  = GetVector( 2 );
	CPoint2 oPosE  = GetVector( 3 );
	INT nDeltaX = oPosE.x - oPosS.x;
	INT nDeltaY = oPosE.y - oPosS.y;
	FLOAT tE = 0.0f;
	FLOAT tL = 1.0f;

	BOOL bVisible = FALSE;
	if ( nDeltaX == 0 && nDeltaY == 0 && ClipPoint( oPosS ) )
	{
		bVisible = TRUE;
	}
	else
	{
		if ( CLIPt( nDeltaX, oPosLT.x - oPosS.x, tE, tL ) )
		{
			if ( CLIPt( -nDeltaX, oPosS.x - oPosRB.x, tE, tL ) )
			{
				if ( CLIPt( nDeltaY, oPosLT.y - oPosS.y, tE, tL ) )
				{
					if ( CLIPt( -nDeltaY, oPosS.y - oPosRB.y, tE, tL ) )
					{
						bVisible = TRUE;

						if ( tL < 1.0f )
						{
							oPosE.x = oPosS.x + static_cast<INT>( tL * nDeltaX );
							oPosE.y = oPosS.y + static_cast<INT>( tL * nDeltaY );
						}

						if ( tE > 0.0f )
						{
							oPosS.x += static_cast<INT>( tE * nDeltaX );
							oPosS.y += static_cast<INT>( tE * nDeltaY );
						}
					}
				}
			}
		}
	}

	if ( bVisible )
		Line( oPosS, oPosE, FALSE );
}

VOID CClipParametric::OnDown( const CPoint2& oPos )
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

VOID CClipParametric::OnMove( const CPoint2& oPos )
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

VOID CClipParametric::OnUp( const CPoint2& oPos )
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

BOOL CClipParametric::ClipPoint( const CPoint2& oPos )
{
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );

	if( oPosLT.x < oPos.x && oPos.x < oPosRB.x && 
		oPosLT.y < oPos.y && oPos.y < oPosRB.y )
		return TRUE;

	return FALSE;
}

BOOL CClipParametric::CLIPt( INT nDenom, INT nNum, FLOAT & tE, FLOAT & tL )
{
	FLOAT t = 0.0f;

	if ( nDenom > 0 )
	{
		t = static_cast<FLOAT>( nNum ) / static_cast<FLOAT>( nDenom );
		if ( t > tL )			return FALSE; 
		else if ( t > tE )		tE = t;
	}
	else if ( nDenom < 0 )
	{
		t = static_cast<FLOAT>( nNum ) / static_cast<FLOAT>( nDenom );
		if ( t < tE )			return FALSE;
		else if ( t < tL )		tL = t;
	}
	else
	{
		if ( nNum > 0 )			return FALSE;
	}

	return TRUE;
}
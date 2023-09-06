#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle( CMemory * pMemory )
: CDrawModify( pMemory, 3 )
{
}

CTriangle::~CTriangle()
{
}

VOID CTriangle::Clear()
{
	Drawing( TRUE );
	DrawGuide();
	Paint();
	Drawing( FALSE );
	Paint();

	ClearVector();
	m_bAddGuidePos = FALSE;
}

VOID CTriangle::Paint()
{
	if ( GetSizeVector() == 3 )
	{
		CPoint2 oPos[3];
		oPos[TOP] = GetVector( 0 );
		oPos[MID] = GetVector( 1 );
		oPos[BOT] = GetVector( 2 );

		Line( oPos[TOP], oPos[MID], FALSE );
		Line( oPos[MID], oPos[BOT], FALSE );
		Line( oPos[BOT], oPos[TOP], FALSE );
	}
}

VOID CTriangle::OnDown( const CPoint2& oPos )
{
	Drawing( TRUE );
	DrawGuide();
	Paint();

	if ( IsSamePosition( oPos ) )
	{
		UpdateVector( oPos );
		Paint();
		DrawGuide();
	}
	else
	{
		if ( GetSizeVector() >= m_nPoint )
		{
			Drawing( FALSE );
			Paint();

			ClearVector();
			Drawing( TRUE );
		}

		SetVector( oPos );
		Paint();
		DrawGuide();
	}
}

VOID CTriangle::SortTri( CPoint2 * oPos )
{
	if ( oPos[TOP].y < oPos[MID].y && oPos[TOP].y < oPos[BOT].y )
	{
		if ( oPos[MID].y > oPos[BOT].y )		
			Swap( oPos[MID], oPos[BOT] );
	}
	else if ( oPos[MID].y < oPos[TOP].y && oPos[MID].y < oPos[BOT].y )
	{
		Swap( oPos[MID], oPos[TOP] );		
		if ( oPos[MID].y > oPos[BOT].y )		
			Swap( oPos[MID], oPos[BOT] );	
	}
	else if ( oPos[BOT].y < oPos[TOP].y && oPos[BOT].y < oPos[MID].y )
	{
		Swap( oPos[BOT], oPos[TOP] );		
		if ( oPos[MID].y > oPos[BOT].y )		
			Swap( oPos[MID], oPos[BOT] );	
	}
}

VOID CTriangle::Swap( CPoint2 & lhv, CPoint2 & rhv )
{
	m_oTemp = lhv;
	lhv = rhv;
	rhv = m_oTemp;
}
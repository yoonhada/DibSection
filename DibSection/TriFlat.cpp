#include "stdafx.h"
#include "Triangle.h"
#include "TriFlat.h"

CTriFlat::CTriFlat( CMemory * pMemory )
: CTriangle( pMemory )
{
}

CTriFlat::~CTriFlat()
{
}

VOID CTriFlat::Paint()
{
	if ( GetSizeVector() == 3 )
	{
		INT nDelta[3], nVolatility[3];
		CPoint2 oPos[3], oPosS, oPosE;
		oPos[TOP] = GetVector( 0 );
		oPos[MID] = GetVector( 1 );
		oPos[BOT] = GetVector( 2 );

		SortTri( oPos );
		nVolatility[TOP2MID] = nVolatility[TOP2BOT] = nVolatility[MID2BOT] = 0;
		nDelta[TOP2MID] = nDelta[TOP2BOT] = nDelta[MID2BOT] = 0;
		oPosS = oPosE = oPos[TOP];

		if ( oPos[MID].y != oPos[TOP].y )		nDelta[TOP2MID] = ( ( oPos[MID].x - oPos[TOP].x ) << 16 ) / ( oPos[MID].y - oPos[TOP].y );
		if ( oPos[BOT].y != oPos[TOP].y )		nDelta[TOP2BOT] = ( ( oPos[BOT].x - oPos[TOP].x ) << 16 ) / ( oPos[BOT].y - oPos[TOP].y );
		if ( oPos[MID].y != oPos[BOT].y )		nDelta[MID2BOT] = ( ( oPos[BOT].x - oPos[MID].x ) << 16 ) / ( oPos[BOT].y - oPos[MID].y );

		for ( int i = oPos[TOP].y; i < oPos[BOT].y; ++i )
		{
			if ( i < oPos[MID].y )
			{
				nVolatility[TOP2MID] += nDelta[TOP2MID];
				oPosS.x = ( 0x8000 + ( oPos[TOP].x << 16 ) + nVolatility[TOP2MID] ) >> 16;
			}
			else
			{
				nVolatility[MID2BOT] += nDelta[MID2BOT];
				oPosS.x = ( 0x8000 + ( oPos[MID].x << 16 ) + nVolatility[MID2BOT] ) >> 16;
			}
			oPosS.y += 1;

			nVolatility[TOP2BOT] += nDelta[TOP2BOT];
			oPosE.x = ( 0x8000 + ( oPos[TOP].x << 16 ) + nVolatility[TOP2BOT] ) >> 16;
			oPosE.y += 1;

			Line( oPosS, oPosE, FALSE );
		}
	}
}

VOID CTriFlat::OnDown( const CPoint2& oPos )
{
	Drawing( TRUE );
	DrawGuide();
	Paint();

	if ( IsSamePosition( oPos ) )
	{
		UpdateVector( oPos );
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
		DrawGuide();
	}

}

VOID CTriFlat::OnMove( const CPoint2& oPos )
{
	DrawGuide();
	UpdateVector( oPos );
	DrawGuide();
}

VOID CTriFlat::OnUp( const CPoint2& oPos )
{
	DrawGuide();
	UpdateVector( oPos );
	Paint();
	DrawGuide();
	Drawing( FALSE );
}
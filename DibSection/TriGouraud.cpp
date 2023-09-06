#include "stdafx.h"
#include "Triangle.h"
#include "TriGouraud.h"

CTriGouraud::CTriGouraud( CMemory * pMemory )
: CTriangle( pMemory )
{
}

CTriGouraud::~CTriGouraud()
{
}

VOID CTriGouraud::Paint()
{
	if ( GetSizeVector() == 3 )
	{
		INT nDelta[3], nVolatility[3], nColDelta[3][3], nColVol[3][3];
		CPoint2 oPos[3], oPosS, oPosE;
		oPos[TOP] = GetVector( 0 );
		oPos[MID] = GetVector( 1 );
		oPos[BOT] = GetVector( 2 );

		SortTri( oPos );
		nVolatility[TOP2MID] = nVolatility[TOP2BOT] = nVolatility[MID2BOT] = 0;
		nDelta[TOP2MID] = nDelta[TOP2BOT] = nDelta[MID2BOT] = 0;
		oPosS = oPosE = oPos[TOP];

		nColDelta[TOP2MID][RE] = nColDelta[TOP2MID][GR] = nColDelta[TOP2MID][BL] = 0;
		nColDelta[TOP2BOT][RE] = nColDelta[TOP2BOT][GR] = nColDelta[TOP2BOT][BL] = 0;
		nColDelta[MID2BOT][RE] = nColDelta[MID2BOT][GR] = nColDelta[MID2BOT][BL] = 0;
		nColVol[TOP2MID][RE] = nColVol[TOP2MID][GR] = nColVol[TOP2MID][BL] = 0;
		nColVol[TOP2BOT][RE] = nColVol[TOP2BOT][GR] = nColVol[TOP2BOT][BL] = 0;
		nColVol[MID2BOT][RE] = nColVol[MID2BOT][GR] = nColVol[MID2BOT][BL] = 0;		

		nDelta[TOP2MID] = oPos[MID].y - oPos[TOP].y;
		if ( nDelta[TOP2MID] != 0 )
		{
			nColDelta[TOP2MID][RE] = ( ( oPos[MID].fr - oPos[TOP].fr ) << 16 ) / nDelta[TOP2MID];
			nColDelta[TOP2MID][GR] = ( ( oPos[MID].fg - oPos[TOP].fg ) << 16 ) / nDelta[TOP2MID];
			nColDelta[TOP2MID][BL] = ( ( oPos[MID].fb - oPos[TOP].fb ) << 16 ) / nDelta[TOP2MID];
			nDelta[TOP2MID] = ( ( oPos[MID].x - oPos[TOP].x ) << 16 ) / nDelta[TOP2MID];
		}

		nDelta[TOP2BOT] = oPos[BOT].y - oPos[TOP].y;
		if ( nDelta[TOP2BOT] != 0 )
		{
			nColDelta[TOP2BOT][RE] = ( ( oPos[BOT].fr - oPos[TOP].fr ) << 16 ) / nDelta[TOP2BOT];
			nColDelta[TOP2BOT][GR] = ( ( oPos[BOT].fg - oPos[TOP].fg ) << 16 ) / nDelta[TOP2BOT];
			nColDelta[TOP2BOT][BL] = ( ( oPos[BOT].fb - oPos[TOP].fb ) << 16 ) / nDelta[TOP2BOT];
			nDelta[TOP2BOT] = ( ( oPos[BOT].x - oPos[TOP].x ) << 16 ) / nDelta[TOP2BOT];
		}

		nDelta[MID2BOT] = oPos[BOT].y - oPos[MID].y;
		if ( nDelta[MID2BOT] != 0 )
		{
			nColDelta[MID2BOT][RE] = ( ( oPos[BOT].fr - oPos[MID].fr ) << 16 ) / nDelta[MID2BOT];
			nColDelta[MID2BOT][GR] = ( ( oPos[BOT].fg - oPos[MID].fg ) << 16 ) / nDelta[MID2BOT];
			nColDelta[MID2BOT][BL] = ( ( oPos[BOT].fb - oPos[MID].fb ) << 16 ) / nDelta[MID2BOT];
			nDelta[MID2BOT] = ( ( oPos[BOT].x - oPos[MID].x ) << 16 ) / nDelta[MID2BOT];
		}

		for ( int i = oPos[TOP].y; i < oPos[BOT].y; ++i )
		{
			if ( i < oPos[MID].y )
			{
				nVolatility[TOP2MID] += nDelta[TOP2MID];
				oPosS.x = ( 0x8000 + ( oPos[TOP].x << 16 ) + nVolatility[TOP2MID] ) >> 16;

				nColVol[TOP2MID][RE] += nColDelta[TOP2MID][RE];
				oPosS.fr = ( 0x8000 + ( oPos[TOP].fr << 16 ) + nColVol[TOP2MID][RE] ) >> 16;
				nColVol[TOP2MID][GR] += nColDelta[TOP2MID][GR];
				oPosS.fg = ( 0x8000 + ( oPos[TOP].fg << 16 ) + nColVol[TOP2MID][GR] ) >> 16;
				nColVol[TOP2MID][BL] += nColDelta[TOP2MID][BL];
				oPosS.fb = ( 0x8000 + ( oPos[TOP].fb << 16 ) + nColVol[TOP2MID][BL] ) >> 16;
			}
			else
			{
				nVolatility[MID2BOT] += nDelta[MID2BOT];
				oPosS.x = ( 0x8000 + ( oPos[MID].x << 16 ) + nVolatility[MID2BOT] ) >> 16;

				nColVol[MID2BOT][RE] += nColDelta[MID2BOT][RE];
				oPosS.fr = ( 0x8000 + ( oPos[MID].fr << 16 ) + nColVol[MID2BOT][RE] ) >> 16;
				nColVol[MID2BOT][GR] += nColDelta[MID2BOT][GR];
				oPosS.fg = ( 0x8000 + ( oPos[MID].fg << 16 ) + nColVol[MID2BOT][GR] ) >> 16;
				nColVol[MID2BOT][BL] += nColDelta[MID2BOT][BL];
				oPosS.fb = ( 0x8000 + ( oPos[MID].fb << 16 ) + nColVol[MID2BOT][BL] ) >> 16;
			}
			oPosS.y += 1;

			nVolatility[TOP2BOT] += nDelta[TOP2BOT];
			oPosE.x = ( 0x8000 + ( oPos[TOP].x << 16 ) + nVolatility[TOP2BOT] ) >> 16;

			nColVol[TOP2BOT][RE] += nColDelta[TOP2BOT][RE];
			oPosE.fr = ( 0x8000 + ( oPos[TOP].fr << 16 ) + nColVol[TOP2BOT][RE] ) >> 16;
			nColVol[TOP2BOT][GR] += nColDelta[TOP2BOT][GR];
			oPosE.fg = ( 0x8000 + ( oPos[TOP].fg << 16 ) + nColVol[TOP2BOT][GR] ) >> 16;
			nColVol[TOP2BOT][BL] += nColDelta[TOP2BOT][BL];
			oPosE.fb = ( 0x8000 + ( oPos[TOP].fb << 16 ) + nColVol[TOP2BOT][BL] ) >> 16;

			oPosE.y += 1;

			LineRate( oPosS, oPosE );
		}
	}
}

VOID CTriGouraud::OnDown( const CPoint2& oPos )
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
		CPoint2 obj = oPos;
		if ( GetSizeVector() == 0 && oPos.GetColor(0) == RGB( 255, 255, 255 ) )		obj.SetColor( RGB( 255, 0, 0 ) );
		if ( GetSizeVector() == 1 && oPos.GetColor(0) == RGB( 255, 255, 255 ) )		obj.SetColor( RGB( 0, 255, 0 ) );
		if ( GetSizeVector() == 2 && oPos.GetColor(0) == RGB( 255, 255, 255 ) )		obj.SetColor( RGB( 0, 0, 255 ) );

		if ( GetSizeVector() >= m_nPoint )
		{
			Drawing( FALSE );
			Paint();

			ClearVector();
			Drawing( TRUE );
		}

		SetVector( obj );
		DrawGuide();
	}

}

VOID CTriGouraud::OnMove( const CPoint2& oPos )
{
	DrawGuide();
	UpdateVector( oPos );
	DrawGuide();
}

VOID CTriGouraud::OnUp( const CPoint2& oPos )
{
	DrawGuide();
	UpdateVector( oPos );
	Paint();
	DrawGuide();
	Drawing( FALSE );
}

#include "stdafx.h"
#include "LineMLA.h"

CLineMLA::CLineMLA( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CLineMLA::~CLineMLA()
{
}

VOID CLineMLA::Paint()
{
	CPoint2 oPos = GetVector( 0 );

	INT nDeltaX = GetVector( 1 ).x - oPos.x;
	INT nDeltaY = GetVector( 1 ).y - oPos.y;
	INT nStepX = ( nDeltaX < 0 ) ? -1 : 1;
	INT nStepY = ( nDeltaY < 0 ) ? -1 : 1;
	
	INT nD, nIncrE, nIncrNE;

	nDeltaX = abs( nDeltaX );
	nDeltaY = abs( nDeltaY );

	if ( nDeltaX > nDeltaY ) 
	{
		nIncrE = nDeltaY << 1;
		nIncrNE = ( nDeltaY - nDeltaX ) << 1;
		nD = ( nDeltaY << 1 ) - nDeltaX;

		for ( int i = 0; i < nDeltaX; ++i )		//while( oPos.x != nEndX )
		{
			oPos.x += nStepX;
			if( nD <= 0 )
			{
				nD += nIncrE;
			}
			else
			{
				nD += nIncrNE;
				oPos.y += nStepY;
			}

			CDrawPixel::Draw( oPos );
		}
	}
	else
	{
		nIncrE = nDeltaX << 1;
		nIncrNE = ( nDeltaX - nDeltaY ) << 1;
		nD = ( nDeltaX << 1 ) - nDeltaY;

		for ( int i = 0; i < nDeltaY; ++i )		//		while( oPos.y != nEndY )
		{
			oPos.y += nStepY;
			if( nD <= 0 )
			{
				nD += nIncrE;
			}
			else
			{
				nD += nIncrNE;
				oPos.x += nStepX;
			}

			CDrawPixel::Draw( oPos );
		}
	}
}

#include "stdafx.h"
#include "LineDSA.h"

CLineDSA::CLineDSA( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CLineDSA::~CLineDSA()
{
}

VOID CLineDSA::Paint()
{
	CPoint2 oPos = GetVector( 0 );

	INT nDeltaX = GetVector( 1 ).x - oPos.x;
	INT nDeltaY = GetVector( 1 ).y - oPos.y;
	INT nStepX = ( nDeltaX < 0 ) ? -1 : 1;
	INT nStepY = ( nDeltaY < 0 ) ? -1 : 1;

	nDeltaX = abs( nDeltaX );
	nDeltaY = abs( nDeltaY );

	if ( nDeltaX > nDeltaY ) 
	{
		INT nDicision, nInc1, nInc2, nCoud;
		nInc2 = ( ( nDeltaY << 1 ) - nDeltaX ) << 1;

		if ( nInc2 < 0 )
		{
			nDicision = ( nDeltaY << 2 ) - nDeltaX;
			nCoud = nDeltaY << 1;
			nInc1 = nDeltaY << 2;

			for ( INT i = 0; i < nDeltaX; i += 2 )
			{
				if( nDicision < 0 )
				{
					oPos.x += nStepX; CDrawPixel::Draw( oPos );
					oPos.x += nStepX; CDrawPixel::Draw( oPos );
					nDicision += nInc1;
				}
				else
				{
					if ( nDicision < nCoud )
					{
						oPos.x += nStepX; CDrawPixel::Draw( oPos );
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					else
					{
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.x += nStepX; CDrawPixel::Draw( oPos );
					}
					nDicision += nInc2;
				}
			}
		}
		else
		{
			nDicision = ( ( ( nDeltaY - nDeltaX ) << 1 ) << 1 ) + 1;
			nCoud = ( nDeltaY - nDeltaX ) << 1;
			nInc1 = ( ( nDeltaY - nDeltaX ) << 1 ) << 1;

			for ( INT i = 0; i < nDeltaX; i += 2 )
			{
				if( nDicision > 0 )
				{
					oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					nDicision += nInc1;
				}
				else
				{
					if ( nDicision < nCoud )
					{
						oPos.x += nStepX; CDrawPixel::Draw( oPos );
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					else
					{
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.x += nStepX; CDrawPixel::Draw( oPos );
					}
					nDicision += nInc2;
				}
			}
		}
	}
	else
	{
		INT nDicision, nInc1, nInc2, nCoud;
		nInc2 = ( ( nDeltaX << 1 ) - nDeltaY ) << 1;

		if ( nInc2 < 0 )
		{
			nDicision = ( nDeltaX << 2 ) - nDeltaY;
			nCoud = nDeltaX << 1;
			nInc1 = nDeltaX << 2;

			for ( INT i = 0; i < nDeltaY; i += 2 )
			{
				if( nDicision < 0 )
				{
					oPos.y += nStepY; CDrawPixel::Draw( oPos );
					oPos.y += nStepY; CDrawPixel::Draw( oPos );
					nDicision += nInc1;
				}
				else
				{
					if ( nDicision < nCoud )
					{
						oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					else
					{
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					nDicision += nInc2;
				}
			}
		}
		else
		{
			nDicision = ( ( ( nDeltaX - nDeltaY ) << 1 ) << 1 ) + 1;
			nCoud = ( nDeltaX - nDeltaY ) << 1;
			nInc1 = ( ( nDeltaX - nDeltaY ) << 1 ) << 1;

			for ( INT i = 0; i < nDeltaX; i += 2 )
			{
				if( nDicision > 0 )
				{
					oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					nDicision += nInc1;
				}
				else
				{
					if ( nDicision < nCoud )
					{
						oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					else
					{
						oPos.x += nStepX, oPos.y += nStepY; CDrawPixel::Draw( oPos );
						oPos.y += nStepY; CDrawPixel::Draw( oPos );
					}
					nDicision += nInc2;
				}
			}
		}
	}
}

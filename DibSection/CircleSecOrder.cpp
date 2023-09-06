#include "stdafx.h"
#include "CircleSecOrder.h"

CCircleSecOrder::CCircleSecOrder( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CCircleSecOrder::~CCircleSecOrder(void)
{
}

VOID CCircleSecOrder::Paint()
{
	const FLOAT PI = 3.14159265f;
	const FLOAT fDegree = PI / 180.0f;

	CPoint2 oPosCenter = GetVector( 0 );
	CPoint2 oPos = GetVector( 1 );

	INT nDeltaX = oPos.x - oPosCenter.x;
	INT nDeltaY = oPos.y - oPosCenter.y;

	FLOAT fRadius = sqrt(static_cast<FLOAT>( nDeltaX * nDeltaX + nDeltaY * nDeltaY ) );

	if ( fRadius > 0.0f )
	{
		INT nIncrX, nIncrY;
		nIncrX = 0;
		nIncrY = static_cast<INT>( fRadius );
		
		INT nDecision = static_cast<INT>( 1.25f - fRadius );
		INT nE = 3;
		INT nSE = static_cast<INT>( -2 * fRadius + 5 );

		while ( nIncrX <= nIncrY )
		{
			oPos.x = oPosCenter.x + nIncrX; oPos.y = oPosCenter.y + nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrY; oPos.y = oPosCenter.y + nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrY; oPos.y = oPosCenter.y - nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrX; oPos.y = oPosCenter.y - nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrX; oPos.y = oPosCenter.y - nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrY; oPos.y = oPosCenter.y - nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrX; oPos.y = oPosCenter.y + nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrY; oPos.y = oPosCenter.y + nIncrX; CDrawPixel::Draw( oPos );

			nE += 2;
			nIncrX++;

			if ( nDecision <= 0 )
			{
				nDecision += nE;
				nSE += 2;
			}
			else
			{
				nDecision += nSE;
				nSE += 4;
				nIncrY--;
			}
		}
	}
}
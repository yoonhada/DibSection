#include "stdafx.h"
#include "CircleMidP.h"

CCircleMidP::CCircleMidP( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CCircleMidP::~CCircleMidP(void)
{
}

VOID CCircleMidP::Paint()
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

			nIncrX++;

			if ( nDecision <= 0 )
			{
				nDecision = nDecision + ( nIncrX << 1 ) + 3;
			}
			else
			{
				nIncrY--;
				nDecision = nDecision + ( ( nIncrX - nIncrY ) << 1 ) + 5;
			}
		}
	}
}
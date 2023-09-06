#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CCircle::~CCircle(void)
{
}

VOID CCircle::Paint()
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
		FLOAT fCount = 180.0f / ( PI * fRadius );		
		for ( FLOAT i = 0.0f; i < 45.0f; i += fCount )
		{
			nIncrX = static_cast<INT>( fRadius * cos( i * fDegree ) );
			nIncrY = static_cast<INT>( fRadius * sin( i * fDegree ) );
			
			oPos.x = oPosCenter.x + nIncrX; oPos.y = oPosCenter.y + nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrY; oPos.y = oPosCenter.y + nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrY; oPos.y = oPosCenter.y - nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x + nIncrX; oPos.y = oPosCenter.y - nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrX; oPos.y = oPosCenter.y - nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrY; oPos.y = oPosCenter.y - nIncrX; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrX; oPos.y = oPosCenter.y + nIncrY; CDrawPixel::Draw( oPos );
			oPos.x = oPosCenter.x - nIncrY; oPos.y = oPosCenter.y + nIncrX; CDrawPixel::Draw( oPos );
		}
	}
}
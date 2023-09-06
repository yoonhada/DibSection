#include "stdafx.h"
#include "LineDDA.h"

CLineDDA::CLineDDA( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CLineDDA::~CLineDDA()
{
}

VOID CLineDDA::Paint()
{
	CPoint2 oPos = GetVector( 0 );

	INT nDeltaX = GetVector( 1 ).x - oPos.x;
	INT nDeltaY = GetVector( 1 ).y - oPos.y;
	INT nStepX = ( nDeltaX < 0 ) ? -1 : 1;
	INT nStepY = ( nDeltaY < 0 ) ? -1 : 1;

	FLOAT t = 0.5f;
	FLOAT fMomentum;
	if ( abs( nDeltaX ) > abs( nDeltaY ) ) 
	{
		fMomentum = ( FLOAT )nDeltaY / ( FLOAT )nDeltaX;
		t += oPos.y;
		fMomentum *= nStepX;
		
		for (INT i = 0; i < abs(nDeltaX); ++i )
		{
			oPos.x += nStepX;
			t += fMomentum;
			
			oPos.y = static_cast< INT >( t );
			CDrawPixel::Draw( oPos );
		}
	}
	else
	{
		fMomentum = (float) nDeltaX / (float) nDeltaY;
		t += oPos.x;
		fMomentum *= nStepY;

		for (INT i = 0; i < abs(nDeltaY); ++i )
		{
			oPos.y += nStepY;
			t += fMomentum;

			oPos.x = static_cast< INT >( t );
			CDrawPixel::Draw( oPos );
		}
	}
}

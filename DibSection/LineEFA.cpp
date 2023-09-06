#include "stdafx.h"
#include "LineEFA.h"

CLineEFA::CLineEFA( CMemory * pMemory )
: CDrawPixel( pMemory, 2 )
{
}

CLineEFA::~CLineEFA()
{
}

VOID CLineEFA::Paint()
{
	CPoint2 oPos = GetVector( 0 );

	BOOL yLonger = FALSE;
	INT nLongLen = GetVector( 1 ).x - oPos.x;
	INT nShortLen = GetVector( 1 ).y - oPos.y;

	if ( abs( nShortLen ) > abs( nLongLen ) ) 
	{
		INT swap = nShortLen;
		nShortLen = nLongLen;
		nLongLen = swap;				
		yLonger = true;
	}

	INT nIncr;
	if ( nLongLen  ==  0 )	nIncr = 0;
	else					nIncr = ( nShortLen << 16 ) / nLongLen;

	if ( yLonger )
	{
		if ( nLongLen > 0 ) 
		{
			nLongLen += oPos.y;

			for ( INT i = 0x8000 + ( oPos.x << 16 ); oPos.y <= nLongLen; ++oPos.y ) 
			{
				oPos.x = i >> 16;
				CDrawPixel::Draw( oPos );
				i += nIncr;
			}
			return;
		}

		nLongLen += oPos.y;
		for ( INT i = 0x8000 + ( oPos.x << 16 ); oPos.y >= nLongLen; --oPos.y ) 
		{
			oPos.x = i >> 16;
			CDrawPixel::Draw( oPos );
			i -= nIncr;
		}

		return;
	}

	if ( nLongLen > 0 ) 
	{
		nLongLen += oPos.x;
		for ( INT i = 0x8000 + ( oPos.y << 16 ); oPos.x <= nLongLen; ++oPos.x ) 
		{
			oPos.y = i >> 16;
			CDrawPixel::Draw( oPos );
			i += nIncr;
		}

		return;
	}

	nLongLen += oPos.x;
	for ( INT i = 0x8000 + ( oPos.y << 16 ); oPos.x >= nLongLen; --oPos.x ) 
	{
		oPos.y = i >> 16;
		CDrawPixel::Draw( oPos );
		i -= nIncr;
	}

	return;
}

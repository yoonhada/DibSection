#include "stdafx.h"
#include "TriTexture.h"

CTriTexture::CTriTexture( CMemory * pMemory )
: CDrawModify( pMemory, 6 )
, m_bMove( FALSE )
{
}

CTriTexture::~CTriTexture()
{
}

VOID CTriTexture::Clear()
{
	if ( GetSizeVector() < 2 )	{ return; }

	Drawing( TRUE );
	DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	if ( GetSizeVector() == 2 )		{ DrawGuide(); }
	Drawing( FALSE );
	ClearVector();
}

VOID CTriTexture::Paint()
{
	CPoint2 oPosRect[4];
	
	oPosRect[0] = GetVector( 0 );
	oPosRect[1] = GetVector( 1 );
	oPosRect[2] = GetVector( 2 );
	oPosRect[3] = GetVector( 3 );

	if ( oPosRect[0].y <= oPosRect[1].y && oPosRect[0].y <= oPosRect[3].y)
	{
		if ( oPosRect[1].y <= oPosRect[3].y )	DrawTexture( oPosRect[0], oPosRect[1], oPosRect[3] );
		else									DrawTexture( oPosRect[0], oPosRect[3], oPosRect[1] );
	}
	else if ( oPosRect[1].y <= oPosRect[0].y && oPosRect[1].y <= oPosRect[3].y)
	{
		if ( oPosRect[0].y <= oPosRect[3].y )	DrawTexture( oPosRect[1], oPosRect[0], oPosRect[3] );
		else									DrawTexture( oPosRect[1], oPosRect[3], oPosRect[0] );
	}
	else if ( oPosRect[3].y <= oPosRect[0].y && oPosRect[3].y <= oPosRect[1].y)
	{
		if ( oPosRect[0].y <= oPosRect[1].y )	DrawTexture( oPosRect[3], oPosRect[0], oPosRect[1] );
		else									DrawTexture( oPosRect[3], oPosRect[1], oPosRect[0] );
	}

	if ( oPosRect[0].y <= oPosRect[2].y && oPosRect[0].y <= oPosRect[3].y)
	{
		if ( oPosRect[2].y <= oPosRect[3].y )	DrawTexture( oPosRect[0], oPosRect[2], oPosRect[3] );
		else									DrawTexture( oPosRect[0], oPosRect[3], oPosRect[2] );
	}
	else if ( oPosRect[2].y <= oPosRect[0].y && oPosRect[2].y <= oPosRect[3].y)
	{
		if ( oPosRect[0].y <= oPosRect[3].y )	DrawTexture( oPosRect[2], oPosRect[0], oPosRect[3] );
		else									DrawTexture( oPosRect[2], oPosRect[3], oPosRect[0] );
	}
	else if ( oPosRect[3].y <= oPosRect[0].y && oPosRect[3].y <= oPosRect[2].y)
	{
		if ( oPosRect[0].y <= oPosRect[2].y )	DrawTexture( oPosRect[3], oPosRect[0], oPosRect[2] );
		else									DrawTexture( oPosRect[3], oPosRect[2], oPosRect[0] );
	}
}

VOID CTriTexture::OnDown( const CPoint2& oPos )
{
	int nSize = GetSizeVector();

	m_bMove = FALSE;
	Drawing( TRUE );

	if ( IsSamePosition( oPos ) )
	{
		DrawGuide();
		Paint();
		UpdateVector( oPos );
		DrawGuide();
		DrawGuideLine();
	}
	else if ( nSize == 0 )		
	{
		SetVector( oPos );
		SetVector( oPos );
		DrawGuide();
		DrawGuide( oPos, oPos );

	}
	else if ( nSize == 4 )
	{
		m_bMove = TRUE;
		m_oMousePos = oPos;

		DrawGuide();
		Paint();
		DrawGuide();
		DrawGuideLine();
	}
}

VOID CTriTexture::OnMove( const CPoint2& oPos )
{
	int nSize = GetSizeVector();

	if ( nSize == 2 )			
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();
		UpdateVector( oPos );
		DrawGuide();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	}
	else if ( nSize == 4 && m_bMove == FALSE )
	{
		DrawGuideLine();
		DrawGuide();
		UpdateVector( oPos );
		DrawGuide();
		DrawGuideLine();
	}
	else
	{
		CPoint2 oP = oPos;
		oP.x -= m_oMousePos.x;
		oP.y -= m_oMousePos.y;
		m_oMousePos = oPos;

		DrawGuideLine();
		DrawGuide();
		MoveVector( oP );

		DrawGuide();
		DrawGuideLine();
	}
}

VOID CTriTexture::OnUp( const CPoint2& oPos )
{
	INT nSwap;
	INT nSize = GetSizeVector();
	CPoint2 oPosRect[4];
	oPosRect[0] = GetVector( 0 );
	oPosRect[1] = GetVector( 1 );

	if ( nSize == 4 )
	{
		DrawGuideLine();
		DrawGuide();
	}
	else if ( nSize == 2 )
	{
		DrawGuide( oPosRect[0], oPosRect[1] );
		DrawGuide();

		if( oPosRect[0].x > oPosRect[1].x )
		{
			nSwap = oPosRect[0].x;
			oPosRect[0].x = oPosRect[1].x;
			oPosRect[1].x = nSwap;
		}
		if( oPosRect[0].y > oPosRect[0].y )
		{
			nSwap = oPosRect[0].y;
			oPosRect[0].y = oPosRect[1].y;
			oPosRect[1].y = nSwap;
		}
		oPosRect[2] = oPosRect[0];
		oPosRect[3] = oPosRect[1];
		oPosRect[2].y = oPosRect[1].y;
		oPosRect[1].y = oPosRect[0].y;

		oPosRect[0].u = 0.0f;
		oPosRect[0].v = 0.0f;
		oPosRect[1].u = 1.0f;
		oPosRect[1].v = 0.0f;
		oPosRect[2].u = 0.0f;
		oPosRect[2].v = 1.0f;
		oPosRect[3].u = 1.0f;
		oPosRect[3].v = 1.0f;

		m_listVector.pop_front();
		m_listVector.pop_front();
		m_listVector.push_back( oPosRect[0] );
		m_listVector.push_back( oPosRect[1] );
		m_listVector.push_back( oPosRect[2] );
		m_listVector.push_back( oPosRect[3] );
	}
	Paint();
	DrawGuide();
	Drawing( FALSE );
}

VOID CTriTexture::DrawTexture( const CPoint2& oTop, const CPoint2& oMid, const CPoint2& oBot)
{
	CDrawBitmap * pBm = m_pMemory->GetDrawBit();
	BYTE * pImage = pBm->GetImages();
	INT nScanLine = GetBytePerScanLine( pBm->GetWidth() );

	INT nDelta[3], nVolatility[3];
	FLOAT fUVDelta[2][3], fUVVolatility[2][3];
	CPoint2 oPos, oPosS, oPosE;

	nVolatility[TOP2MID] = nVolatility[TOP2BOT] = nVolatility[MID2BOT] = 0;
	nDelta[TOP2MID] = nDelta[TOP2BOT] = nDelta[MID2BOT] = 0;
	oPos = oPosS = oPosE = oTop;

	if ( oMid.y != oTop.y )		nDelta[TOP2MID] = ( ( oMid.x - oTop.x ) << 16 ) / ( oMid.y - oTop.y );
	if ( oBot.y != oTop.y )		nDelta[TOP2BOT] = ( ( oBot.x - oTop.x ) << 16 ) / ( oBot.y - oTop.y );
	if ( oMid.y != oBot.y )		nDelta[MID2BOT] = ( ( oBot.x - oMid.x ) << 16 ) / ( oBot.y - oMid.y );
	
	INT nW = pBm->GetWidth();
	INT nH = pBm->GetHeight();

	fUVVolatility[0][TOP2MID] = fUVVolatility[0][TOP2BOT] = fUVVolatility[0][MID2BOT] = 0.0f;
	fUVVolatility[1][TOP2MID] = fUVVolatility[1][TOP2BOT] = fUVVolatility[1][MID2BOT] = 0.0f;
	fUVDelta[0][TOP2MID] = fUVDelta[0][TOP2BOT] = fUVDelta[0][MID2BOT] = 0.0f;
	fUVDelta[1][TOP2MID] = fUVDelta[1][TOP2BOT] = fUVDelta[1][MID2BOT] = 0.0f;

	if ( oMid.x != oTop.x )		fUVDelta[0][TOP2MID] = ( oMid.u - oTop.u ) / ( oMid.x - oTop.x );
	if ( oBot.x != oTop.x )		fUVDelta[0][TOP2BOT] = ( oBot.u - oTop.u ) / ( oBot.x - oTop.x );
	if ( oBot.x != oMid.x )		fUVDelta[0][MID2BOT] = ( oBot.u - oMid.u ) / ( oBot.x - oMid.x );
	if ( oMid.y != oTop.y )		fUVDelta[1][TOP2MID] = ( oMid.v - oTop.v ) / ( oMid.y - oTop.y );
	if ( oBot.y != oTop.y )		fUVDelta[1][TOP2BOT] = ( oBot.v - oTop.v ) / ( oBot.y - oTop.y );
	if ( oBot.y != oMid.y )		fUVDelta[1][MID2BOT] = ( oBot.v - oMid.v ) / ( oBot.y - oMid.y );
	
	FLOAT fDel, fVol;
	for (int i = oTop.y; i < oBot.y; ++i )
	{
		if ( i < oMid.y )
		{
			nVolatility[TOP2MID] += nDelta[TOP2MID];
			oPosS.x = ( 0x8000 + ( oTop.x << 16 ) + nVolatility[TOP2MID] ) >> 16;

			fUVVolatility[0][TOP2MID] += fUVDelta[0][TOP2MID];
			fUVVolatility[1][TOP2MID] += fUVDelta[1][TOP2MID];
			oPosS.u = oTop.u + fUVVolatility[0][TOP2MID];
			oPosS.v = oTop.v + fUVVolatility[1][TOP2MID];
		}
		else
		{
			nVolatility[MID2BOT] += nDelta[MID2BOT];
			oPosS.x = ( 0x8000 + ( oMid.x << 16 ) + nVolatility[MID2BOT] ) >> 16;

			fUVVolatility[0][MID2BOT] += fUVDelta[0][MID2BOT];
			fUVVolatility[1][MID2BOT] += fUVDelta[1][MID2BOT];
			oPosS.u = oMid.u + fUVVolatility[0][MID2BOT];
			oPosS.v = oMid.v + fUVVolatility[1][MID2BOT];
		}
		oPosS.y += 1;

		nVolatility[TOP2BOT] += nDelta[TOP2BOT];
		oPosE.x = ( 0x8000 + ( oTop.x << 16 ) + nVolatility[TOP2BOT] ) >> 16;

		fUVVolatility[0][TOP2BOT] += fUVDelta[0][TOP2BOT];
		fUVVolatility[1][TOP2BOT] += fUVDelta[1][TOP2BOT];
		oPosE.u = oTop.u + fUVVolatility[0][TOP2BOT];
		oPosE.v = oTop.v + fUVVolatility[1][TOP2BOT];

		oPosE.y += 1;

		if ( oPosS.x < oPosE.x )
		{
			fDel = ( oPosE.u - oPosS.u ) / ( oPosE.x - oPosS.x );
			fVol = 0.0f;
			for (int j = oPosS.x; j < oPosE.x; ++j )
			{
				fVol += fDel;
				oPos.u = oPosS.u + fVol;
				oPos.v = oPosS.v;

				oPos.x = j;
				oPos.y = i;
				oPos.fr = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u ) * 3 ) + 2 );
				oPos.fg = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u ) * 3 ) + 1 );
				oPos.fb = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u ) * 3 ) + 0 );
				Draw( oPos );
			}
		}
		else
		{
			fDel = ( oPosS.u - oPosE.u ) / ( oPosS.x - oPosE.x );
			fVol = 0.0f;
			for (int j = oPosE.x; j < oPosS.x; ++j )
			{
				fVol += fDel;
				oPos.u = oPosE.u + fVol;
				oPos.v = oPosE.v;

				oPos.x = j;
				oPos.y = i;
				oPos.fr = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u) * 3 ) + 2 );
				oPos.fg = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u) * 3 ) + 1 );
				oPos.fb = *( pImage + nScanLine * static_cast<INT>( nH * ( 1.0f - oPos.v ) ) + ( static_cast<INT>( nW * oPos.u) * 3 ) + 0 );
				Draw( oPos );
			}
		}
	}
}

VOID CTriTexture::DrawGuideLine( )
{
	CPoint2 oPoint[4];
	std::list < CPoint2 >::iterator It = m_listVector.begin();
	
	if ( m_listVector.size() < 4 )
		return;

	oPoint[0] = GetVector(0);
	oPoint[1] = GetVector(1);
	oPoint[2] = GetVector(2);
	oPoint[3] = GetVector(3);

	Line(oPoint[0], oPoint[1]);
	Line(oPoint[1], oPoint[3]);
	Line(oPoint[3], oPoint[2]);
	Line(oPoint[2], oPoint[0]);
}

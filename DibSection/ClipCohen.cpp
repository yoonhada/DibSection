#include "stdafx.h"
#include "ClipCohen.h"

CClipCohen::CClipCohen( CMemory * pMemory )
: CDrawModify( pMemory, 4 )
{
}

CClipCohen::~CClipCohen()
{
}

VOID CClipCohen::Clear()
{
	if ( GetSizeVector() < 2 )	{ return; }

	Drawing( TRUE );
	DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	if ( GetSizeVector() == 2 )		{ DrawGuide(); }
	Drawing( FALSE );
	ClearVector();
}

VOID CClipCohen::Paint()
{
	CPoint2 oPos;
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );
	CPoint2 oPosS  = GetVector( 2 );
	CPoint2 oPosE  = GetVector( 3 );

	INT nCode;
	INT nCodeS = GetOutCode( oPosS );
	INT nCodeE = GetOutCode( oPosE );
	BOOL bAccept = FALSE;

	while ( TRUE ) 
	{
		if ( !( nCodeS | nCodeE ) )
		{
			bAccept = TRUE;
			break;
		}  
		else if ( nCodeS & nCodeE ) 
		{
			break;
		} 
		else
		{
			oPos = oPosS;
			nCode = nCodeS ? nCodeS : nCodeE;

			if ( nCode & LEFT )
			{
				oPos.x = oPosLT.x;
				oPos.y = oPosS.y + ( oPosE.y - oPosS.y ) * ( oPosLT.x - oPosS.x ) / ( oPosE.x - oPosS.x );
			}
			else if ( nCode & TOP) 
			{
				oPos.x = oPosS.x + ( oPosE.x - oPosS.x ) * ( oPosLT.y - oPosS.y ) / ( oPosE.y - oPosS.y );
				oPos.y = oPosLT.y;
			}
			else if ( nCode & RIGHT ) 
			{
				oPos.x = oPosRB.x;
				oPos.y = oPosS.y + ( oPosE.y - oPosS.y ) * ( oPosRB.x - oPosS.x ) / ( oPosE.x - oPosS.x );
			} 
			else if ( nCode & BOTTOM )
			{
				oPos.x = oPosS.x + ( oPosE.x - oPosS.x ) * ( oPosRB.y - oPosS.y ) / ( oPosE.y - oPosS.y );
				oPos.y = oPosRB.y;
			}

			if ( nCode == nCodeS )
			{
				oPosS = oPos;
				nCodeS = GetOutCode( oPos );
			} 
			else 
			{
				oPosE = oPos;
				nCodeE = GetOutCode( oPos );
			}
		}
	}

	if ( bAccept )			{ Line( oPosS, oPosE, FALSE ); }
}

VOID CClipCohen::OnDown( const CPoint2& oPos )
{
	int nSize = GetSizeVector();

	Drawing( TRUE );

	if ( nSize == 0 )		
	{
		SetVector( oPos );
		SetVector( oPos );

		DrawGuide();
		DrawGuide( oPos, oPos );
	}
	else if ( nSize == 2 )	
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();

		if ( IsSamePosition( oPos ) )
		{
			UpdateVector( oPos );
			DrawGuide();
			DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		}
		else
		{
			DrawGuide( GetVector( 0 ), GetVector( 1 ) );

			SetVector( oPos );
			SetVector( oPos );
			Paint();
		}

	}
	else if ( nSize == 4 )
	{
		m_listVector.pop_back();
		m_listVector.pop_back();
		SetVector( oPos );
		SetVector( oPos );
		Paint();
	}
}

VOID CClipCohen::OnMove( const CPoint2& oPos )
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
	else if ( nSize == 4 )
	{
		Paint();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		UpdateVector( oPos );
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		Paint();
	}
}

VOID CClipCohen::OnUp( const CPoint2& oPos )
{	
	int nSize = GetSizeVector();
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );

	if ( nSize == 2 )
	{
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		DrawGuide();
		INT nSwap;
		if( oPosLT.x > oPosRB.x )
		{
			nSwap = oPosLT.x;
			oPosLT.x = oPosRB.x;
			oPosRB.x = nSwap;
		}
		if( oPosLT.y > oPosRB.y )
		{
			nSwap = oPosLT.y;
			oPosLT.y = oPosRB.y;
			oPosRB.y = nSwap;
		}
		m_listVector.pop_front();
		m_listVector.pop_front();
		m_listVector.push_front( oPosRB );
		m_listVector.push_front( oPosLT );

		DrawGuide();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
	}
	else if ( nSize == 4 )
	{
		Paint();
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );
		UpdateVector( oPos );
		DrawGuide( GetVector( 0 ), GetVector( 1 ) );

		Drawing( FALSE );
		Paint();
	}
}

BOOL CClipCohen::GetOutCode( const CPoint2& oPos )
{
	INT nRet = 0;
	CPoint2 oPosLT = GetVector( 0 );
	CPoint2 oPosRB = GetVector( 1 );

	if ( oPos.y < oPosLT.y )		{ nRet |= TOP;		 }
	if ( oPos.y > oPosRB.y )		{ nRet |= BOTTOM;	 }
	if ( oPos.x < oPosLT.x )		{ nRet |= LEFT;		 }
	if ( oPos.x > oPosRB.x )		{ nRet |= RIGHT;	 }

	return nRet;
}
#include "stdafx.h"
#include "TriNormal.h"

CTriNormal::CTriNormal( CMemory * pMemory )
: CDrawModify( pMemory, 3 )
{
}

CTriNormal::~CTriNormal()
{
}

VOID CTriNormal::Clear()
{
	Drawing( TRUE );
	DrawGuide();
	Paint();
	Drawing( FALSE );
	Paint();

	ClearVector();
	m_bAddGuidePos = FALSE;
}

VOID CTriNormal::Paint()
{
	if ( GetSizeVector() == 3 )
	{
		CVector2 oPosF = GetVector( 0 );
		CVector2 oPosC = GetVector( 1 );
		CVector2 oPosE = GetVector( 2 );

		Line( oPosF, oPosC, FALSE );
		Line( oPosC, oPosE, FALSE );
		Line( oPosE, oPosF, FALSE );
	}
}

VOID CTriNormal::OnDown( const CVector2& oPos )
{
	Drawing( TRUE );
	DrawGuide();
	Paint();

	if ( IsSamePosition( oPos ) )
	{
		UpdateVector( oPos );
		Paint();
		DrawGuide();
	}
	else
	{
		if ( GetSizeVector() >= m_nPoint )
		{
			Drawing( FALSE );
			Paint();

			ClearVector();
			Drawing( TRUE );
		}

		SetVector( oPos );
		Paint();
		DrawGuide();
	}
}
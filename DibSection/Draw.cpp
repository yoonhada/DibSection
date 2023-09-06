#include "stdafx.h"

CDraw::CDraw( CMemory * pMemory )
: m_pMemory( pMemory )
, m_bDrawing(FALSE)
, m_nPoint( 0 )
, m_ppVector( NULL )
{
	m_vectorRECT[0] = CPoint2( 0, 0 );
	m_vectorRECT[1] = CPoint2( pMemory->GetWidth(), pMemory->GetHeight() );
}

CDraw::CDraw( CMemory * pMemory, INT nPoint )
: m_pMemory( pMemory )
, m_nPoint( nPoint )
, m_bDrawing(FALSE)
, m_ppVector( NULL )
{
	m_ppVector = new CPoint2 * [ nPoint ];
	m_vectorRECT[0] = CPoint2( 0, 0 );
	m_vectorRECT[1] = CPoint2( pMemory->GetWidth(), pMemory->GetHeight() );
}

CDraw::~CDraw()
{
	SAFE_DELETE_ARRAY( m_ppVector );
}

CPoint2& CDraw::GetVector()				
{
	return  m_listVector.back();
}

CPoint2& CDraw::GetVector( INT nIndex )	
{ 
	if ( nIndex > static_cast<INT>( m_listVector.size() ) )
	{
		return m_listVector.back();
	}

	for ( m_iter = m_listVector.begin(); m_iter != m_listVector.end(); m_iter++ )
	{
		if ( nIndex == 0 )
			break;

		--nIndex;
	}

	return ( *m_iter );
}

VOID CDraw::AddVector( const CPoint2& oPos )
{
	m_listVector.push_back( oPos );

	m_riter = m_listVector.rbegin();
}

VOID CDraw::SetVector( const CPoint2& oPos, BOOL bUpdate )
{
	if ( static_cast< INT >( m_listVector.size() ) > m_nPoint )		{ m_listVector.clear(); }
	if ( bUpdate == FALSE && !m_listVector.empty( ) )				{ m_listVector.pop_back(); }

	m_listVector.push_back( oPos );
	m_riter = m_listVector.rbegin();
}

const CPoint2 CDraw::DeleteVector( const CPoint2& oPos )
{
	CPoint2 oRet;
	if( IsSamePosition( oPos ) )
	{
		oRet = *m_iter;
		m_listVector.erase( m_iter );
	}

	return oRet;
}

VOID CDraw::UpdateVector( const CPoint2& oPos )
{
	(*m_riter).x = oPos.x;
	(*m_riter).y = oPos.y;
}

VOID CDraw::MoveVector( const CPoint2& oPos )
{
	for ( m_riter = m_listVector.rbegin(); m_riter != m_listVector.rend(); ++m_riter )
	{
		m_riter->x += oPos.x;
		m_riter->y += oPos.y;
	}
}

INT CDraw::GetBytePerScanLine( const INT nWidth )
{
	return ( nWidth * 3 + 3 ) & ~3;
}

INT CDraw::GetOffset( const INT nPosX, const INT nPosY, const INT nWidth )
{
	return nPosX * 3 + nPosY * ( ( nWidth * 3 + 3 ) & ~3 );
}

VOID CDraw::ClearVector()
{
	m_listVector.clear();
}

BOOL CDraw::IsSamePosition( const CPoint2& oPos )
{
	BOOL bRet = FALSE;
	const int nSame = GUIDELINE << 1;

	for ( m_riter = m_listVector.rbegin(); m_riter != m_listVector.rend(); ++m_riter )
	{
		if ( ( m_riter->x - nSame ) < oPos.x && oPos.x < ( m_riter->x + nSame ) && 
			 ( m_riter->y - nSame ) < oPos.y && oPos.y < ( m_riter->y + nSame ) )
		{
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}

BOOL CDraw::FindPosition( const CPoint2& oPos )
{
	BOOL bRet = FALSE;

	for ( m_riter = m_listVector.rbegin(); m_riter != m_listVector.rend(); ++m_riter )
	{
		if ( m_riter->x == oPos.x && m_riter->y == oPos.y )
		{
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}
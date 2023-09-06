#include <Windows.h>
#include "stdafx.h"
#include "Memory.h"
#include "2DDrawInc.h"

CMemory::CMemory( HWND hWnd )
: m_pBits( NULL )
, m_pDraw( NULL )
, m_pDraw3D( NULL )
, m_pList( NULL )
{
	m_hScrDC = GetDC( hWnd );
	m_hMemDC = CreateCompatibleDC( m_hScrDC );


	m_nWidth  = GetSystemMetrics( SM_CXSCREEN );
	m_nHeight = GetSystemMetrics( SM_CYSCREEN );

	m_ppDrawMenu = new CDraw * [END];

	m_ppDrawMenu[NONE]				 = NULL;
	m_ppDrawMenu[CLINEDDA]			 = new CLineDDA( this );
	m_ppDrawMenu[CLINEMLA]			 = new CLineMLA( this );
	m_ppDrawMenu[CLINEDSA]			 = new CLineDSA( this );
	m_ppDrawMenu[CLINEEFA]			 = new CLineEFA( this );
	m_ppDrawMenu[CCIRCLE]			 = new CCircle( this );
	m_ppDrawMenu[CCIRCLEMIDP]		 = new CCircleMidP( this );
	m_ppDrawMenu[CCIRCLESECORDER]	 = new CCircleSecOrder( this );
	m_ppDrawMenu[CSPCARDINAL]		 = new CSpCardinal( this );
	m_ppDrawMenu[CSPHERMIT]			 = new CSpHermit( this );
	m_ppDrawMenu[CSPBEZIER3]		 = new CSpBezier3( this );
	m_ppDrawMenu[CSPBEZIER4]		 = new CSpBezier4( this );
	m_ppDrawMenu[CCLIPENDPOINT]		 = new CClipEndPoint( this );
	m_ppDrawMenu[CCLIPCOHEN]		 = new CClipCohen( this );
	m_ppDrawMenu[CCLIPPARAMETRIC]	 = new CClipParametric( this );
	m_ppDrawMenu[CTRIANGLE]			 = new CTriangle( this );
	m_ppDrawMenu[CTRIFLAT]			 = new CTriFlat( this );
	m_ppDrawMenu[CTRIGOURAUD]		 = new CTriGouraud( this );
	m_ppDrawMenu[CTRITEXTURE]		 = new CTriTexture( this );
	//Clear();
	Create();
}

CMemory::~CMemory(void)
{
	Destory();
}

VOID CMemory::Clear()
{
	m_pDraw = NULL;
	SetColor( BACKGROUND, GRAY );
	SetColor( FORGROUND,  WHITE );

	for ( int i = ( NONE + 1 ); i < END; ++i )
	{
		m_ppDrawMenu[i]->ClearVector();
	}

	m_pList->Clear();
}

VOID CMemory::Create()
{
	m_pDraw = NULL;
	SetColor( BACKGROUND, GRAY );
	SetColor( FORGROUND,  WHITE );

	SAFE_DELETE( m_pList );
	SAFE_DELETE( m_pDraw3D );
	m_pList = new CModelList;
	m_pDraw3D = new CDraw3D( this );
}

VOID CMemory::Destory()
{
	for ( int i = 1; i < END; ++i )
	{
		SAFE_DELETE( m_ppDrawMenu[i] );
	}

	SAFE_DELETE_ARRAY( m_ppDrawMenu );

	SAFE_DELETE( m_pDraw );
	SAFE_DELETE( m_pDraw3D );
	SAFE_DELETE( m_pList );
}

VOID CMemory::Render()
{
	BitBlt( 
		m_hScrDC, 0, 0, m_nWidth, m_nHeight, 
		m_hMemDC, 0, 0, SRCCOPY );
}

VOID CMemory::Update()
{
}

void CMemory::SetColor( INT nType, COLORREF color )
{
	if( nType == FORGROUND )		m_colorForGround = color;
	else if( nType == BACKGROUND )	m_colorBackGround = color; 
}

COLORREF CMemory::GetColor( INT nType ) const
{
	if( nType == FORGROUND )		return m_colorForGround;
	else if( nType == BACKGROUND )	return m_colorBackGround;

	return 0;
}

VOID CMemory::SetDraw( CDrawBitmap * pDraw, BOOL bFlag )
{
	m_pBitMap = pDraw;
}
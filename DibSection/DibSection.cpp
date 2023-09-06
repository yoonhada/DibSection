#include "stdafx.h"
#include "DrawBitmap.h"

CDibSection::CDibSection( CMemory * pMemory )
: m_pMemory( pMemory )
, m_bDrawInable( FALSE )
{
	Create();
}

CDibSection::~CDibSection()
{
}

VOID CDibSection::Clear()
{
	m_bDrawInable = FALSE;
	memset( m_pMemory->GetBits(), 0, m_pMemory->GetWidth() * m_pMemory->GetHeight() * 3 );
}

VOID CDibSection::Create()
{
	BYTE * pBits;
	BITMAPINFO oBitInfo;

	INT nSize = sizeof( BITMAPINFO );

	ZeroMemory( &oBitInfo, nSize );
	oBitInfo.bmiHeader.biSize			= nSize;
	oBitInfo.bmiHeader.biWidth			= m_pMemory->GetWidth();
	oBitInfo.bmiHeader.biHeight			= -m_pMemory->GetHeight();
	oBitInfo.bmiHeader.biPlanes			= 1;
	oBitInfo.bmiHeader.biBitCount		= 24;
	oBitInfo.bmiHeader.biCompression	= BI_RGB;
	oBitInfo.bmiHeader.biSizeImage		= 0;
	//oBitInfo.bmiHeader.biXPelsPerMeter;
	//oBitInfo.bmiHeader.biYPelsPerMeter;
	//oBitInfo.bmiHeader.biClrUsed;
	//oBitInfo.bmiHeader.biClrImportant;

	HBITMAP hDIBBitMap = CreateDIBSection(
		m_pMemory->GetMemDC(),		// handle to DC
		( BITMAPINFO* )&oBitInfo,	// bitmap data
		DIB_RGB_COLORS,				// data type indicator
		( LPVOID* )&pBits,			// bit values
		NULL,						// handle to file mapping object
		NULL );						// offset to bitmap bit values

	m_hOldBitMap = ( HBITMAP )SelectObject( m_pMemory->GetMemDC(), hDIBBitMap );
	m_pMemory->SetBits( pBits );
}



VOID CDibSection::Destory()
{
	CDraw * pDraw = m_pMemory->GetDraw();

	if( pDraw )			SAFE_DELETE( pDraw );
}

VOID CDibSection::Render()
{
}

VOID CDibSection::Update()
{
}

void CDibSection::OnMove( const CPoint2& oPos )
{
	if ( m_bDrawInable )
	{
		CDraw * pDraw = m_pMemory->GetDraw();
		if ( pDraw )	{ pDraw->OnMove( oPos ); }
	}
}

void CDibSection::OnDown( const CPoint2& oPos )
{
	m_bDrawInable = TRUE;
	CDraw * pDraw = m_pMemory->GetDraw();
	if ( pDraw )	{ pDraw->OnDown( oPos ); }
}

void CDibSection::OnUp( const CPoint2& oPos )
{
	if ( m_bDrawInable )
	{
		m_bDrawInable = FALSE;
		CDraw * pDraw = m_pMemory->GetDraw();
		if ( pDraw )	{ pDraw->OnUp( oPos ); }
	}
}

BOOL CDibSection::LoadBitmapEx( HWND hWnd )
{
	BOOL bRet = FALSE;
	OPENFILENAME OFN;	
	WCHAR szStr[MAX_PATH] = TEXT("");
	WCHAR szCurrentDir[MAX_PATH] = TEXT("");

	int nSize = sizeof(OPENFILENAME);
	memset(&OFN, 0, nSize);
	OFN.lStructSize = nSize;
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = TEXT("BMP(*.bmp)\0*.bmp\0All File(*.*)\0*.*\0");
	OFN.lpstrFile = szStr;
	OFN.nMaxFile = MAX_PATH;

	GetCurrentDirectory(MAX_PATH,  szCurrentDir);
	bRet = GetOpenFileName(&OFN);
	if(bRet != FALSE){
		FILE *fp;
		BITMAPFILEHEADER oBmfh;
		BITMAPINFOHEADER oBmih;

		//fopen_s(&fp, lpstr, "r");
		_wfopen_s(&fp, szStr, L"rb");

		if(fp != NULL){
			fread(&oBmfh, sizeof(BITMAPFILEHEADER), 1, fp);
			fread(&oBmih, sizeof(BITMAPINFOHEADER), 1, fp);
			if( oBmfh.bfType == 0X4D42 || oBmih.biBitCount == 24 || oBmih.biCompression == BI_RGB)
			{
				CDraw * pDraw = m_pMemory->GetDraw();
				if( pDraw )		
				{
					SAFE_DELETE( pDraw );
					m_pMemory->SetDraw( NULL );
				}

				CDrawBitmap * pBits = new CDrawBitmap( m_pMemory, oBmih.biWidth, oBmih.biHeight );
				m_pMemory->SetDraw( pBits );
				m_pMemory->SetDraw( pBits, FALSE );
				fread( pBits->GetImages(), pBits->GetSize(), 1, fp );		//oBmih.biSizeImage, 1, fp );
				fclose( fp );
			}
		}
	}
	SetCurrentDirectory( szCurrentDir );

	return bRet;
}
#include "stdafx.h"

CWndEx::CWndEx( )
: m_pDibSection( NULL )
, m_pMemory( NULL )
, m_nDialogMode( 0 ) 
, m_nDrawMode( 0 )
, m_nOffSet( 200 )
{
	m_lpszTitle[FRAMHWND] = L"SoftWare Rendering";
	m_lpszTitle[MAINHWND] = L"View";

	
#ifdef _DEBUG
	CDebugConsole::GetInstance( );
#endif
	CFrequency::GetInstance( );

	srand( ( unsigned )time( NULL ) );
}

CWndEx::~CWndEx( )
{
	Destory( );
}

ATOM CWndEx::RegisterClass( WNDPROC lpfnWndProc, LPTSTR lpszTitle, UINT dwStyle )
{
	WNDCLASSEX wndClass;
	
	wndClass.cbSize = sizeof( WNDCLASSEX );
	/* Win 3.x */
	wndClass.style			= dwStyle; 
	wndClass.lpfnWndProc	= lpfnWndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= m_hInstance;
	wndClass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wndClass.hCursor		= LoadCursor( NULL, IDC_CROSS );
	wndClass.hbrBackground	= ( HBRUSH )( COLOR_WINDOW + 1 );
	wndClass.lpszMenuName	= NULL;		// MAKEINTRESOURCE( IDI_MENU );
	wndClass.lpszClassName	= lpszTitle;
	/* Win 4.0 */
	wndClass.hIconSm		= NULL;		// LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON ) );

	return RegisterClassEx( &wndClass );
}

BOOL CWndEx::InitInstance( INT nCmdShow )
{
	BOOL bRet = FALSE;

	m_hWnd[FRAMHWND] = CreateWindow( 
		m_lpszTitle[FRAMHWND], m_lpszTitle[FRAMHWND], 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		1024, 768,
		NULL, NULL, m_hInstance, NULL );

	Create( );
	if ( m_hWnd[FRAMHWND] )
	{
		ShowWindow( m_hWnd[FRAMHWND], nCmdShow );
		UpdateWindow( m_hWnd[FRAMHWND] );
		bRet = TRUE;
	}

	return bRet;
}

VOID CWndEx::Create( )
{
	CFrequency::GetInstance( );

	SAFE_DELETE( m_pDibSection );
	SAFE_DELETE( m_pMemory );

	m_pMemory		= new CMemory( m_hWnd[MAINHWND] );
	m_pDibSection	= new CDibSection( m_pMemory );
	m_pTrans		= new CTrans( m_pMemory->GetWidth( ) - m_nOffSet, m_pMemory->GetHeight( ) );
}

VOID CWndEx::Destory( )
{
	SAFE_DELETE( m_pDibSection );
	SAFE_DELETE( m_pMemory );

	CFrequency::DestoryInstance( );

#ifdef _DEBUG
	CDebugConsole::DestoryInstance( );
#endif
}

VOID CWndEx::Render( )
{
	m_pMemory->Render( );
}

VOID CWndEx::Update( )
{
	CFrequency::GetInstance( )->Update( );

	if ( m_nDialogMode == THWND )
	{
		Input( );
		Frame( );
		OutputInfo( );
	}

	Output( );
}

VOID CWndEx::Input( )
{
}

VOID CWndEx::Frame( )
{
	m_pDibSection->Clear( );
	SetFrame( );
}

VOID CWndEx::OutputInfo( )
{
	SetTextColor( m_pMemory->GetMemDC( ), WHITE );
	SetBkColor( m_pMemory->GetMemDC( ), BLACK );

	//WCHAR buf[256];
	//swprintf_s( buf, 256, L"MODE Select : F1[Model], F2[Euler], F3[LookAt], F4[Project]" );
	//TextOut( m_pMemory->GetMemDC( ), 10, 10, buf, wcslen( buf ) );
}

VOID CWndEx::Output( )
{
	FLOAT fFps = CFrequency::GetInstance( )->GetFrequency( );
	WCHAR szBuffer[256];	
	swprintf_s( szBuffer, 256, L"FPS : %03.1f", fFps );
	SetDlgItemText( m_hWnd[SIDEHWND], IDC_FPSSTATIC, szBuffer );
}

VOID CWndEx::SetFrame( )
{
	WCHAR szBuffer[256];	
	CNode * pNode = NULL;

	if ( m_nTransformPipeline == IDC_RADIOTMODEL )
	{
		CMatrix4 mat;
		pNode = m_pMemory->GetList()->GetCurr();
		if ( pNode )
		{	
			Pipeline( pNode, mat );

			swprintf_s( szBuffer, 256, 
				L"Model Select : Tab\n"
				L"None  : Rotate( %-03d, %-03d, %-03d )\n"
				L"Ctrl  : Trans ( %0.0f, %0.0f, %0.0f )\n" 
				L"Shift : Scale ( %0.2f, %0.2f, %0.2f )\n", 
				pNode->m_nRotate[0], pNode->m_nRotate[1], pNode->m_nRotate[2], 
				pNode->m_fTrans[0], pNode->m_fTrans[1], pNode->m_fTrans[2], 
				pNode->m_fScale[0], pNode->m_fScale[1], pNode->m_fScale[2] );
			SetDlgItemText( m_hDlgWnd[THWND], IDC_STATICDESCRIPTION, szBuffer );
		}
	}
	else if ( m_nTransformPipeline == IDC_RADIOTWORLD )
	{
		CMatrix4 mat;
		pNode = m_pMemory->GetList( )->MoveHead( );
		m_pTrans->TransWorld2View( 0, mat );		// m_nTransformPipeline - IDC_RADIOTWORLD
		while ( pNode )
		{
			m_pTrans->TransModel2World( pNode, mat );
			Pipeline( pNode, mat );
			pNode = m_pMemory->GetList( )->MoveNext( );
		}

		pNode = m_pMemory->GetList()->GetCurr();
		if ( pNode )
		{	
			swprintf_s( szBuffer, 256, 
				L"Model Select : Tab\n"
				L"None  : Rotate( %-03d, %-03d, %-03d )\n"
				L"Ctrl  : Trans ( %0.0f, %0.0f, %0.0f )\n" 
				L"Shift : Scale ( %0.2f, %0.2f, %0.2f )\n", 
				pNode->m_nRotate[0], pNode->m_nRotate[1], pNode->m_nRotate[2], 
				pNode->m_fTrans[0], pNode->m_fTrans[1], pNode->m_fTrans[2], 
				pNode->m_fScale[0], pNode->m_fScale[1], pNode->m_fScale[2] );
			SetDlgItemText( m_hDlgWnd[THWND], IDC_STATICDESCRIPTION, szBuffer );
		}
	}
	else if ( m_nTransformPipeline >= IDC_RADIOTVIEW )
	{
		CMatrix4 mat, matP, matV, matW;
		pNode = m_pMemory->GetList( )->MoveHead( );
		m_pTrans->TransWorld2View( 1, matV );
		if ( m_nTransformPipeline == IDC_RADIOTPROJECT )
		{
			m_pTrans->TransView2Projection( matP );
			matV = matP * matV;
		}

		while ( pNode )
		{
			m_pTrans->TransModel2World( pNode, matW );
			mat = matV * matW;
			Pipeline( pNode, mat );
			pNode = m_pMemory->GetList( )->MoveNext( );
		}

		swprintf_s( szBuffer, 256, 
			L"Camera \n"
			L"None  : Move \n"
			L"Ctrl  : Target ( %-0.1f, %-0.1f, %-0.1f )\n" 
			L"Shift : Dir    ( %-0.1f, %-0.1f, %-0.1f )", 
			m_pTrans->m_vertorTarget.x, m_pTrans->m_vertorTarget.y, m_pTrans->m_vertorTarget.z, 
			m_pTrans->m_vertorCamera.x, m_pTrans->m_vertorCamera.y, m_pTrans->m_vertorCamera.z );
		SetDlgItemText( m_hDlgWnd[THWND], IDC_STATICDESCRIPTION, szBuffer );
	}
}

void CWndEx::Pipeline( CNode * pNode, CMatrix4 &mat )
{
	// Curring		
	if ( m_nDrawMode == 0 )		pNode->Curring( m_nTransformPipeline, mat, m_pTrans, FALSE );
	else						pNode->Curring( m_nTransformPipeline, mat, m_pTrans );

	CMatrix4 matS;
	m_pTrans->TransNdc2Screen( matS );
	pNode->Screen( m_nTransformPipeline, matS );

	if ( m_nDrawMode == 0 || m_nDrawMode == 1 )
		m_pMemory->GetDraw3D( )->Triangle( pNode );
	else if ( m_nDrawMode == 2 )
		m_pMemory->GetDraw3D( )->Flat( pNode );
	else if ( m_nDrawMode == 3 )
		m_pMemory->GetDraw3D( )->Goroud( pNode );
}

VOID CWndEx::CreateMenuEx( HWND hWnd )
{
	HMENU hMenu, hMenuPopup;

	hMenu = CreateMenu( );
	hMenuPopup = CreateMenu( );
	AppendMenu( hMenuPopup, MF_STRING,				IDM_FILE_NEW,			L"&New"		 );
	AppendMenu( hMenuPopup, MF_SEPARATOR,			0,						NULL		 );
	AppendMenu( hMenuPopup, MF_STRING,				IDM_APP_EXIT,			L"E&xit"	 );
	AppendMenu( hMenu,		MF_STRING | MF_POPUP,	( UINT )hMenuPopup,		L"&File"	 );	
	SetMenu( hWnd, hMenu );
}

INT CWndEx::MessageLoop( HINSTANCE hInstance )
{
	CWndEx * view = CWndEx::GetInstance( );

	MSG Message;
	ZeroMemory( &Message, sizeof( MSG ) ); 

	view->m_hInstance = hInstance;
	view->RegisterClass( FramWndProc, view->m_lpszTitle[FRAMHWND], CS_HREDRAW | CS_VREDRAW );
	view->RegisterClass( MainWndPorc, view->m_lpszTitle[MAINHWND], CS_HREDRAW | CS_VREDRAW );
	view->InitInstance ( SW_MAXIMIZE );

	//HACCEL hAccel;
	//hAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCELERATOR ) );

	while ( TRUE )
	{
		if ( PeekMessage ( &Message, NULL, NULL, NULL, PM_REMOVE ) )
		{
			//if( !TranslateAccelerator( GetInstance( ).m_hWnd, hAccel, &Message ) )
			if ( Message.message == WM_QUIT )
			{
				PostQuitMessage( 0 );
				break;
			}
			else
			{
				if ( !IsWindow( view->m_hWnd[DLOGHWND] ) || 
					 !IsDialogMessage( view->m_hWnd[DLOGHWND], &Message ) )
				{
					TranslateMessage( &Message );
					DispatchMessage( &Message );
				}
			}
		}
		else
		{
			view->Update( );
			view->Render( );
		}
	}

	UnregisterClass( view->m_lpszTitle[FRAMHWND], view->m_hInstance );
	UnregisterClass( view->m_lpszTitle[MAINHWND], view->m_hInstance );
	return static_cast< INT >( Message.wParam );
}

LRESULT CALLBACK CWndEx::FramWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWndEx * view = CWndEx::GetInstance( );
	switch ( message )
	{
		HANDLE_MSG( hWnd, WM_COMMAND,		view->OnCommand		 );
		HANDLE_MSG( hWnd, WM_CREATE,		view->OnCreate		 );
		HANDLE_MSG( hWnd, WM_DESTROY,		view->OnDestroy		 );
		HANDLE_MSG( hWnd, WM_SIZE,			view->OnSize		 );
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
} 

void CWndEx::OnCommand( HWND hWnd, INT id, HWND hwndCtl, UINT codeNotify )
{
	switch( id )
	{
	case IDM_APP_EXIT:
		PostMessage( hWnd, WM_CLOSE, 0, 0 );
		break;
	}
}

BOOL CWndEx::OnCreate( HWND hWnd, LPCREATESTRUCT lpCreateStruct )
{
	InitCommonControls( );
	//CreateMenuEx( hWnd );

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN;
	m_hWnd[MAINHWND] = CreateWindow( m_lpszTitle[MAINHWND], NULL, dwStyle, 0, 0, 0, 0, hWnd, ( HMENU )0, m_hInstance, NULL );
	m_hWnd[SIDEHWND] = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_DIALOGSIDE ), hWnd, ( DLGPROC )SideWndPorc );
	m_hDlgWnd[TWWND] = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_DIALOG2D ),	 m_hWnd[TAB_HWND], ( DLGPROC )Two_WndPorc );
	m_hDlgWnd[THWND] = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_DIALOG3D ),	 m_hWnd[TAB_HWND], ( DLGPROC )ThreWndPorc );

	SendMessage( m_hWnd[SIDEHWND], WM_DIALOGSELECT, 0, 0 );
	SetFocus( hWnd );

	return TRUE;
}

void CWndEx::OnDestroy( HWND hWnd )
{
	PostQuitMessage( 0 );
}

VOID CWndEx::OnSize( HWND hWnd, UINT state, INT cx, INT cy )
{
	RECT rect;

	GetClientRect( hWnd, &rect );

	if ( state != SIZE_MINIMIZED )
	{
		MoveWindow( m_hWnd[MAINHWND], 0, 0, rect.right - m_nOffSet, rect.bottom, TRUE );
		MoveWindow( m_hWnd[SIDEHWND], rect.right - m_nOffSet, 0, rect.right, rect.bottom, TRUE );
	}
}

LRESULT CALLBACK CWndEx::MainWndPorc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWndEx * view = CWndEx::GetInstance( );
	switch ( message )
	{
		HANDLE_MSG( hWnd, WM_LBUTTONUP,		view->OnLButtonUp	 );
		HANDLE_MSG( hWnd, WM_LBUTTONDOWN,	view->OnLButtonDown	 );
		HANDLE_MSG( hWnd, WM_RBUTTONUP,		view->OnRButtonUp	 );
		HANDLE_MSG( hWnd, WM_RBUTTONDOWN,	view->OnRButtonDown	 );
		HANDLE_MSG( hWnd, WM_MOUSEMOVE,		view->OnMouseMove	 );
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
} 

VOID CWndEx::OnLButtonDown( HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags )
{
	RECT rect;
	::GetWindowRect( hWnd, &rect );
	ClipCursor( &rect );

	m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );

	if ( m_nDialogMode == TWWND )
	{
		m_pDibSection->OnDown( m_oMousePos );
	}
}

VOID CWndEx::OnLButtonUp( HWND hWnd, INT x, INT y, UINT keyFlags )
{
	m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );
	ClipCursor( NULL );

	if ( m_nDialogMode == TWWND )
	{
		m_pDibSection->OnUp( m_oMousePos );
	}
}

VOID CWndEx::OnRButtonDown( HWND hWnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags )
{
	RECT rect;
	::GetWindowRect( hWnd, &rect );
	ClipCursor( &rect );

	m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );
}

VOID CWndEx::OnRButtonUp( HWND hWnd, INT x, INT y, UINT keyFlags )
{
	m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );
	ClipCursor( NULL );
}

VOID CWndEx::OnMouseMove( HWND hWnd, INT x, INT y, UINT keyFlags )
{
	if ( m_nDialogMode == TWWND )
	{
		m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );
		m_pDibSection->OnMove( m_oMousePos );
	}
	else
	{
		int nDeltaX = x - m_oMousePos.x;
		int nDeltaY = y - m_oMousePos.y;

		if( ( keyFlags & MK_LBUTTON ) == MK_LBUTTON ){
			if( ( keyFlags & MK_CONTROL ) == MK_CONTROL )	{ Trans( nDeltaX, nDeltaY ); }
			else if( ( keyFlags & MK_SHIFT ) == MK_SHIFT )	{ Scale( nDeltaX, nDeltaY ); }
			else										{ Rotate( nDeltaX, nDeltaY ); }
		}else if( ( keyFlags & MK_RBUTTON ) == MK_RBUTTON ){
			if( abs( nDeltaX ) < abs( nDeltaY ) )	nDeltaX = nDeltaY;
			if( ( keyFlags & MK_CONTROL ) == MK_CONTROL )	{ Trans( nDeltaX, ENOUGHBIGINT ); }
			else if( ( keyFlags & MK_SHIFT ) == MK_SHIFT )	{ Scale( nDeltaX, ENOUGHBIGINT ); }
			else										{ Rotate( nDeltaX, ENOUGHBIGINT ); }
		}

		m_oMousePos = CPoint2( x, y, m_pMemory->GetColor( CMemory::FORGROUND ), m_pMemory->GetColor( CMemory::BACKGROUND ) );
	}
}

LRESULT CALLBACK CWndEx::SideWndPorc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWndEx * view = CWndEx::GetInstance( );
	switch ( message )
	{
		HANDLE_MSG( hWnd, WM_INITDIALOG, view->OnInitDialogSide );
		HANDLE_MSG( hWnd, WM_COMMAND, view->OnCommandSide );
		HANDLE_MSG( hWnd, WM_PAINT, view->OnPaintSide );
		HANDLE_MSG( hWnd, WM_NOTIFY, view->OnNotifySide );
		HANDLE_MSG( hWnd, WM_DESTROY, view->OnDestorySide );
		case WM_DIALOGSELECT:	return view->OnDialogSelect( hWnd, wParam );
	}

	return FALSE;
} 

BOOL CWndEx::OnInitDialogSide( HWND hWnd, HWND hwndFocus, LPARAM lParam )
{
	m_hWnd[TAB_HWND] = GetDlgItem( hWnd, IDC_TAB );

	TCHAR * pszText[2] = {
		TEXT( "2D Rendering" ), 
		TEXT( "3D Rendering" )
	};

	TCITEM tie;
	tie.mask = TCIF_TEXT;
	for ( int i = 0; i < 2; ++i ){
		tie.pszText = pszText[i];
		TabCtrl_InsertItem( m_hWnd[TAB_HWND], i, &tie );
	}

	return TRUE;
}

VOID CWndEx::OnCommandSide( HWND hWnd, INT id, HWND hwndCtl, UINT codeNotify )
{
	switch( id )
	{
	case IDC_BUTTONNEW:
		m_pDibSection->Clear( );
		m_pMemory->Clear( );
		m_pTrans->Clear( );
		InvalidateRect( hWnd, NULL, FALSE );
		break;
	case IDC_BUTTONOPEN:
		if( m_pDibSection->LoadBitmapEx( m_hWnd[MAINHWND] ) )
		{
			CDraw * pDraw = m_pMemory->GetDraw( );
			pDraw->Paint( );
		}
		break;
	case IDC_BUTTONLINE:
		ChooseColorSide( hWnd, CMemory::FORGROUND );
		InvalidateRect( hWnd, NULL, FALSE );
		break;
	case IDC_BUTTONBRUSH:
		ChooseColorSide( hWnd, CMemory::BACKGROUND );
		InvalidateRect( hWnd, NULL, FALSE );
		break;
	}
}

VOID CWndEx::ChooseColorSide( HWND hWnd, INT nType )
{
	COLORREF oColor;
	CHOOSECOLOR oCol;
	static COLORREF acrCustClr[16];
	static DWORD rgbCurrent;

	ZeroMemory( &oCol, sizeof( CHOOSECOLOR ) );
	oCol.lStructSize = sizeof( CHOOSECOLOR );
	oCol.hwndOwner = hWnd;
	oCol.lpCustColors = ( LPDWORD )acrCustClr;
	oCol.rgbResult = rgbCurrent;
	oCol.Flags = CC_FULLOPEN | CC_RGBINIT;

	if ( ChooseColor( &oCol ) == TRUE )
	{
		oColor = oCol.rgbResult;
		m_pMemory->SetColor( nType, oColor );
	}
}

VOID CWndEx::OnPaintSide( HWND hWnd )
{
	HDC hDC;
	PAINTSTRUCT ps;
	COLORREF colorDraw, colorGuide;
	HBRUSH hDBrush, hGBrush, hOldBrush;
	HPEN hPen, hOldPen;

	colorDraw = m_pMemory->GetColor( CMemory::FORGROUND );
	colorGuide = m_pMemory->GetColor( CMemory::BACKGROUND );

	hDC = BeginPaint( hWnd, &ps );
	hPen = ( HPEN )CreatePen( PS_NULL, 5, colorDraw );
	hDBrush = ( HBRUSH )CreateSolidBrush( colorDraw );
	hGBrush = ( HBRUSH )CreateSolidBrush( colorGuide );
	hOldPen = ( HPEN )SelectObject( hDC, hPen );
	hOldBrush = ( HBRUSH )SelectObject( hDC, hDBrush );
	Rectangle( hDC, SIDE_LEFT  , SIDE_TOP, SIDE_LEFT + 15, SIDE_TOP + 30 );
	hOldBrush = ( HBRUSH )SelectObject( hDC, hGBrush );
	Rectangle( hDC, SIDE_LEFT + 15, SIDE_TOP, SIDE_LEFT + 30, SIDE_TOP + 30 );
	SelectObject( hDC, hOldBrush );
	SelectObject( hDC, hOldPen );
	DeleteObject( hPen );
	DeleteObject( hDBrush );
	DeleteObject( hGBrush );
	EndPaint( hWnd, &ps );
}

LONG CWndEx::OnNotifySide( HWND hWnd, UINT id, NMHDR* pNMHDR )
{
	if( pNMHDR->code == TCN_SELCHANGE )
	{
		SendMessage( hWnd, WM_DIALOGSELECT, TabCtrl_GetCurSel( m_hWnd[TAB_HWND] ), 0 );
	}

	return TRUE;
}

VOID CWndEx::OnDestorySide( HWND hWnd )
{
	if( IsWindow( m_hDlgWnd[TWWND] ) )
	{
		DestroyWindow( m_hDlgWnd[TWWND] );
	}
	if( IsWindow( m_hDlgWnd[THWND] ) )
	{
		DestroyWindow( m_hDlgWnd[THWND] );
	}
}

BOOL CWndEx::OnDialogSelect( HWND hWnd, WPARAM wParam )
{
	m_nDialogMode = wParam;
	ShowWindow( m_hDlgWnd[TWWND], SW_HIDE );
	ShowWindow( m_hDlgWnd[THWND], SW_HIDE );

	m_hWnd[DLOGHWND] = m_hDlgWnd[wParam];
	ShowWindow( m_hWnd[DLOGHWND], SW_SHOW );	

	if ( m_pMemory && m_pDibSection )
		SendMessage( hWnd, WM_COMMAND, IDC_BUTTONNEW, NULL );

	return TRUE;
}

LRESULT CALLBACK CWndEx::Two_WndPorc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWndEx * view = CWndEx::GetInstance( );

	switch( message )
	{
		HANDLE_MSG( hWnd, WM_INITDIALOG, view->OnInitDialog2D );
		HANDLE_MSG( hWnd, WM_COMMAND,	 view->OnCommand2D );
	}

	return FALSE;
}

BOOL CWndEx::OnInitDialog2D( HWND hWnd, HWND hWndFocus, LPARAM lParam )
{
	RECT rect = {0, 0, 0, 0};

	GetClientRect( m_hWnd[TAB_HWND], &rect );
	TabCtrl_AdjustRect( m_hWnd[TAB_HWND], FALSE, &rect );
	SetWindowPos( hWnd, HWND_TOP, 0, rect.top, rect.right-rect.left, rect.bottom - rect.top, SWP_NOZORDER );

	CheckRadioButton( hWnd, IDC_RADIO2DNONE, IDC_RADIOEFA, IDC_RADIO2DNONE );

	return TRUE;
} 

VOID CWndEx::OnCommand2D( HWND hWnd, int id, HWND hWndCtl, UINT codeNotify )
{
	CDraw * pDraw = m_pMemory->GetDraw( );
	if ( pDraw )			pDraw->Clear( );

	switch( id )
	{
	case IDC_RADIO2DNONE:
		m_pMemory->SetDraw( CMemory::NONE );

		break;
	case IDC_RADIODDA:
		m_pMemory->SetDraw( CMemory::CLINEDDA );
		break;
	case IDC_RADIOMLA:
		m_pMemory->SetDraw( CMemory::CLINEMLA );
		break;
	case IDC_RADIODSA:
		m_pMemory->SetDraw( CMemory::CLINEDSA );
		break;
	case IDC_RADIOEFA:
		m_pMemory->SetDraw( CMemory::CLINEEFA );
		break;
	case IDC_RADIOBASIC:
		m_pMemory->SetDraw( CMemory::CCIRCLE );
		break;
	case IDC_RADIOMIDPOINT:
		m_pMemory->SetDraw( CMemory::CCIRCLEMIDP );
		break;
	case IDC_RADIOSECONDORDER:
		m_pMemory->SetDraw( CMemory::CCIRCLESECORDER );
		break;
	case IDC_RADIOCARDINAL:
		m_pMemory->SetDraw( CMemory::CSPCARDINAL );
		break;
	case IDC_RADIOHERMIT:
		m_pMemory->SetDraw( CMemory::CSPHERMIT );
		break;
	case IDC_RADIOBEZIER3:
		m_pMemory->SetDraw( CMemory::CSPBEZIER3 );
		break;
	case IDC_RADIOBEZIER4:
		m_pMemory->SetDraw( CMemory::CSPBEZIER4 );
		break;
	case IDC_RADIOENDPOINT:
		m_pMemory->SetDraw( CMemory::CCLIPENDPOINT );
		break;
	case IDC_RADIOCOHEN:
		m_pMemory->SetDraw( CMemory::CCLIPCOHEN );
		break;
	case IDC_RADIOPARAMETRIC:
		m_pMemory->SetDraw( CMemory::CCLIPPARAMETRIC );
		break;
	case IDC_RADIONORMAL:
		m_pMemory->SetDraw( CMemory::CTRIANGLE );
		break;
	case IDC_RADIOFLAT:
		m_pMemory->SetDraw( CMemory::CTRIFLAT );
		break;
	case IDC_RADIOGOURAUD:
		m_pMemory->SetDraw( CMemory::CTRIGOURAUD );
		break;
	case IDC_RADIOTEXTURE:
		if( m_pDibSection->LoadBitmapEx( m_hWnd[MAINHWND] ) )
			m_pMemory->SetDraw( CMemory::CTRITEXTURE );
		break;
	}
}

LRESULT CALLBACK CWndEx::ThreWndPorc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	CWndEx * view = CWndEx::GetInstance( );

	switch ( message )
	{
		HANDLE_MSG( hWnd, WM_INITDIALOG, view->OnInitDialog3D );
		HANDLE_MSG( hWnd, WM_COMMAND,	view->OnCommand3D );
	}

	return FALSE;
} 

BOOL CWndEx::OnInitDialog3D( HWND hWnd, HWND hWndFocus, LPARAM lParam )
{
	RECT rect = {0, 0, 0, 0};

	GetClientRect( m_hWnd[TAB_HWND], &rect );
	TabCtrl_AdjustRect( m_hWnd[TAB_HWND], FALSE, &rect );
	SetWindowPos( hWnd, HWND_TOP, 0, rect.top, rect.right-rect.left, rect.bottom - rect.top, SWP_NOZORDER );

	CheckRadioButton( hWnd, IDC_RADIOMODEWIRE, IDC_RADIOMODEGOURAUD, IDC_RADIOMODECULLING );
	CheckRadioButton( hWnd, IDC_RADIOTMODEL, IDC_RADIOTPROJECT, IDC_RADIOTMODEL ) ;
	SetWindowText( GetDlgItem( hWnd, IDC_EDITRADIUS ),		L"200" );
	SetWindowText( GetDlgItem( hWnd, IDC_EDITLATITUDE ),	L"18" );
	SetWindowText( GetDlgItem( hWnd, IDC_EDITLONGITUDE ),	L"36" );
	SetWindowText( GetDlgItem( hWnd, IDC_EDITRECUR ),		L"5" );
	SetUIShow( IDC_BUTTON3DHEXAGON, hWnd );

	m_nDrawMode = IDC_RADIOMODECULLING - IDC_RADIOMODEWIRE;
	m_nFlagEditMode = IDC_BUTTON3DHEXAGON;
	m_nTransformPipeline = IDC_RADIOTMODEL;

	return TRUE;
} 

VOID CWndEx::OnCommand3D( HWND hWnd, int id, HWND hWndCtl, UINT codeNotify )
{
	switch( id )
	{
	case IDC_RADIOMODEWIRE:
	case IDC_RADIOMODECULLING:
	case IDC_RADIOMODEFLAT:
	case IDC_RADIOMODEGOURAUD:
		m_nDrawMode = id - IDC_RADIOMODEWIRE;
		break;
	case IDC_BUTTON3DHEXAGON:
	case IDC_BUTTON3DPYRAMID:
	case IDC_BUTTON3DDIAMOND:
	case IDC_BUTTON3DGLOBE:
	case IDC_BUTTON3DGEOSPHERE:
		m_nFlagEditMode = id;
		SetUIShow( id, hWnd );
		break;
	case IDC_BUTTON3DRANDOM:
		m_pMemory->GetList()->RandomModel();
		break;
	case IDC_BUTTON3DADD:
		WCHAR str[256];
		float fRadius;
		int nLatitude, nLongitude, nRecur;

		GetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITRADIUS ),		str, 256 );		fRadius = ( float )_wtof( str );
		GetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITLATITUDE ),	str, 256 );		nLatitude = _wtoi( str );
		GetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITLONGITUDE ),	str, 256 );		nLongitude = _wtoi( str );
		GetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITRECUR ),		str, 256 );		nRecur = _wtoi( str );

		if ( fRadius <= 0.0f )	fRadius = 200.0f;
		if ( nLatitude <= 0 )	nLatitude = 18;
		if ( nLongitude <= 0 )	nLongitude = 36;
		if ( nRecur <= 0 )		nRecur = 5;

		swprintf_s( str, 256, L"%d", ( int )fRadius );SetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITRADIUS ),		str );
		swprintf_s( str, 256, L"%d", nLatitude );	SetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITLATITUDE ),	str );
		swprintf_s( str, 256, L"%d", nLongitude );	SetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITLONGITUDE ),	str );
		swprintf_s( str, 256, L"%d", nRecur );		SetWindowText( GetDlgItem( m_hDlgWnd[THWND], IDC_EDITRECUR ),		str );

		m_pMemory->GetList( )->LoadModel( m_nFlagEditMode - IDC_BUTTON3DHEXAGON, fRadius, nLatitude, nLongitude, nRecur );
		break;
	case IDC_BUTTON3DDEL:
		m_pMemory->GetList( )->Remove( );
		break;
	case IDC_BUTTON3DNEXT:
		m_pMemory->GetList( )->GetNext( );
		break;
	case IDC_RADIOTMODEL:
	case IDC_RADIOTWORLD:
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DADD  ), TRUE );
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DNEXT ), TRUE );
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DDEL  ), TRUE );
		m_nTransformPipeline = id;
		break;
	case IDC_RADIOTVIEW:
	case IDC_RADIOTPROJECT:
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DADD  ), FALSE );
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DNEXT ), FALSE );
		EnableWindow( GetDlgItem( hWnd, IDC_BUTTON3DDEL  ), FALSE );
		m_nTransformPipeline = id;
		break;
	}
}

void CWndEx::SetUIShow( int nItem, HWND hWnd )
{
	ShowWindow( GetDlgItem( hWnd, IDC_STATIC1 ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_EDITRADIUS ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_STATIC2 ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_EDITLATITUDE ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_STATIC3 ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_EDITLONGITUDE ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_STATIC4 ), SW_HIDE );
	ShowWindow( GetDlgItem( hWnd, IDC_EDITRECUR ), SW_HIDE );

	switch ( nItem )
	{
	case IDC_BUTTON3DHEXAGON:
	case IDC_BUTTON3DPYRAMID:
	case IDC_BUTTON3DDIAMOND:
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC1 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITRADIUS ), SW_SHOW );
		break;
	case IDC_BUTTON3DGLOBE:
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC1 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITRADIUS ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC2 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITLATITUDE ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC3 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITLONGITUDE ), SW_SHOW );
		break;
	case IDC_BUTTON3DGEOSPHERE:
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC1 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITRADIUS ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_STATIC4 ), SW_SHOW );
		ShowWindow( GetDlgItem( hWnd, IDC_EDITRECUR ), SW_SHOW );
		break;
	}
}

void CWndEx::Scale( int nX, int nY )
{
	const float fRate = 0.1f;
	CNode * pNode;

	switch( m_nTransformPipeline )
	{
	case IDC_RADIOTMODEL:
	case IDC_RADIOTWORLD:
		pNode = m_pMemory->GetList( )->GetCurr( );
		if( pNode ){
			if( nY != ENOUGHBIGINT ){
				pNode->SetScale( AXISX, ( float )( nX * fRate ) );
				pNode->SetScale( AXISY, ( float )( nY * fRate ) );
			}else{
				pNode->SetScale( AXISZ, ( float )( nX * fRate ) );
			}
		}
		break;
	case IDC_RADIOTVIEW:
	case IDC_RADIOTPROJECT:
		if( nY != ENOUGHBIGINT ){
			m_pTrans->SetCamera( AXISX, static_cast<float>(  nX * fRate ) );
			m_pTrans->SetCamera( AXISY, static_cast<float>( -nY * fRate ) );
		}else{
			m_pTrans->SetCamera( AXISZ, static_cast<float>( -nX * fRate ) );
		}
		break;
	default:
		break;
	}
}

void CWndEx::Rotate( int nX, int nY )
{
	CNode * pNode;

	switch( m_nTransformPipeline )
	{
	case IDC_RADIOTMODEL:
	case IDC_RADIOTWORLD:
		pNode = m_pMemory->GetList( )->GetCurr( );
		if( pNode ){
			if( nY != ENOUGHBIGINT ){
				pNode->SetRotate( AXISX, nY );
				pNode->SetRotate( AXISY, nX );
			}else{
				pNode->SetRotate( AXISZ, -nX );
			}
		}
		break;
	case IDC_RADIOTVIEW:
	case IDC_RADIOTPROJECT:
		Trans( nX, nY );
		Scale( nX, nY );
		break;
	default:
		break;
	}
}

void CWndEx::Trans( int nX, int nY )
{
	const float fRate = 0.1f;
	CNode * pNode;

	switch( m_nTransformPipeline )
	{
	case IDC_RADIOTMODEL:
	case IDC_RADIOTWORLD:
		pNode = m_pMemory->GetList( )->GetCurr( );
		if( pNode ){
			if( nY != ENOUGHBIGINT ){
				pNode->SetTrans( AXISX, nX );
				pNode->SetTrans( AXISY, -nY );
			}else{
				pNode->SetTrans( AXISZ, nX );
			}
		}
		break;
	case IDC_RADIOTVIEW:
	case IDC_RADIOTPROJECT:
		if( nY != ENOUGHBIGINT ){
			m_pTrans->SetTraget( AXISX, static_cast<float>( nX * fRate ) );
			m_pTrans->SetTraget( AXISY, static_cast<float>( nY * fRate ) );
		}else{
			m_pTrans->SetTraget( AXISZ, static_cast<float>( nX * fRate ) );
		}	
		break;
	default:
		break;
	}
}
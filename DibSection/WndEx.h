#pragma once
#pragma comment( lib, "comctl32" )

class CWndEx : public CSingleton< CWndEx >
{
private:
	// ENUM
	enum { FRAMHWND, MAINHWND, SIDEHWND, TAB_HWND, DLOGHWND, STATUS, END };
	enum { TWWND, THWND, DLGEND };
	
	// PRE
	friend class CSingleton<CWndEx>;

	// MEMBER
	HWND			m_hWnd[END];
	HWND			m_hDlgWnd[DLGEND];
	HINSTANCE		m_hInstance;

	LPWSTR			m_lpszTitle[2];

	CDibSection *	m_pDibSection;
	CMemory *		m_pMemory;
	CTrans *		m_pTrans;

	CPoint2			m_oMousePos;

	INT				m_nDialogMode;
	INT				m_nDrawMode;
	INT				m_nTransformPipeline;

	INT				m_nFlagEditMode;
	const INT		m_nOffSet;

	CWndEx();
	~CWndEx();

	//VOID Clear();
	VOID Create();
	VOID Destory();
	VOID Render();
	VOID Update();

	// Method
	VOID Input();
	VOID Frame();
	VOID Output();
	VOID OutputInfo();

	VOID SetFrame();

	ATOM RegisterClass( WNDPROC, LPTSTR, UINT );
	BOOL InitInstance( INT );

	static LRESULT CALLBACK FramWndProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK MainWndPorc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK SideWndPorc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK Two_WndPorc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK ThreWndPorc( HWND, UINT, WPARAM, LPARAM );

	VOID CreateMenuEx( HWND );
	VOID CreateStatusWindowEx( HWND );
	VOID SetStatusRGB();

	// MESSAGE
		// Frame MESSAGE
		VOID OnCommand( HWND, INT, HWND, UINT );
		BOOL OnCreate( HWND, LPCREATESTRUCT );
		VOID OnDestroy( HWND );
		VOID OnSize( HWND, UINT, INT, INT );

		// Main Message
		VOID OnMouseMove( HWND, INT, INT, UINT );
		VOID OnLButtonDown( HWND, BOOL, INT, INT, UINT );
		VOID OnLButtonUp( HWND, INT, INT, UINT );
		VOID OnRButtonDown( HWND, BOOL, INT, INT, UINT );
		VOID OnRButtonUp( HWND, INT, INT, UINT );

		// Side Message
		BOOL OnInitDialogSide( HWND, HWND, LPARAM );
		VOID OnCommandSide( HWND, INT, HWND, UINT );
		VOID OnPaintSide( HWND );
		VOID ChooseColorSide( HWND, INT );
		LONG OnNotifySide( HWND, UINT, NMHDR* );
		VOID OnDestorySide( HWND );
		BOOL OnDialogSelect( HWND, WPARAM );

		// 2D Message
		BOOL OnInitDialog2D( HWND, HWND, LPARAM );
		VOID OnCommand2D( HWND, INT, HWND, UINT );
		VOID OnPaint2D(HWND);


		// 3D Message
		BOOL OnInitDialog3D( HWND, HWND, LPARAM );
		VOID OnCommand3D( HWND, INT, HWND, UINT );

private:
	void SetUIShow(int, HWND);
	void Rotate(int, int);
	void Scale(int, int);
	void Trans(int, int);

	void Pipeline( CNode*, CMatrix4& );

public:
	static INT MessageLoop( HINSTANCE = NULL );
};

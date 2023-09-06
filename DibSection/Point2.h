#pragma once

struct CPoint2
{
	INT x, y;
	BYTE fr, fg, fb;
	BYTE br, bg, bb;
	FLOAT u, v;

	CPoint2()		{}
	CPoint2( INT _x, INT _y, DWORD _fcolor = 0 , DWORD _bcolor = 0 ) : x( _x ), y( _y )
	{
		fr = GetRValue( _fcolor );
		fg = GetGValue( _fcolor );
		fb = GetBValue( _fcolor );
		br = GetRValue( _bcolor );
		bg = GetGValue( _bcolor );
		bb = GetBValue( _bcolor );
	}

	VOID SetColor( DWORD _color, BOOL bFG = TRUE )
	{
		if ( bFG )
		{
			fr = GetRValue( _color );
			fg = GetGValue( _color );
			fb = GetBValue( _color );
		}
		else
		{
			br = GetRValue( _color );
			bg = GetGValue( _color );
			bb = GetBValue( _color );
		}
	}

	DWORD GetColor( INT nType ) const 
	{
		if ( nType == 0 )
			return RGB( fr, fg, fb );
		else
			return RGB( br, bg, bb );
	}
};

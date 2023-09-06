#include "stdafx.h"

INT APIENTRY WinMain( HINSTANCE hInstance, 
					  HINSTANCE hPrevInstance, 
					  LPSTR lpCmdLine, 
					  int nShowCmd )
{
	return CWndEx::MessageLoop( hInstance );
}
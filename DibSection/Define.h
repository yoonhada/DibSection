#pragma once

#define SAFE_DELETE( p )			{ if ( p ) { delete	( p );		( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p )		{ if ( p ) { delete[] ( p );	( p ) = NULL; } }
#define SAFE_RELEASE( p )			{ if ( p ) { ( p )->Release();	( p ) = NULL; } }

#define BLACK           RGB(0X00,0X00,0X00)
#define WHITE           RGB(0XFF,0XFF,0XFF)
#define GRAY			RGB(0X80,0X80,0X80)
#define BLUE            RGB(0X00,0X00,0XFF)
#define YELLOW          RGB(0XFF,0XFF,0X00)
#define GREEN           RGB(0X00,0XFF,0X00)
#define MAGENTA         RGB(0XFF,0X00,0XFF)
#define RED             RGB(0XFF,0X00,0X00)
#define CYAN            RGB(0X00,0XFF,0XFF)

#define WM_DIALOGSELECT WM_USER+1

#define SIDE_LEFT		9
#define SIDE_TOP		42

#define RADIAN			0.0174532925f
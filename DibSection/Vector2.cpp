#include "stdafx.h"

CVector2::CVector2( FLOAT _x, FLOAT _y )
: x(_x)
, y(_y)
{
}


CVector2 CVector2::operator-( void ) const
{
	return CVector2( -x, -y );
}


CVector2 CVector2::operator+( const CVector2& vec ) const
{
	return CVector2( x + vec.x, y + vec.y );
}


CVector2 CVector2::operator-( const CVector2& vec ) const
{
	return CVector2( x - vec.x, y - vec.y );
}


FLOAT CVector2::operator*( const CVector2& vec ) const
{
	return ( x * vec.x + y * vec.y );
}


//CVector2 CVector2::operator*( const Matrix2& m ) const
//{
//	CVector2 temp;
//
//	temp.x = x * m._11 + y * m._21;
//	temp.y = x * m._12 + y * m._22;
//
//	return temp;
//}


FLOAT CVector2::operator^( const CVector2& vec ) const
{
	return ( x * vec.y - y * vec.x );
}


CVector2& CVector2::operator+=( const CVector2& vec )
{
	x += vec.x;
	y += vec.y;

	return *this;
}


CVector2& CVector2::operator-=( const CVector2& vec )
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}


CVector2 CVector2::operator*( const FLOAT scalar ) const
{
	return CVector2( x * scalar, y * scalar );
}


CVector2 CVector2::operator/( const FLOAT scalar ) const
{
	return CVector2( x / scalar, y / scalar );
}


CVector2& CVector2::operator*=( const FLOAT scalar )
{
	x *= scalar;
	y *= scalar;

	return *this;
}


CVector2& CVector2::operator/=( const FLOAT scalar )
{
	x /= scalar;
	y /= scalar;

	return *this;
}


void CVector2::Normalize( void )
{
	FLOAT invlength = 1 / sqrt( x * x + y * y );

	x *= invlength;
	y *= invlength;
}

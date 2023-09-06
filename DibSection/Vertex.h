#pragma once

struct CVertex
{
	CVector4 pos;
	CVector4 color;
	CVector3 normal;
	CPoint2 texcoord;

	CVertex(){};
	CVertex(CVector4 p, CVector4 c, CVector3 n, CPoint2 t) : pos(p), color(c), normal(n), texcoord(t) {}
	~CVertex(){};
};
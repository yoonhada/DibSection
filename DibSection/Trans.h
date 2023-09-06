#pragma once

class CNode;
class CTrans
{
public:
	CTrans(int, int);
	virtual ~CTrans(void);

	void Clear();

	void TransModel2World(CNode *, CMatrix4&);
	void TransWorld2View(int, CMatrix4&);
	void TransView2Projection(CMatrix4&);
	void TransProjection2Ndc(CMatrix4 &, CMatrix4 &);
	void TransNdc2Screen(CMatrix4 &);

	void SetRotate(int nAxis, int nValue)	{ m_nRotate[nAxis] = (m_nRotate[nAxis] + nValue) % 360;}
	void SetCamera(int nAxis, float fValue) {
		if(nAxis == AXISX)		{m_vertorCamera.x += fValue;	}
		if(nAxis == AXISY)		{m_vertorCamera.y += fValue;	}
		if(nAxis == AXISZ)		{m_vertorCamera.z += fValue;	}
	}
	void SetTraget(int nAxis, float fValue){					   
		if(nAxis == AXISX)		m_vertorTarget.x += fValue;
		if(nAxis == AXISY)		m_vertorTarget.y += fValue;
		if(nAxis == AXISZ)		m_vertorTarget.z += fValue;
	}

	int  GetRotate(int nAxis)	{ return m_nRotate[nAxis]; }
	float GetCamera(int nAxis){
		if(nAxis == AXISX)		return m_vertorCamera.x;
		else if(nAxis == AXISY) return m_vertorCamera.y;
		else					return m_vertorCamera.z;
	}
	float GetTraget(int nAxis){
		if(nAxis == AXISX)		return m_vertorTarget.x;
		else if(nAxis == AXISY)	return m_vertorTarget.y;
		else					return m_vertorTarget.z;
	};

	void LockAt( CMatrix4& );
	void EulerAngel( CMatrix4& );

	//private:
	int m_nWidth, m_nHeight;
	int m_nRotate[3];
	CVector4 m_vertorCamera;
	CVector4 m_vertorTarget;
	float m_fZn, m_fZf;
};